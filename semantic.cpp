#include "semantic.hpp"

#include <cctype>
#include <cstdio>
#include <utility>
#include <sstream>

namespace {

struct ParamSpec {
    std::string name;
    SemType type;
    bool by_ref;
    const AstNode *decl_node;
    std::string c_name;
};

SemType make_type(TypeKind kind) {
    SemType type;
    type.kind = kind;
    return type;
}

SemType make_invalid_type() {
    return make_type(TypeKind::Invalid);
}

ExprInfo make_expr_info(const SemType &type,
                        bool is_lvalue,
                        bool is_assignable,
                        const Symbol *symbol) {
    ExprInfo info;
    info.type = type;
    info.is_lvalue = is_lvalue;
    info.is_assignable = is_assignable;
    info.symbol = symbol;
    return info;
}

const AstNode *child_at(const AstNode *node, size_t index) {
    if (node == NULL || index >= node->children.size()) {
        return NULL;
    }
    return node->children[index];
}

const AstNode *list_node_child(const AstNode *node) {
    return child_at(node, 0);
}

bool is_relop(const std::string &op) {
    return op == "=" || op == "<>" || op == "<" || op == "<=" || op == ">" || op == ">=";
}

bool comparable_types(const SemType &lhs, const SemType &rhs) {
    if (lhs.kind == TypeKind::Invalid || rhs.kind == TypeKind::Invalid) {
        return true;
    }
    if (is_numeric(lhs) && is_numeric(rhs)) {
        return true;
    }
    return same_type(lhs, rhs) &&
           (lhs.kind == TypeKind::Char || lhs.kind == TypeKind::Boolean);
}

bool io_compatible_type(const SemType &type) {
    return type.kind == TypeKind::Integer ||
           type.kind == TypeKind::Real ||
           type.kind == TypeKind::Boolean ||
           type.kind == TypeKind::Char;
}

class AnalyzerImpl {
public:
    SemanticResult run(const AstNode *root) {
        result_ = SemanticResult();
        current_scope_ = NULL;
        current_function_ = NULL;
        current_function_name_.clear();
        current_function_type_ = make_type(TypeKind::Void);
        subprogram_symbols_.clear();
        subprogram_param_specs_.clear();
        used_c_names_.clear();

        if (root == NULL) {
            SemanticError error;
            error.loc = ast_make_location(0, 0, 0, 0);
            error.message = "语义分析输入 AST 为空";
            result_.errors.push_back(error);
            result_.ok = false;
            return std::move(result_);
        }

        Scope *global_scope = new_scope(NULL, root);
        result_.global_scope = global_scope;
        analyze_program(root, global_scope);
        result_.ok = result_.errors.empty();
        return std::move(result_);
    }

private:
    void analyze_program(const AstNode *root, Scope *global_scope) {
        if (root->kind != AST_PROGRAM) {
            report_error(root, "语义分析入口必须是 AST_PROGRAM");
            return;
        }
        const AstNode *block = child_at(root, 1);
        current_scope_ = global_scope;
        analyze_block(block, global_scope);
        current_scope_ = NULL;
    }

    void analyze_block(const AstNode *block, Scope *scope) {
        if (block == NULL || block->kind != AST_BLOCK) {
            report_error(block, "语义分析期望遇到 Block 节点");
            return;
        }

        Scope *saved_scope = current_scope_;
        current_scope_ = scope;

        declare_consts(child_at(block, 0), scope);
        declare_vars(child_at(block, 1), scope);
        scan_subprogram_heads(child_at(block, 2), scope);
        analyze_subprograms(child_at(block, 2), scope);
        analyze_stmt(child_at(block, 3));

        current_scope_ = saved_scope;
    }

    void declare_consts(const AstNode *const_list, Scope *scope) {
        if (const_list == NULL) {
            return;
        }

        for (size_t i = 0; i < const_list->children.size(); ++i) {
            const AstNode *decl = const_list->children[i];
            const AstNode *value = child_at(decl, 0);
            ExprInfo value_info = analyze_expr(value);
            Symbol *symbol = declare_symbol(scope,
                                            decl->text,
                                            SymbolKind::Const,
                                            value_info.type,
                                            false,
                                            decl,
                                            std::vector<ParamInfo>());
            if (symbol == NULL) {
                continue;
            }
            if (value_info.type.kind == TypeKind::Invalid) {
                report_error(value, "常量声明的值类型无效");
                symbol->type = make_invalid_type();
            }
        }
    }

    void declare_vars(const AstNode *var_list, Scope *scope) {
        if (var_list == NULL) {
            return;
        }

        for (size_t i = 0; i < var_list->children.size(); ++i) {
            const AstNode *decl = var_list->children[i];
            SemType type = parse_type(child_at(decl, 1));
            const AstNode *ids = child_at(decl, 0);
            if (ids == NULL) {
                continue;
            }
            for (size_t j = 0; j < ids->children.size(); ++j) {
                const AstNode *id_node = ids->children[j];
                declare_symbol(scope,
                               id_node->text,
                               SymbolKind::Var,
                               type,
                               false,
                               id_node,
                               std::vector<ParamInfo>());
            }
        }
    }

