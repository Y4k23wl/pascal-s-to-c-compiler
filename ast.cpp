#include "ast.hpp"

#include <sstream>

namespace {

void ast_dump_impl(FILE *out, const AstNode *node, int indent) {
    if (node == NULL) {
        std::fprintf(out, "%*s(null)\n", indent, "");
        return;
    }

    std::ostringstream meta;
    switch (node->kind) {
        case AST_IDENTIFIER:
        case AST_BASIC_TYPE:
        case AST_PROGRAM_HEAD:
        case AST_PROCEDURE_HEAD:
        case AST_FUNCTION_HEAD:
        case AST_CONST_DECL:
        case AST_VAR_REF:
        case AST_CALL_STMT:
        case AST_CALL_EXPR:
        case AST_FOR_STMT:
        case AST_BINARY_EXPR:
        case AST_UNARY_EXPR:
            if (!node->text.empty()) {
                meta << " text=\"" << node->text << "\"";
            }
            break;
        default:
            break;
    }

    if (node->kind == AST_INT_LITERAL) {
        meta << " value=" << node->int_value;
    }
    if (node->kind == AST_PERIOD) {
        meta << " low=" << node->int_value
             << " high=" << node->second_int_value;
    }
    if (node->kind == AST_REAL_LITERAL) {
        meta << " value=" << node->real_value;
    }
    if (node->kind == AST_CHAR_LITERAL) {
        meta << " text=\"" << node->text << "\"";
    }
    if (node->kind == AST_PARAM_GROUP) {
        meta << " by_ref=" << (node->flag ? "true" : "false");
    }
    std::fprintf(out,
                 "%*s%s%s [%d:%d-%d:%d]\n",
                 indent,
                 "",
                 ast_kind_name(node->kind),
                 meta.str().c_str(),
                 node->loc.first_line,
                 node->loc.first_column,
                 node->loc.last_line,
                 node->loc.last_column);

    for (std::vector<AstNode *>::const_iterator it = node->children.begin();
         it != node->children.end();
         ++it) {
        ast_dump_impl(out, *it, indent + 2);
    }
}

}  // namespace

AstLocation ast_make_location(int first_line,
                              int first_column,
                              int last_line,
                              int last_column) {
    AstLocation loc;
    loc.first_line = first_line;
    loc.first_column = first_column;
    loc.last_line = last_line;
    loc.last_column = last_column;
    return loc;
}

AstNode *ast_new(AstKind kind, AstLocation loc) {
    AstNode *node = new AstNode();
    node->kind = kind;
    node->loc = loc;
    node->int_value = 0;
    node->second_int_value = 0;
    node->real_value = 0.0;
    node->flag = false;
    return node;
}

AstNode *ast_new_text(AstKind kind, AstLocation loc, const char *text) {
    AstNode *node = ast_new(kind, loc);
    if (text != NULL) {
        node->text = text;
    }
    return node;
}

AstNode *ast_new_int(AstKind kind, AstLocation loc, long long value) {
    AstNode *node = ast_new(kind, loc);
    node->int_value = value;
    return node;
}

AstNode *ast_new_real(AstKind kind, AstLocation loc, double value) {
    AstNode *node = ast_new(kind, loc);
    node->real_value = value;
    return node;
}

AstNode *ast_add_child(AstNode *parent, AstNode *child) {
    if (parent != NULL && child != NULL) {
        parent->children.push_back(child);
    }
    return parent;
}

AstNode *ast_append_list(AstNode *list, AstNode *item) {
    if (list == NULL) {
        return item;
    }
    return ast_add_child(list, item);
}

AstNode *ast_make_identifier(const char *name, AstLocation loc) {
    return ast_new_text(AST_IDENTIFIER, loc, name);
}

AstNode *ast_make_identifier_list(AstNode *first, AstLocation loc) {
    AstNode *list = ast_new(AST_IDENTIFIER_LIST, loc);
    return ast_append_list(list, first);
}

