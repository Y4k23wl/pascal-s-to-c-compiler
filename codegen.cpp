#include "codegen.hpp"

#include <cassert>
#include <iomanip>
#include <sstream>

namespace {

std::string join_strings(const std::vector<std::string> &parts) {
    std::ostringstream out;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << parts[i];
    }
    return out.str();
}

}  // namespace

std::string CodeGenerator::generate(const AstNode *root, const SemanticResult &sem) {
    assert(root != NULL);
    assert(sem.ok);

    reset(sem);
    emit_program(root);
    return out_.str();
}

void CodeGenerator::reset(const SemanticResult &sem) {
    out_.str("");
    out_.clear();
    sem_ = &sem;
    indent_level_ = 0;
    for_temp_counter_ = 0;
    owner_scopes_.clear();

    for (size_t i = 0; i < sem.scope_storage.size(); ++i) {
        const Scope *scope = sem.scope_storage[i].get();
        owner_scopes_[scope->owner] = scope;
    }
}

void CodeGenerator::emit_program(const AstNode *node) {
    const AstNode *block = child_at(node, 1);

    emit_line("#include <stdio.h>");
    emit_line("#include <stdbool.h>");
    emit_line("#include <string.h>");
    emit_line();

    emit_helpers();
    emit_global_decls(block);
    emit_prototypes(child_at(block, 2));
    emit_subprograms(child_at(block, 2));
    emit_main(node);
}

void CodeGenerator::emit_helpers() {
    emit_line("static bool read_bool(bool *out_value) {");
    ++indent_level_;
    emit_line("char buffer[16];");
    emit_line("if (scanf(\"%15s\", buffer) != 1) {");
    ++indent_level_;
    emit_line("return false;");
    --indent_level_;
    emit_line("}");
    emit_line("if (strcmp(buffer, \"true\") == 0 || strcmp(buffer, \"1\") == 0) {");
    ++indent_level_;
    emit_line("*out_value = true;");
    emit_line("return true;");
    --indent_level_;
    emit_line("}");
    emit_line("if (strcmp(buffer, \"false\") == 0 || strcmp(buffer, \"0\") == 0) {");
    ++indent_level_;
    emit_line("*out_value = false;");
    emit_line("return true;");
    --indent_level_;
    emit_line("}");
    emit_line("return false;");
    --indent_level_;
    emit_line("}");
    emit_line();

    emit_line("static void write_bool(bool value) {");
    ++indent_level_;
    emit_line("printf(\"%s\", value ? \"true\" : \"false\");");
    --indent_level_;
    emit_line("}");
    emit_line();
}

void CodeGenerator::emit_global_decls(const AstNode *block) {
    const Scope *global_scope = sem_->global_scope;
    assert(global_scope != NULL);

    emit_const_decls(child_at(block, 0), global_scope, true);
    emit_var_decls(child_at(block, 1), global_scope, true);
    if (child_at(block, 0) != NULL || child_at(block, 1) != NULL) {
        emit_line();
    }
}

void CodeGenerator::emit_prototypes(const AstNode *subprogram_list) {
    if (subprogram_list == NULL || subprogram_list->children.empty()) {
        return;
    }

    for (size_t i = 0; i < subprogram_list->children.size(); ++i) {
        const AstNode *subprogram = subprogram_list->children[i];
        const AstNode *head = child_at(subprogram, 0);
        const Symbol *symbol = lookup_global_symbol(head->text);
        assert(symbol != NULL);
        emit_line(emit_signature(*symbol) + ";");
    }
    emit_line();
}

void CodeGenerator::emit_subprograms(const AstNode *subprogram_list) {
    if (subprogram_list == NULL) {
        return;
    }

    for (size_t i = 0; i < subprogram_list->children.size(); ++i) {
        emit_subprogram(subprogram_list->children[i]);
        emit_line();
    }
}

void CodeGenerator::emit_subprogram(const AstNode *subprogram) {
    const AstNode *head = child_at(subprogram, 0);
    const AstNode *block = child_at(subprogram, 1);
    const Scope *local_scope = scope_for_owner(subprogram);
    const Symbol *symbol = lookup_global_symbol(head->text);

    assert(local_scope != NULL);
    assert(symbol != NULL);

    emit_line(emit_signature(*symbol) + " {");
    ++indent_level_;

    if (symbol->kind == SymbolKind::Function) {
        const std::string init = emit_default_value(symbol->type);
        emit_line(emit_decl(Symbol{"__result",
                                   SymbolKind::Var,
                                   symbol->type,
                                   false,
                                   NULL,
                                   std::vector<ParamInfo>(),
                                   "__result"},
                            false,
                            &init) +
                  ";");
    }

    emit_local_decls(block, local_scope);
    emit_statement_list(child_at(child_at(block, 3), 0));

    if (symbol->kind == SymbolKind::Function) {
        emit_line("return __result;");
    }

    --indent_level_;
    emit_line("}");
}