    void scan_subprogram_heads(const AstNode *subprogram_list, Scope *scope) {
        if (subprogram_list == NULL) {
            return;
        }

        for (size_t i = 0; i < subprogram_list->children.size(); ++i) {
            const AstNode *subprogram = subprogram_list->children[i];
            const AstNode *head = child_at(subprogram, 0);
            if (head == NULL) {
                continue;
            }

            std::vector<ParamSpec> param_specs = collect_params(child_at(head, 0));
            std::vector<ParamInfo> params;
            params.reserve(param_specs.size());
            for (size_t j = 0; j < param_specs.size(); ++j) {
                ParamInfo info;
                info.name = param_specs[j].name;
                info.type = param_specs[j].type;
                info.by_ref = param_specs[j].by_ref;
                info.c_name = param_specs[j].c_name;
                params.push_back(info);
            }

            SymbolKind kind = head->kind == AST_FUNCTION_HEAD
                                  ? SymbolKind::Function
                                  : SymbolKind::Procedure;
            SemType return_type = kind == SymbolKind::Function
                                      ? parse_type(child_at(head, 1))
                                      : make_type(TypeKind::Void);
            Symbol *symbol = declare_symbol(scope,
                                            head->text,
                                            kind,
                                            return_type,
                                            false,
                                            head,
                                            params);
            subprogram_param_specs_[subprogram] = param_specs;
            if (symbol != NULL) {
                subprogram_symbols_[subprogram] = symbol;
            }
        }
    }

    void analyze_subprograms(const AstNode *subprogram_list, Scope *scope) {
        if (subprogram_list == NULL) {
            return;
        }
        for (size_t i = 0; i < subprogram_list->children.size(); ++i) {
            analyze_subprogram(subprogram_list->children[i], scope);
        }
    }

    void analyze_subprogram(const AstNode *subprogram, Scope *enclosing_scope) {
        if (subprogram == NULL) {
            return;
        }

        const AstNode *head = child_at(subprogram, 0);
        const Symbol *subprogram_symbol = NULL;
        std::unordered_map<const AstNode *, const Symbol *>::const_iterator symbol_it =
            subprogram_symbols_.find(subprogram);
        if (symbol_it != subprogram_symbols_.end()) {
            subprogram_symbol = symbol_it->second;
        }

        Scope *saved_scope = current_scope_;
        const Symbol *saved_function = current_function_;
        std::string saved_function_name = current_function_name_;
        SemType saved_function_type = current_function_type_;

        Scope *local_scope = new_scope(enclosing_scope, subprogram);
        current_scope_ = local_scope;
        if (head != NULL && head->kind == AST_FUNCTION_HEAD) {
            current_function_ = subprogram_symbol;
            current_function_name_ = head->text;
            current_function_type_ = parse_type(child_at(head, 1));
        } else {
            current_function_ = NULL;
            current_function_name_.clear();
            current_function_type_ = make_type(TypeKind::Void);
        }

        std::unordered_map<const AstNode *, std::vector<ParamSpec> >::const_iterator params_it =
            subprogram_param_specs_.find(subprogram);
        if (params_it != subprogram_param_specs_.end()) {
            const std::vector<ParamSpec> &specs = params_it->second;
            for (size_t i = 0; i < specs.size(); ++i) {
                declare_param(local_scope, specs[i]);
            }
        }

        analyze_block(child_at(subprogram, 1), local_scope);

        current_scope_ = saved_scope;
        current_function_ = saved_function;
        current_function_name_ = saved_function_name;
        current_function_type_ = saved_function_type;
    }

    void declare_param(Scope *scope, const ParamSpec &spec) {
        Symbol *param = declare_symbol(scope,
                                       spec.name,
                                       SymbolKind::Param,
                                       spec.type,
                                       spec.by_ref,
                                       spec.decl_node,
                                       std::vector<ParamInfo>());
        if (param != NULL) {
            param->c_name = spec.c_name;
        }
    }

    std::vector<ParamSpec> collect_params(const AstNode *param_list) {
        std::vector<ParamSpec> specs;
        if (param_list == NULL) {
            return specs;
        }

        for (size_t i = 0; i < param_list->children.size(); ++i) {
            const AstNode *group = param_list->children[i];
            SemType type = parse_type(child_at(group, 1));
            const AstNode *ids = child_at(group, 0);
            if (ids == NULL) {
                continue;
            }
            for (size_t j = 0; j < ids->children.size(); ++j) {
                const AstNode *id_node = ids->children[j];
                ParamSpec spec;
                spec.name = id_node->text;
                spec.type = type;
                spec.by_ref = group->flag;
                spec.decl_node = id_node;
                spec.c_name = make_unique_c_name(SymbolKind::Param, id_node->text);
                specs.push_back(spec);
            }
        }
        return specs;
    }