AstNode *ast_make_basic_type(const char *name, AstLocation loc) {
    return ast_new_text(AST_BASIC_TYPE, loc, name);
}

AstNode *ast_make_const_decl(const char *name, AstNode *value, AstLocation loc) {
    AstNode *node = ast_new_text(AST_CONST_DECL, loc, name);
    return ast_add_child(node, value);
}

AstNode *ast_make_var_decl(AstNode *ids, AstNode *type, AstLocation loc) {
    AstNode *node = ast_new(AST_VAR_DECL, loc);
    ast_add_child(node, ids);
    ast_add_child(node, type);
    return node;
}

AstNode *ast_make_period(int low, int high, AstLocation loc) {
    AstNode *node = ast_new_int(AST_PERIOD, loc, low);
    node->second_int_value = high;
    return node;
}

AstNode *ast_make_array_type(AstNode *periods, AstNode *base_type, AstLocation loc) {
    AstNode *node = ast_new(AST_ARRAY_TYPE, loc);
    ast_add_child(node, periods);
    ast_add_child(node, base_type);
    return node;
}

AstNode *ast_make_program_head(const char *name, AstNode *ids, AstLocation loc) {
    AstNode *node = ast_new_text(AST_PROGRAM_HEAD, loc, name);
    if (ids != NULL) {
        ast_add_child(node, ids);
    }
    return node;
}

AstNode *ast_make_block(AstNode *consts,
                        AstNode *vars,
                        AstNode *subprograms,
                        AstNode *compound_stmt,
                        AstLocation loc) {
    AstNode *node = ast_new(AST_BLOCK, loc);
    ast_add_child(node, consts);
    ast_add_child(node, vars);
    ast_add_child(node, subprograms);
    ast_add_child(node, compound_stmt);
    return node;
}

AstNode *ast_make_program(AstNode *head, AstNode *body, AstLocation loc) {
    AstNode *node = ast_new(AST_PROGRAM, loc);
    ast_add_child(node, head);
    ast_add_child(node, body);
    return node;
}

AstNode *ast_make_subprogram_head(bool is_function,
                                  const char *name,
                                  AstNode *params,
                                  AstNode *return_type,
                                  AstLocation loc) {
    AstNode *node = ast_new_text(is_function ? AST_FUNCTION_HEAD : AST_PROCEDURE_HEAD,
                                 loc,
                                 name);
    if (params != NULL) {
        ast_add_child(node, params);
    }
    if (return_type != NULL) {
        ast_add_child(node, return_type);
    }
    return node;
}

AstNode *ast_make_subprogram(AstNode *head, AstNode *body, AstLocation loc) {
    AstNode *node = ast_new(AST_SUBPROGRAM, loc);
    ast_add_child(node, head);
    ast_add_child(node, body);
    return node;
}

AstNode *ast_make_param_group(bool by_ref, AstNode *ids, AstNode *type, AstLocation loc) {
    AstNode *node = ast_new(AST_PARAM_GROUP, loc);
    node->flag = by_ref;
    ast_add_child(node, ids);
    ast_add_child(node, type);
    return node;
}

AstNode *ast_make_compound_stmt(AstNode *statements, AstLocation loc) {
    AstNode *node = ast_new(AST_COMPOUND_STMT, loc);
    ast_add_child(node, statements);
    return node;
}

AstNode *ast_make_empty_stmt(AstLocation loc) {
    return ast_new(AST_EMPTY_STMT, loc);
}

AstNode *ast_make_var_ref(const char *name, AstNode *indices, AstLocation loc) {
    AstNode *node = ast_new_text(AST_VAR_REF, loc, name);
    if (indices != NULL) {
        ast_add_child(node, indices);
    }
    return node;
}

AstNode *ast_make_call(AstKind kind, const char *name, AstNode *args, AstLocation loc) {
    AstNode *node = ast_new_text(kind, loc, name);
    if (args != NULL) {
        ast_add_child(node, args);
    }
    return node;
}