void CodeGenerator::emit_main(const AstNode *program) {
    const AstNode *block = child_at(program, 1);

    emit_line("int main(void) {");
    ++indent_level_;
    emit_statement_list(child_at(child_at(block, 3), 0));
    emit_line("return 0;");
    --indent_level_;
    emit_line("}");
}

void CodeGenerator::emit_local_decls(const AstNode *block, const Scope *scope) {
    bool emitted = false;

    const AstNode *const_list = child_at(block, 0);
    const AstNode *var_list = child_at(block, 1);
    if (const_list != NULL && !const_list->children.empty()) {
        emit_const_decls(const_list, scope, false);
        emitted = true;
    }
    if (var_list != NULL && !var_list->children.empty()) {
        emit_var_decls(var_list, scope, false);
        emitted = true;
    }
    if (emitted) {
        emit_line();
    }
}

void CodeGenerator::emit_const_decls(const AstNode *const_list,
                                     const Scope *scope,
                                     bool /* is_global */) {
    if (const_list == NULL) {
        return;
    }

    for (size_t i = 0; i < const_list->children.size(); ++i) {
        const AstNode *decl = const_list->children[i];
        const Symbol *symbol = lookup_symbol(scope, decl->text);
        const AstNode *value = child_at(decl, 0);
        assert(symbol != NULL);
        const std::string init = emit_expr(value);
        emit_line(emit_decl(*symbol, true, &init) + ";");
    }
}

void CodeGenerator::emit_var_decls(const AstNode *var_list,
                                   const Scope *scope,
                                   bool /* is_global */) {
    if (var_list == NULL) {
        return;
    }

    for (size_t i = 0; i < var_list->children.size(); ++i) {
        const AstNode *decl = var_list->children[i];
        const AstNode *ids = child_at(decl, 0);
        if (ids == NULL) {
            continue;
        }
        for (size_t j = 0; j < ids->children.size(); ++j) {
            const AstNode *id_node = ids->children[j];
            const Symbol *symbol = lookup_symbol(scope, id_node->text);
            assert(symbol != NULL);
            emit_line(emit_decl(*symbol, false, NULL) + ";");
        }
    }
}