    SemType parse_type(const AstNode *type_node) {
        if (type_node == NULL) {
            return make_invalid_type();
        }

        if (type_node->kind == AST_BASIC_TYPE) {
            if (type_node->text == "integer") {
                return make_type(TypeKind::Integer);
            }
            if (type_node->text == "real") {
                return make_type(TypeKind::Real);
            }
            if (type_node->text == "boolean") {
                return make_type(TypeKind::Boolean);
            }
            if (type_node->text == "char") {
                return make_type(TypeKind::Char);
            }
            report_error(type_node, "未知基本类型：" + type_node->text);
            return make_invalid_type();
        }

        if (type_node->kind == AST_ARRAY_TYPE) {
            const AstNode *period_list = child_at(type_node, 0);
            SemType base_type = parse_type(child_at(type_node, 1));
            if (base_type.kind == TypeKind::Invalid) {
                return make_invalid_type();
            }

            SemType array_type;
            array_type.kind = TypeKind::Array;
            array_type.element_type.reset(new SemType(base_type));

            if (period_list == NULL) {
                report_error(type_node, "数组类型缺少下标区间");
                return make_invalid_type();
            }

            for (size_t i = 0; i < period_list->children.size(); ++i) {
                const AstNode *period = period_list->children[i];
                ArrayBound bound;
                bound.low = static_cast<int>(period->int_value);
                bound.high = static_cast<int>(period->second_int_value);
                if (bound.low > bound.high) {
                    report_error(period, "数组区间下界大于上界");
                    return make_invalid_type();
                }
                array_type.bounds.push_back(bound);
            }
            return array_type;
        }

        report_error(type_node, "未知类型节点：" + std::string(ast_kind_name(type_node->kind)));
        return make_invalid_type();
    }

    void analyze_stmt(const AstNode *node) {
        if (node == NULL) {
            return;
        }

        switch (node->kind) {
            case AST_COMPOUND_STMT:
                analyze_statement_list(list_node_child(node));
                return;
            case AST_STATEMENT_LIST:
                analyze_statement_list(node);
                return;
            case AST_EMPTY_STMT:
                return;
            case AST_ASSIGN_STMT:
                analyze_assign_stmt(node);
                return;
            case AST_CALL_STMT:
                analyze_call_stmt(node);
                return;
            case AST_IF_STMT:
                analyze_if_stmt(node);
                return;
            case AST_WHILE_STMT:
                analyze_while_stmt(node);
                return;
            case AST_FOR_STMT:
                analyze_for_stmt(node);
                return;
            case AST_READ_STMT:
                analyze_read_stmt(node);
                return;
            case AST_WRITE_STMT:
                analyze_write_stmt(node);
                return;
            default:
                report_error(node,
                             "语义分析遇到无法处理的语句节点：" +
                                 std::string(ast_kind_name(node->kind)));
                return;
        }
    }

    void analyze_statement_list(const AstNode *statement_list) {
        if (statement_list == NULL) {
            return;
        }
        for (size_t i = 0; i < statement_list->children.size(); ++i) {
            analyze_stmt(statement_list->children[i]);
        }
    }

    void analyze_assign_stmt(const AstNode *node) {
        const AstNode *target = child_at(node, 0);
        const AstNode *expr = child_at(node, 1);

        ExprInfo lhs_info;
        bool is_function_result = false;
        if (is_current_function_result_ref(target)) {
            lhs_info = make_expr_info(current_function_type_, true, true, current_function_);
            remember_expr_info(target, lhs_info);
            result_.function_result_refs.insert(target);
            is_function_result = true;
        } else {
            lhs_info = analyze_expr(target);
        }

        ExprInfo rhs_info = analyze_expr(expr);

        if (lhs_info.type.kind == TypeKind::Array && !is_function_result) {
            report_error(target, "不支持对整个数组做赋值");
            return;
        }

        if (!lhs_info.is_assignable && lhs_info.type.kind != TypeKind::Invalid) {
            if (is_function_result) {
                report_error(target, "函数返回值引用不可赋值");
            } else {
                report_error(target, "赋值语句左侧不是可赋值左值");
            }
        }

        if (!assignment_compatible(lhs_info.type, rhs_info.type) &&
            lhs_info.type.kind != TypeKind::Invalid &&
            rhs_info.type.kind != TypeKind::Invalid) {
            report_error(node,
                         "赋值类型不兼容：无法将 " + type_to_string(rhs_info.type) +
                             " 赋给 " + type_to_string(lhs_info.type));
        }
    }

    void analyze_call_stmt(const AstNode *node) {
        const Symbol *callee = lookup(node->text);
        if (callee == NULL) {
            report_error(node, "未声明的子程序：" + node->text);
            analyze_argument_list(child_at(node, 0));
            return;
        }

        result_.resolved_symbols[node] = callee;

        if (callee->kind != SymbolKind::Procedure && callee->kind != SymbolKind::Function) {
            report_error(node, "调用语句中的目标不是过程或函数：" + node->text);
            analyze_argument_list(child_at(node, 0));
            return;
        }

        check_call_arguments(*callee, node, child_at(node, 0));
    }