AstNode *ast_make_assign_stmt(AstNode *target, AstNode *expr, AstLocation loc) {
    AstNode *node = ast_new(AST_ASSIGN_STMT, loc);
    ast_add_child(node, target);
    ast_add_child(node, expr);
    return node;
}

AstNode *ast_make_if_stmt(AstNode *cond,
                          AstNode *then_stmt,
                          AstNode *else_stmt,
                          AstLocation loc) {
    AstNode *node = ast_new(AST_IF_STMT, loc);
    ast_add_child(node, cond);
    ast_add_child(node, then_stmt);
    if (else_stmt != NULL) {
        ast_add_child(node, else_stmt);
    }
    return node;
}

AstNode *ast_make_for_stmt(const char *name,
                           AstNode *start_expr,
                           AstNode *end_expr,
                           AstNode *body,
                           AstLocation loc) {
    AstNode *node = ast_new_text(AST_FOR_STMT, loc, name);
    ast_add_child(node, start_expr);
    ast_add_child(node, end_expr);
    ast_add_child(node, body);
    return node;
}

AstNode *ast_make_read_stmt(AstNode *vars, AstLocation loc) {
    AstNode *node = ast_new(AST_READ_STMT, loc);
    ast_add_child(node, vars);
    return node;
}

AstNode *ast_make_write_stmt(AstNode *exprs, AstLocation loc) {
    AstNode *node = ast_new(AST_WRITE_STMT, loc);
    ast_add_child(node, exprs);
    return node;
}

AstNode *ast_make_binary_expr(const char *op,
                              AstNode *lhs,
                              AstNode *rhs,
                              AstLocation loc) {
    AstNode *node = ast_new_text(AST_BINARY_EXPR, loc, op);
    ast_add_child(node, lhs);
    ast_add_child(node, rhs);
    return node;
}

AstNode *ast_make_unary_expr(const char *op, AstNode *operand, AstLocation loc) {
    AstNode *node = ast_new_text(AST_UNARY_EXPR, loc, op);
    ast_add_child(node, operand);
    return node;
}

const char *ast_kind_name(AstKind kind) {
    switch (kind) {
        case AST_PROGRAM: return "Program";
        case AST_PROGRAM_HEAD: return "ProgramHead";
        case AST_BLOCK: return "Block";
        case AST_IDENTIFIER: return "Identifier";
        case AST_IDENTIFIER_LIST: return "IdentifierList";
        case AST_CONST_DECL: return "ConstDecl";
        case AST_CONST_DECL_LIST: return "ConstDeclList";
        case AST_VAR_DECL: return "VarDecl";
        case AST_VAR_DECL_LIST: return "VarDeclList";
        case AST_BASIC_TYPE: return "BasicType";
        case AST_ARRAY_TYPE: return "ArrayType";
        case AST_PERIOD: return "Period";
        case AST_PERIOD_LIST: return "PeriodList";
        case AST_SUBPROGRAM: return "Subprogram";
        case AST_SUBPROGRAM_LIST: return "SubprogramList";
        case AST_PROCEDURE_HEAD: return "ProcedureHead";
        case AST_FUNCTION_HEAD: return "FunctionHead";
        case AST_PARAM_GROUP: return "ParamGroup";
        case AST_PARAM_LIST: return "ParamList";
        case AST_COMPOUND_STMT: return "CompoundStmt";
        case AST_STATEMENT_LIST: return "StatementList";
        case AST_EMPTY_STMT: return "EmptyStmt";
        case AST_ASSIGN_STMT: return "AssignStmt";
        case AST_CALL_STMT: return "CallStmt";
        case AST_CALL_EXPR: return "CallExpr";
        case AST_IF_STMT: return "IfStmt";
        case AST_FOR_STMT: return "ForStmt";
        case AST_READ_STMT: return "ReadStmt";
        case AST_WRITE_STMT: return "WriteStmt";
        case AST_VAR_REF: return "VarRef";
        case AST_VARIABLE_LIST: return "VariableList";
        case AST_EXPRESSION_LIST: return "ExpressionList";
        case AST_BINARY_EXPR: return "BinaryExpr";
        case AST_UNARY_EXPR: return "UnaryExpr";
        case AST_INT_LITERAL: return "IntLiteral";
        case AST_REAL_LITERAL: return "RealLiteral";
        case AST_CHAR_LITERAL: return "CharLiteral";
        default: return "Unknown";
    }
}