void CodeGenerator::emit_stmt(const AstNode *node) {
    if (node == NULL) {
        return;
    }

    switch (node->kind) {
        case AST_COMPOUND_STMT:
            emit_line("{");
            ++indent_level_;
            emit_statement_list(child_at(node, 0));
            --indent_level_;
            emit_line("}");
            return;
        case AST_STATEMENT_LIST:
            emit_statement_list(node);
            return;
        case AST_EMPTY_STMT:
            emit_line(";");
            return;
        case AST_ASSIGN_STMT: {
            const AstNode *target = child_at(node, 0);
            const AstNode *expr = child_at(node, 1);
            emit_line(emit_assignment_target(target) + " = " + emit_expr(expr) + ";");
            return;
        }
        case AST_CALL_STMT: {
            const Symbol *callee = resolved_symbol(node);
            assert(callee != NULL);
            emit_line(emit_call(*callee, child_at(node, 0)) + ";");
            return;
        }
        case AST_IF_STMT:
            emit_line("if (" + emit_expr(child_at(node, 0)) + ")");
            emit_stmt_as_block(child_at(node, 1));
            if (child_at(node, 2) != NULL) {
                emit_line("else");
                emit_stmt_as_block(child_at(node, 2));
            }
            return;
        case AST_WHILE_STMT:
            emit_line("while (" + emit_expr(child_at(node, 0)) + ")");
            emit_stmt_as_block(child_at(node, 1));
            return;
        case AST_FOR_STMT: {
            const Symbol *loop_symbol = resolved_symbol(node);
            const std::string loop_var =
                loop_symbol->by_ref ? "(*" + loop_symbol->c_name + ")" : loop_symbol->c_name;
            std::ostringstream temp_name;
            temp_name << "__for_end_" << (++for_temp_counter_);

            emit_line("{");
            ++indent_level_;
            emit_line("int " + temp_name.str() + " = " + emit_expr(child_at(node, 1)) + ";");
            emit_line("for (" + loop_var + " = " + emit_expr(child_at(node, 0)) + "; " +
                      loop_var + " <= " + temp_name.str() + "; ++" + loop_var + ")");
            emit_stmt_as_block(child_at(node, 2));
            --indent_level_;
            emit_line("}");
            return;
        }
        case AST_READ_STMT: {
            const AstNode *vars = child_at(node, 0);
            if (vars == NULL) {
                return;
            }
            for (size_t i = 0; i < vars->children.size(); ++i) {
                const AstNode *var = vars->children[i];
                const ExprInfo *info = expr_info(var);
                assert(info != NULL);
                switch (info->type.kind) {
                    case TypeKind::Integer:
                        emit_line("scanf(\"%d\", " + emit_address_of(var) + ");");
                        break;
                    case TypeKind::Real:
                        emit_line("scanf(\"%f\", " + emit_address_of(var) + ");");
                        break;
                    case TypeKind::Char:
                        emit_line("scanf(\" %c\", " + emit_address_of(var) + ");");
                        break;
                    case TypeKind::Boolean:
                        emit_line("read_bool(" + emit_address_of(var) + ");");
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
            return;
        }
        case AST_WRITE_STMT: {
            const AstNode *exprs = child_at(node, 0);
            if (exprs == NULL) {
                return;
            }
            for (size_t i = 0; i < exprs->children.size(); ++i) {
                const AstNode *expr = exprs->children[i];
                const ExprInfo *info = expr_info(expr);
                assert(info != NULL);
                switch (info->type.kind) {
                    case TypeKind::Integer:
                        emit_line("printf(\"%d\", " + emit_expr(expr) + ");");
                        break;
                    case TypeKind::Real:
                        emit_line("printf(\"%g\", " + emit_expr(expr) + ");");
                        break;
                    case TypeKind::Char:
                        emit_line("printf(\"%c\", " + emit_expr(expr) + ");");
                        break;
                    case TypeKind::Boolean:
                        emit_line("write_bool(" + emit_expr(expr) + ");");
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
            return;
        }
        default:
            assert(false);
            return;
    }
}

void CodeGenerator::emit_stmt_as_block(const AstNode *node) {
    if (node != NULL && node->kind == AST_COMPOUND_STMT) {
        emit_stmt(node);
        return;
    }

    emit_line("{");
    ++indent_level_;
    emit_stmt(node);
    --indent_level_;
    emit_line("}");
}

void CodeGenerator::emit_statement_list(const AstNode *node) {
    if (node == NULL) {
        return;
    }
    for (size_t i = 0; i < node->children.size(); ++i) {
        emit_stmt(node->children[i]);
    }
}

std::string CodeGenerator::emit_expr(const AstNode *node) {
    return emit_expr_with_parent(node, 0, false);
}

std::string CodeGenerator::emit_expr_with_parent(const AstNode *node,
                                                 int parent_precedence,
                                                 bool is_right_child) {
    assert(node != NULL);

    const int current_precedence = expr_precedence(node);
    std::string text;

    switch (node->kind) {
        case AST_BOOL_LITERAL:
            text = node->flag ? "true" : "false";
            break;
        case AST_INT_LITERAL: {
            std::ostringstream out;
            out << node->int_value;
            text = out.str();
            break;
        }
        case AST_REAL_LITERAL:
            text = format_real_literal(node->real_value);
            break;
        case AST_CHAR_LITERAL:
            text = node->text;
            break;
        case AST_VAR_REF:
            text = emit_var_ref(node);
            break;
        case AST_CALL_EXPR: {
            const Symbol *callee = resolved_symbol(node);
            assert(callee != NULL);
            text = emit_call(*callee, child_at(node, 0));
            break;
        }
        case AST_UNARY_EXPR: {
            const AstNode *operand = child_at(node, 0);
            const ExprInfo *operand_info = expr_info(operand);
            assert(operand_info != NULL);

            if (node->text == "+") {
                text = "+" + emit_expr_with_parent(operand, current_precedence, true);
                break;
            }
            if (node->text == "-") {
                text = "-" + emit_expr_with_parent(operand, current_precedence, true);
                break;
            }
            if (node->text == "not") {
                if (operand_info->type.kind == TypeKind::Integer) {
                    text = "~" + emit_expr_with_parent(operand, current_precedence, true);
                    break;
                }
                text = "!" + emit_expr_with_parent(operand, current_precedence, true);
                break;
            }
            assert(false);
            break;
        }
        case AST_BINARY_EXPR: {
            const AstNode *lhs = child_at(node, 0);
            const AstNode *rhs = child_at(node, 1);
            const ExprInfo *lhs_info = expr_info(lhs);
            const ExprInfo *rhs_info = expr_info(rhs);
            assert(lhs_info != NULL);
            assert(rhs_info != NULL);

            if (node->text == "/") {
                if (lhs_info->type.kind == TypeKind::Integer &&
                    rhs_info->type.kind == TypeKind::Integer) {
                    text = "(float)" + emit_expr_with_parent(lhs, current_precedence, false) +
                           " / (float)" +
                           emit_expr_with_parent(rhs, current_precedence, true);
                    break;
                }
            }
            text = emit_expr_with_parent(lhs, current_precedence, false) + " " +
                   binary_op_to_c(node->text) + " " +
                   emit_expr_with_parent(rhs, current_precedence, true);
            break;
        }
        default:
            assert(false);
            break;
    }

    if (current_precedence < parent_precedence ||
        (is_right_child && current_precedence == parent_precedence &&
         (node->kind == AST_BINARY_EXPR || node->kind == AST_UNARY_EXPR))) {
        return "(" + text + ")";
    }
    return text;
}

std::string CodeGenerator::emit_var_ref(const AstNode *node) {
    const Symbol *symbol = resolved_symbol(node);
    const AstNode *indices = child_at(node, 0);
    assert(symbol != NULL);

    if (sem_->function_result_refs.find(node) != sem_->function_result_refs.end()) {
        return "__result";
    }

    if (symbol->kind == SymbolKind::Function) {
        return emit_call(*symbol, NULL);
    }

    if (indices == NULL) {
        if (symbol->kind == SymbolKind::Param && symbol->by_ref) {
            return "(*" + symbol->c_name + ")";
        }
        return symbol->c_name;
    }

    std::string out = symbol->c_name;
    for (size_t i = 0; i < indices->children.size(); ++i) {
        const ArrayBound &bound = symbol->type.bounds[i];
        std::ostringstream index_expr;
        index_expr << "(" << emit_expr(indices->children[i]) << ")";
        if (bound.low != 0) {
            index_expr << " - " << bound.low;
        }
        out += "[" + index_expr.str() + "]";
    }
    return out;
}

std::string CodeGenerator::emit_call(const Symbol &callee, const AstNode *arg_list) {
    std::vector<std::string> args;
    if (arg_list != NULL) {
        args.reserve(arg_list->children.size());
        for (size_t i = 0; i < arg_list->children.size(); ++i) {
            const AstNode *arg = arg_list->children[i];
            if (i < callee.params.size() && callee.params[i].by_ref) {
                args.push_back(emit_address_of(arg));
            } else {
                args.push_back(emit_expr(arg));
            }
        }
    }
    return callee.c_name + "(" + join_strings(args) + ")";
}

std::string CodeGenerator::emit_address_of(const AstNode *node) {
    return "(&(" + emit_expr(node) + "))";
}

std::string CodeGenerator::emit_assignment_target(const AstNode *node) {
    if (sem_->function_result_refs.find(node) != sem_->function_result_refs.end()) {
        return "__result";
    }
    return emit_expr(node);
}

std::string CodeGenerator::emit_default_value(const SemType &type) const {
    switch (type.kind) {
        case TypeKind::Integer:
            return "0";
        case TypeKind::Real:
            return "0.0f";
        case TypeKind::Boolean:
            return "false";
        case TypeKind::Char:
            return "'\\0'";
        case TypeKind::Array:
        case TypeKind::Void:
        case TypeKind::Invalid:
            break;
    }
    return "0";
}

std::string CodeGenerator::emit_decl(const Symbol &symbol,
                                     bool with_const,
                                     const std::string *init) const {
    std::ostringstream out;

    if (with_const) {
        out << "const ";
    }

    if (symbol.by_ref) {
        out << c_type_name(symbol.type) << " *" << symbol.c_name;
    } else if (symbol.type.kind == TypeKind::Array) {
        out << c_type_name(*symbol.type.element_type) << " " << symbol.c_name;
        for (size_t i = 0; i < symbol.type.bounds.size(); ++i) {
            const ArrayBound &bound = symbol.type.bounds[i];
            out << "[" << (bound.high - bound.low + 1) << "]";
        }
    } else {
        out << c_type_name(symbol.type) << " " << symbol.c_name;
    }

    if (init != NULL) {
        out << " = " << *init;
    }
    return out.str();
}

std::string CodeGenerator::emit_signature(const Symbol &symbol) const {
    std::vector<std::string> params;
    params.reserve(symbol.params.size());

    for (size_t i = 0; i < symbol.params.size(); ++i) {
        const ParamInfo &param = symbol.params[i];
        Symbol param_symbol;
        param_symbol.name = param.name;
        param_symbol.kind = SymbolKind::Param;
        param_symbol.type = param.type;
        param_symbol.by_ref = param.by_ref;
        param_symbol.decl_node = NULL;
        param_symbol.c_name = param.c_name;
        params.push_back(emit_decl(param_symbol, false, NULL));
    }

    const std::string param_text = params.empty() ? "void" : join_strings(params);
    return c_type_name(symbol.type) + " " + symbol.c_name + "(" + param_text + ")";
}

std::string CodeGenerator::c_type_name(const SemType &type) const {
    switch (type.kind) {
        case TypeKind::Integer:
            return "int";
        case TypeKind::Real:
            return "float";
        case TypeKind::Boolean:
            return "bool";
        case TypeKind::Char:
            return "char";
        case TypeKind::Void:
            return "void";
        case TypeKind::Array:
            assert(type.element_type.get() != NULL);
            return c_type_name(*type.element_type);
        case TypeKind::Invalid:
            break;
    }
    return "void";
}

std::string CodeGenerator::binary_op_to_c(const std::string &op) const {
    if (op == "=") {
        return "==";
    }
    if (op == "<>") {
        return "!=";
    }
    if (op == "div") {
        return "/";
    }
    if (op == "mod") {
        return "%";
    }
    if (op == "and") {
        return "&&";
    }
    if (op == "or") {
        return "||";
    }
    return op;
}

std::string CodeGenerator::format_real_literal(double value) const {
    std::ostringstream out;
    out << std::setprecision(17) << value;
    std::string text = out.str();
    if (text.find('.') == std::string::npos &&
        text.find('e') == std::string::npos &&
        text.find('E') == std::string::npos) {
        text += ".0";
    }
    return text + "f";
}

int CodeGenerator::expr_precedence(const AstNode *node) const {
    if (node == NULL) {
        return 0;
    }

    switch (node->kind) {
        case AST_BINARY_EXPR:
            if (node->text == "*" || node->text == "/" || node->text == "div" ||
                node->text == "mod" || node->text == "and") {
                return 60;
            }
            if (node->text == "+" || node->text == "-" || node->text == "or") {
                return 50;
            }
            return 40;
        case AST_UNARY_EXPR:
            return 70;
        case AST_BOOL_LITERAL:
        case AST_INT_LITERAL:
        case AST_REAL_LITERAL:
        case AST_CHAR_LITERAL:
        case AST_VAR_REF:
        case AST_CALL_EXPR:
            return 80;
        default:
            return 0;
    }
}

const Symbol *CodeGenerator::lookup_symbol(const Scope *scope, const std::string &name) const {
    if (scope == NULL) {
        return NULL;
    }
    std::unordered_map<std::string, Symbol *>::const_iterator it = scope->symbols.find(name);
    if (it == scope->symbols.end()) {
        return NULL;
    }
    return it->second;
}

const Symbol *CodeGenerator::lookup_global_symbol(const std::string &name) const {
    return lookup_symbol(sem_->global_scope, name);
}

const Symbol *CodeGenerator::resolved_symbol(const AstNode *node) const {
    std::unordered_map<const AstNode *, const Symbol *>::const_iterator it =
        sem_->resolved_symbols.find(node);
    if (it == sem_->resolved_symbols.end()) {
        return NULL;
    }
    return it->second;
}

const ExprInfo *CodeGenerator::expr_info(const AstNode *node) const {
    std::unordered_map<const AstNode *, ExprInfo>::const_iterator it = sem_->expr_info.find(node);
    if (it == sem_->expr_info.end()) {
        return NULL;
    }
    return &it->second;
}

const Scope *CodeGenerator::scope_for_owner(const AstNode *owner) const {
    std::unordered_map<const AstNode *, const Scope *>::const_iterator it =
        owner_scopes_.find(owner);
    if (it == owner_scopes_.end()) {
        return NULL;
    }
    return it->second;
}

const AstNode *CodeGenerator::child_at(const AstNode *node, size_t index) const {
    if (node == NULL || index >= node->children.size()) {
        return NULL;
    }
    return node->children[index];
}

void CodeGenerator::emit_indent() {
    for (int i = 0; i < indent_level_; ++i) {
        out_ << "    ";
    }
}

void CodeGenerator::emit_line(const std::string &text) {
    if (!text.empty()) {
        emit_indent();
        out_ << text;
    }
    out_ << "\n";
}