    void analyze_if_stmt(const AstNode *node) {
        ExprInfo cond_info = analyze_expr(child_at(node, 0));
        if (cond_info.type.kind != TypeKind::Invalid &&
            cond_info.type.kind != TypeKind::Boolean) {
            report_error(child_at(node, 0), "if 条件表达式必须是 boolean");
        }

        analyze_stmt(child_at(node, 1));
        analyze_stmt(child_at(node, 2));
    }

    void analyze_while_stmt(const AstNode *node) {
        ExprInfo cond_info = analyze_expr(child_at(node, 0));
        if (cond_info.type.kind != TypeKind::Invalid &&
            cond_info.type.kind != TypeKind::Boolean) {
            report_error(child_at(node, 0), "while 条件表达式必须是 boolean");
        }

        analyze_stmt(child_at(node, 1));
    }

    void analyze_for_stmt(const AstNode *node) {
        const Symbol *symbol = lookup(node->text);
        if (symbol == NULL) {
            report_error(node, "for 循环变量未声明：" + node->text);
        } else {
            result_.resolved_symbols[node] = symbol;
            if (symbol->kind != SymbolKind::Var && symbol->kind != SymbolKind::Param) {
                report_error(node, "for 循环变量必须是变量或参数：" + node->text);
            } else if (!same_type(symbol->type, make_type(TypeKind::Integer))) {
                report_error(node, "for 循环变量必须是 integer：" + node->text);
            } else if (symbol->kind == SymbolKind::Param || symbol->kind == SymbolKind::Var) {
                ExprInfo loop_var_info =
                    make_expr_info(symbol->type, true, symbol->type.kind != TypeKind::Array, symbol);
                if (!loop_var_info.is_assignable) {
                    report_error(node, "for 循环变量必须是可赋值整数变量");
                }
            }
        }

        ExprInfo start_info = analyze_expr(child_at(node, 0));
        ExprInfo end_info = analyze_expr(child_at(node, 1));
        if (start_info.type.kind != TypeKind::Invalid &&
            start_info.type.kind != TypeKind::Integer) {
            report_error(child_at(node, 0), "for 起始表达式必须是 integer");
        }
        if (end_info.type.kind != TypeKind::Invalid &&
            end_info.type.kind != TypeKind::Integer) {
            report_error(child_at(node, 1), "for 终止表达式必须是 integer");
        }

        analyze_stmt(child_at(node, 2));
    }

    void analyze_read_stmt(const AstNode *node) {
        const AstNode *vars = child_at(node, 0);
        if (vars == NULL) {
            return;
        }
        for (size_t i = 0; i < vars->children.size(); ++i) {
            ExprInfo info = analyze_expr(vars->children[i]);
            if (info.type.kind == TypeKind::Array) {
                report_error(vars->children[i], "read 不支持整个数组");
                continue;
            }
            if (!info.is_assignable && info.type.kind != TypeKind::Invalid) {
                report_error(vars->children[i], "read 参数必须是可赋值左值");
            } else if (info.type.kind != TypeKind::Invalid && !io_compatible_type(info.type)) {
                report_error(vars->children[i],
                             "read 仅支持 integer、real、boolean、char 类型");
            }
        }
    }

    void analyze_write_stmt(const AstNode *node) {
        const AstNode *exprs = child_at(node, 0);
        if (exprs == NULL) {
            return;
        }
        for (size_t i = 0; i < exprs->children.size(); ++i) {
            ExprInfo info = analyze_expr(exprs->children[i]);
            if (info.type.kind == TypeKind::Array) {
                report_error(exprs->children[i], "write 不支持直接输出整个数组");
            } else if (info.type.kind != TypeKind::Invalid && !io_compatible_type(info.type)) {
                report_error(exprs->children[i],
                             "write 仅支持 integer、real、boolean、char 类型");
            }
        }
    }

    void analyze_argument_list(const AstNode *arg_list) {
        if (arg_list == NULL) {
            return;
        }
        for (size_t i = 0; i < arg_list->children.size(); ++i) {
            analyze_expr(arg_list->children[i]);
        }
    }