void ast_dump(FILE *out, const AstNode *node, int indent) {
    ast_dump_impl(out, node, indent);
}

bool ast_validate(FILE *out, const AstNode *node) {
    bool ok = true;
    size_t child_count;

    if (node == NULL) {
        std::fprintf(out, "AST validation error: root is null\n");
        return false;
    }

    child_count = node->children.size();

    switch (node->kind) {
        case AST_PROGRAM:
            ok = (child_count == 2);
            break;
        case AST_PROGRAM_HEAD:
            ok = (child_count <= 1) && !node->text.empty();
            break;
        case AST_BLOCK:
            ok = (child_count == 4);
            break;
        case AST_CONST_DECL:
            ok = (child_count == 1) && !node->text.empty();
            break;
        case AST_VAR_DECL:
        case AST_ARRAY_TYPE:
        case AST_SUBPROGRAM:
        case AST_PARAM_GROUP:
        case AST_ASSIGN_STMT:
        case AST_BINARY_EXPR:
            ok = (child_count == 2);
            break;
        case AST_PROCEDURE_HEAD:
            ok = (child_count == 1) && !node->text.empty();
            break;
        case AST_FUNCTION_HEAD:
            ok = (child_count == 2) && !node->text.empty();
            break;
        case AST_COMPOUND_STMT:
        case AST_READ_STMT:
        case AST_WRITE_STMT:
            ok = (child_count == 1);
            break;
        case AST_EMPTY_STMT:
        case AST_INT_LITERAL:
        case AST_REAL_LITERAL:
        case AST_CHAR_LITERAL:
        case AST_IDENTIFIER:
        case AST_BASIC_TYPE:
        case AST_PERIOD:
            ok = (child_count == 0);
            break;
        case AST_CALL_STMT:
        case AST_CALL_EXPR:
        case AST_VAR_REF:
            ok = (child_count <= 1) && !node->text.empty();
            break;
        case AST_IF_STMT:
            ok = (child_count == 2 || child_count == 3);
            break;
        case AST_FOR_STMT:
            ok = (child_count == 3) && !node->text.empty();
            break;
        case AST_UNARY_EXPR:
            ok = (child_count == 1) && !node->text.empty();
            break;
        case AST_IDENTIFIER_LIST:
        case AST_CONST_DECL_LIST:
        case AST_VAR_DECL_LIST:
        case AST_PERIOD_LIST:
        case AST_SUBPROGRAM_LIST:
        case AST_PARAM_LIST:
        case AST_STATEMENT_LIST:
        case AST_VARIABLE_LIST:
        case AST_EXPRESSION_LIST:
            ok = true;
            break;
        default:
            ok = false;
            break;
    }

    if (!ok) {
        std::fprintf(out,
                     "AST validation error: %s has %zu child(ren) at %d:%d\n",
                     ast_kind_name(node->kind),
                     child_count,
                     node->loc.first_line,
                     node->loc.first_column);
        return false;
    }

    for (std::vector<AstNode *>::const_iterator it = node->children.begin();
         it != node->children.end();
         ++it) {
        if (!ast_validate(out, *it)) {
            return false;
        }
    }
    return true;
}

void ast_free(AstNode *node) {
    if (node == NULL) {
        return;
    }
    for (std::vector<AstNode *>::iterator it = node->children.begin();
         it != node->children.end();
         ++it) {
        ast_free(*it);
    }
    delete node;
}