    bool check_call_arguments(const Symbol &callee,
                              const AstNode *call_node,
                              const AstNode *arg_list) {
        std::vector<ExprInfo> args;
        if (arg_list != NULL) {
            args.reserve(arg_list->children.size());
            for (size_t i = 0; i < arg_list->children.size(); ++i) {
                args.push_back(analyze_expr(arg_list->children[i]));
            }
        }

        if (args.size() != callee.params.size()) {
            std::ostringstream out;
            out << "调用 " << callee.name << " 的实参数量不匹配：期望 "
                << callee.params.size() << " 个，实际得到 " << args.size() << " 个";
            report_error(call_node, out.str());
            return false;
        }

        bool ok = true;
        for (size_t i = 0; i < args.size(); ++i) {
            const ParamInfo &param = callee.params[i];
            const ExprInfo &arg = args[i];
            const AstNode *arg_node = arg_list->children[i];

            if (param.by_ref) {
                if (!arg.is_assignable && arg.type.kind != TypeKind::Invalid) {
                    report_error(arg_node,
                                 "第 " + ordinal(i + 1) +
                                     " 个实参必须是可赋值左值，因为对应形参是 var 参数");
                    ok = false;
                }
                if (!same_type(param.type, arg.type) &&
                    param.type.kind != TypeKind::Invalid &&
                    arg.type.kind != TypeKind::Invalid) {
                    report_error(arg_node,
                                 "第 " + ordinal(i + 1) + " 个 var 参数类型必须严格一致：期望 " +
                                     type_to_string(param.type) + "，实际为 " +
                                     type_to_string(arg.type));
                    ok = false;
                }
            } else if (!assignment_compatible(param.type, arg.type) &&
                       param.type.kind != TypeKind::Invalid &&
                       arg.type.kind != TypeKind::Invalid) {
                report_error(arg_node,
                             "第 " + ordinal(i + 1) + " 个参数类型不兼容：期望 " +
                                 type_to_string(param.type) + "，实际为 " +
                                 type_to_string(arg.type));
                ok = false;
            }
        }
        return ok;
    }

    ExprInfo compute_expr_info(const AstNode *node) {
        switch (node->kind) {
            case AST_BOOL_LITERAL:
                return make_expr_info(make_type(TypeKind::Boolean), false, false, NULL);
            case AST_INT_LITERAL:
                return make_expr_info(make_type(TypeKind::Integer), false, false, NULL);
            case AST_REAL_LITERAL:
                return make_expr_info(make_type(TypeKind::Real), false, false, NULL);
            case AST_CHAR_LITERAL:
                return make_expr_info(make_type(TypeKind::Char), false, false, NULL);
            case AST_VAR_REF:
                return analyze_var_ref(node);
            case AST_CALL_EXPR:
                return analyze_call_expr(node);
            case AST_UNARY_EXPR:
                return analyze_unary_expr_from_operand(
                    node, result_.expr_info.find(child_at(node, 0))->second);
            case AST_BINARY_EXPR:
                return analyze_binary_expr_from_children(
                    node,
                    result_.expr_info.find(child_at(node, 0))->second,
                    result_.expr_info.find(child_at(node, 1))->second);
            default:
                report_error(node,
                             "语义分析遇到无法处理的表达式节点：" +
                                 std::string(ast_kind_name(node->kind)));
                return make_expr_info(make_invalid_type(), false, false, NULL);
        }
    }

    ExprInfo analyze_expr_iterative(const AstNode *root) {
        std::vector<std::pair<const AstNode *, bool> > stack;
        stack.push_back(std::make_pair(root, false));

        while (!stack.empty()) {
            const AstNode *node = stack.back().first;
            bool expanded = stack.back().second;
            stack.pop_back();

            if (node == NULL) {
                continue;
            }
            if (result_.expr_info.find(node) != result_.expr_info.end()) {
                continue;
            }

            if (!expanded) {
                stack.push_back(std::make_pair(node, true));
                if (node->kind == AST_BINARY_EXPR) {
                    const AstNode *rhs = child_at(node, 1);
                    const AstNode *lhs = child_at(node, 0);
                    if (rhs != NULL && result_.expr_info.find(rhs) == result_.expr_info.end()) {
                        stack.push_back(std::make_pair(rhs, false));
                    }
                    if (lhs != NULL && result_.expr_info.find(lhs) == result_.expr_info.end()) {
                        stack.push_back(std::make_pair(lhs, false));
                    }
                } else if (node->kind == AST_UNARY_EXPR) {
                    const AstNode *operand = child_at(node, 0);
                    if (operand != NULL &&
                        result_.expr_info.find(operand) == result_.expr_info.end()) {
                        stack.push_back(std::make_pair(operand, false));
                    }
                }
                continue;
            }

            remember_expr_info(node, compute_expr_info(node));
        }

        return result_.expr_info.find(root)->second;
    }

    ExprInfo analyze_expr(const AstNode *node) {
        if (node == NULL) {
            return make_expr_info(make_invalid_type(), false, false, NULL);
        }

        std::unordered_map<const AstNode *, ExprInfo>::const_iterator cached =
            result_.expr_info.find(node);
        if (cached != result_.expr_info.end()) {
            return cached->second;
        }

        if (node->kind == AST_BINARY_EXPR || node->kind == AST_UNARY_EXPR) {
            return analyze_expr_iterative(node);
        }

        ExprInfo info = compute_expr_info(node);
        remember_expr_info(node, info);
        return info;
    }

    ExprInfo analyze_var_ref(const AstNode *node) {
        const Symbol *symbol = lookup(node->text);
        if (symbol == NULL) {
            report_error(node, "未声明的标识符：" + node->text);
            return make_expr_info(make_invalid_type(), false, false, NULL);
        }

        result_.resolved_symbols[node] = symbol;

        if (symbol->kind == SymbolKind::Procedure) {
            report_error(node, "过程不能作为表达式使用：" + node->text);
            return make_expr_info(make_invalid_type(), false, false, symbol);
        }

        const AstNode *indices = child_at(node, 0);
        if (symbol->kind == SymbolKind::Function) {
            if (indices != NULL) {
                report_error(node, "函数结果不能使用数组下标：" + node->text);
                analyze_argument_list(indices);
                return make_expr_info(make_invalid_type(), false, false, symbol);
            }
            if (!symbol->params.empty()) {
                report_error(node, "带参数的函数必须显式调用：" + node->text);
                return make_expr_info(make_invalid_type(), false, false, symbol);
            }
            return make_expr_info(symbol->type, false, false, symbol);
        }

        if (indices == NULL) {
            bool is_assignable =
                symbol->kind != SymbolKind::Const && symbol->type.kind != TypeKind::Array;
            bool is_lvalue = symbol->kind != SymbolKind::Const;
            return make_expr_info(symbol->type, is_lvalue, is_assignable, symbol);
        }

        if (symbol->type.kind != TypeKind::Array || symbol->type.element_type.get() == NULL) {
            report_error(node, "只有数组变量才能使用下标：" + node->text);
            analyze_argument_list(indices);
            return make_expr_info(make_invalid_type(), false, false, symbol);
        }

        if (indices->children.size() != symbol->type.bounds.size()) {
            std::ostringstream out;
            out << "数组 " << node->text << " 的下标维数不匹配：期望 "
                << symbol->type.bounds.size() << " 维，实际得到 "
                << indices->children.size() << " 维";
            report_error(node, out.str());
        }

        for (size_t i = 0; i < indices->children.size(); ++i) {
            ExprInfo index_info = analyze_expr(indices->children[i]);
            if (index_info.type.kind != TypeKind::Invalid &&
                index_info.type.kind != TypeKind::Integer) {
                report_error(indices->children[i], "数组下标表达式必须是 integer");
            }
        }

        return make_expr_info(*symbol->type.element_type,
                              symbol->kind != SymbolKind::Const,
                              symbol->kind != SymbolKind::Const,
                              symbol);
    }

    ExprInfo analyze_call_expr(const AstNode *node) {
        const Symbol *callee = lookup(node->text);
        if (callee == NULL) {
            report_error(node, "未声明的函数：" + node->text);
            analyze_argument_list(child_at(node, 0));
            return make_expr_info(make_invalid_type(), false, false, NULL);
        }

        result_.resolved_symbols[node] = callee;

        if (callee->kind != SymbolKind::Function) {
            report_error(node, "表达式中的调用目标不是函数：" + node->text);
            analyze_argument_list(child_at(node, 0));
            return make_expr_info(make_invalid_type(), false, false, callee);
        }

        check_call_arguments(*callee, node, child_at(node, 0));
        return make_expr_info(callee->type, false, false, callee);
    }

    ExprInfo analyze_unary_expr_from_operand(const AstNode *node, const ExprInfo &operand) {
        if (node->text == "+") {
            if (operand.type.kind != TypeKind::Invalid && !is_numeric(operand.type)) {
                report_error(node, "一元正号只接受 integer 或 real");
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(operand.type, false, false, NULL);
        }

        if (node->text == "-") {
            if (operand.type.kind != TypeKind::Invalid && !is_numeric(operand.type)) {
                report_error(node, "一元负号只接受 integer 或 real");
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(operand.type, false, false, NULL);
        }

        if (node->text == "not") {
            if (operand.type.kind != TypeKind::Invalid &&
                operand.type.kind != TypeKind::Boolean &&
                operand.type.kind != TypeKind::Integer) {
                report_error(node, "not 运算只接受 boolean 或 integer");
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(operand.type, false, false, NULL);
        }

        report_error(node, "未知一元运算符：" + node->text);
        return make_expr_info(make_invalid_type(), false, false, NULL);
    }

    ExprInfo analyze_unary_expr(const AstNode *node) {
        return analyze_unary_expr_from_operand(node, analyze_expr(child_at(node, 0)));
    }

    ExprInfo analyze_binary_expr_from_children(const AstNode *node,
                                               const ExprInfo &lhs,
                                               const ExprInfo &rhs) {
        const std::string &op = node->text;

        if (op == "+" || op == "-" || op == "*") {
            if (!is_numeric(lhs.type) || !is_numeric(rhs.type)) {
                if (lhs.type.kind != TypeKind::Invalid && rhs.type.kind != TypeKind::Invalid) {
                    report_error(node, "算术运算只接受 integer 或 real");
                }
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            if (lhs.type.kind == TypeKind::Real || rhs.type.kind == TypeKind::Real) {
                return make_expr_info(make_type(TypeKind::Real), false, false, NULL);
            }
            return make_expr_info(make_type(TypeKind::Integer), false, false, NULL);
        }

        if (op == "/") {
            if (!is_numeric(lhs.type) || !is_numeric(rhs.type)) {
                if (lhs.type.kind != TypeKind::Invalid && rhs.type.kind != TypeKind::Invalid) {
                    report_error(node, "实数除法只接受 integer 或 real");
                }
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(make_type(TypeKind::Real), false, false, NULL);
        }

        if (op == "div" || op == "mod") {
            if (lhs.type.kind != TypeKind::Integer || rhs.type.kind != TypeKind::Integer) {
                if (lhs.type.kind != TypeKind::Invalid && rhs.type.kind != TypeKind::Invalid) {
                    report_error(node, std::string(op) + " 运算只接受 integer");
                }
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(make_type(TypeKind::Integer), false, false, NULL);
        }

        if (op == "and" || op == "or") {
            if (lhs.type.kind != TypeKind::Boolean || rhs.type.kind != TypeKind::Boolean) {
                if (lhs.type.kind != TypeKind::Invalid && rhs.type.kind != TypeKind::Invalid) {
                    report_error(node, std::string(op) + " 运算只接受 boolean");
                }
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(make_type(TypeKind::Boolean), false, false, NULL);
        }

        if (is_relop(op)) {
            if (!comparable_types(lhs.type, rhs.type)) {
                if (lhs.type.kind != TypeKind::Invalid && rhs.type.kind != TypeKind::Invalid) {
                    report_error(node,
                                 "关系运算两侧类型不可比较：" + type_to_string(lhs.type) +
                                     " 与 " + type_to_string(rhs.type));
                }
                return make_expr_info(make_invalid_type(), false, false, NULL);
            }
            return make_expr_info(make_type(TypeKind::Boolean), false, false, NULL);
        }

        report_error(node, "未知二元运算符：" + op);
        return make_expr_info(make_invalid_type(), false, false, NULL);
    }

    ExprInfo analyze_binary_expr(const AstNode *node) {
        return analyze_binary_expr_from_children(
            node, analyze_expr(child_at(node, 0)), analyze_expr(child_at(node, 1)));
    }

    bool is_current_function_result_ref(const AstNode *target) const {
        if (target == NULL || target->kind != AST_VAR_REF) {
            return false;
        }
        if (current_function_name_.empty()) {
            return false;
        }
        if (target->text != current_function_name_) {
            return false;
        }
        if (child_at(target, 0) != NULL) {
            return false;
        }
        return lookup_current_scope_symbol(target->text) == NULL;
    }

    Scope *new_scope(Scope *parent, const AstNode *owner) {
        std::unique_ptr<Scope> scope(new Scope());
        scope->parent = parent;
        scope->owner = owner;
        scope->depth = parent == NULL ? 0 : parent->depth + 1;
        Scope *ptr = scope.get();
        result_.scope_storage.push_back(std::move(scope));
        return ptr;
    }

    Symbol *declare_symbol(Scope *scope,
                           const std::string &name,
                           SymbolKind kind,
                           const SemType &type,
                           bool by_ref,
                           const AstNode *decl_node,
                           const std::vector<ParamInfo> &params) {
        if (scope == NULL) {
            return NULL;
        }

        if (scope->symbols.find(name) != scope->symbols.end()) {
            report_error(decl_node, "同一作用域内重复声明标识符：" + name);
            return NULL;
        }

        std::unique_ptr<Symbol> symbol(new Symbol());
        symbol->name = name;
        symbol->kind = kind;
        symbol->type = type;
        symbol->by_ref = by_ref;
        symbol->decl_node = decl_node;
        symbol->params = params;
        symbol->c_name = make_unique_c_name(kind, name);

        Symbol *ptr = symbol.get();
        result_.symbol_storage.push_back(std::move(symbol));
        scope->symbols[name] = ptr;
        return ptr;
    }

    const Symbol *lookup(const std::string &name) const {
        Scope *scope = current_scope_;
        while (scope != NULL) {
            std::unordered_map<std::string, Symbol *>::const_iterator it =
                scope->symbols.find(name);
            if (it != scope->symbols.end()) {
                return it->second;
            }
            scope = scope->parent;
        }
        return NULL;
    }

    const Symbol *lookup_current_scope_symbol(const std::string &name) const {
        if (current_scope_ == NULL) {
            return NULL;
        }
        std::unordered_map<std::string, Symbol *>::const_iterator it =
            current_scope_->symbols.find(name);
        if (it == current_scope_->symbols.end()) {
            return NULL;
        }
        return it->second;
    }

    std::string make_unique_c_name(SymbolKind kind, const std::string &name) {
        std::string prefix;
        switch (kind) {
            case SymbolKind::Const: prefix = "c_"; break;
            case SymbolKind::Var:
                prefix = (current_scope_ != NULL && current_scope_->depth == 0) ? "g_" : "l_";
                break;
            case SymbolKind::Param: prefix = "p_"; break;
            case SymbolKind::Procedure:
            case SymbolKind::Function:
                prefix = "fn_";
                break;
        }

        std::string base = sanitize_identifier(name);
        if (base.empty()) {
            base = "unnamed";
        }

        std::string candidate = prefix + base;
        size_t suffix = 1;
        while (used_c_names_.find(candidate) != used_c_names_.end()) {
            std::ostringstream out;
            out << prefix << base << "_" << suffix;
            candidate = out.str();
            ++suffix;
        }
        used_c_names_.insert(candidate);
        return candidate;
    }

    std::string sanitize_identifier(const std::string &name) const {
        std::string cleaned;
        cleaned.reserve(name.size());
        for (size_t i = 0; i < name.size(); ++i) {
            unsigned char ch = static_cast<unsigned char>(name[i]);
            if (std::isalnum(ch) || ch == '_') {
                cleaned.push_back(static_cast<char>(std::tolower(ch)));
            } else {
                cleaned.push_back('_');
            }
        }
        return cleaned;
    }

    void remember_expr_info(const AstNode *node, const ExprInfo &info) {
        if (node != NULL) {
            result_.expr_info[node] = info;
        }
    }

    void report_error(const AstNode *node, const std::string &message) {
        SemanticError error;
        if (node != NULL) {
            error.loc = node->loc;
        } else {
            error.loc = ast_make_location(0, 0, 0, 0);
        }
        error.message = message;
        result_.errors.push_back(error);
    }

    std::string ordinal(size_t n) const {
        std::ostringstream out;
        out << n;
        return out.str();
    }

    SemanticResult result_;
    Scope *current_scope_;
    const Symbol *current_function_;
    std::string current_function_name_;
    SemType current_function_type_;
    std::unordered_map<const AstNode *, const Symbol *> subprogram_symbols_;
    std::unordered_map<const AstNode *, std::vector<ParamSpec> > subprogram_param_specs_;
    std::unordered_set<std::string> used_c_names_;
};

}  // namespace

bool is_numeric(const SemType &type) {
    return type.kind == TypeKind::Integer || type.kind == TypeKind::Real;
}

bool is_scalar(const SemType &type) {
    return type.kind == TypeKind::Integer ||
           type.kind == TypeKind::Real ||
           type.kind == TypeKind::Boolean ||
           type.kind == TypeKind::Char;
}

bool same_type(const SemType &a, const SemType &b) {
    if (a.kind != b.kind) {
        return false;
    }
    if (a.kind == TypeKind::Array) {
        if (a.bounds.size() != b.bounds.size()) {
            return false;
        }
        for (size_t i = 0; i < a.bounds.size(); ++i) {
            if (a.bounds[i].low != b.bounds[i].low || a.bounds[i].high != b.bounds[i].high) {
                return false;
            }
        }
        if (a.element_type.get() == NULL || b.element_type.get() == NULL) {
            return a.element_type.get() == b.element_type.get();
        }
        return same_type(*a.element_type, *b.element_type);
    }
    return true;
}

bool assignment_compatible(const SemType &lhs, const SemType &rhs) {
    if (lhs.kind == TypeKind::Invalid || rhs.kind == TypeKind::Invalid) {
        return true;
    }
    if (same_type(lhs, rhs)) {
        return true;
    }
    return lhs.kind == TypeKind::Real && rhs.kind == TypeKind::Integer;
}

std::string type_to_string(const SemType &type) {
    switch (type.kind) {
        case TypeKind::Integer:
            return "integer";
        case TypeKind::Real:
            return "real";
        case TypeKind::Boolean:
            return "boolean";
        case TypeKind::Char:
            return "char";
        case TypeKind::Void:
            return "void";
        case TypeKind::Invalid:
            return "<invalid>";
        case TypeKind::Array: {
            std::ostringstream out;
            out << "array[";
            for (size_t i = 0; i < type.bounds.size(); ++i) {
                if (i != 0) {
                    out << ", ";
                }
                out << type.bounds[i].low << ".." << type.bounds[i].high;
            }
            out << "] of ";
            if (type.element_type.get() != NULL) {
                out << type_to_string(*type.element_type);
            } else {
                out << "<invalid>";
            }
            return out.str();
        }
    }
    return "<invalid>";
}

SemanticResult SemanticAnalyzer::analyze(const AstNode *root) {
    AnalyzerImpl impl;
    return impl.run(root);
}

void print_semantic_errors(FILE *out, const std::vector<SemanticError> &errors) {
    for (size_t i = 0; i < errors.size(); ++i) {
        const SemanticError &error = errors[i];
        std::fprintf(out,
                     "[语义错误] 行：%d，列：%d - %s\n",
                     error.loc.first_line,
                     error.loc.first_column,
                     error.message.c_str());
    }
}
