#pragma once

#include <cstdio>
#include <string>
#include <vector>

struct AstLocation {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};

enum AstKind {
    AST_PROGRAM,
    AST_PROGRAM_HEAD,
    AST_BLOCK,
    AST_IDENTIFIER,
    AST_IDENTIFIER_LIST,
    AST_CONST_DECL,
    AST_CONST_DECL_LIST,
    AST_VAR_DECL,
    AST_VAR_DECL_LIST,
    AST_BASIC_TYPE,
    AST_ARRAY_TYPE,
    AST_PERIOD,
    AST_PERIOD_LIST,
    AST_SUBPROGRAM,
    AST_SUBPROGRAM_LIST,
    AST_PROCEDURE_HEAD,
    AST_FUNCTION_HEAD,
    AST_PARAM_GROUP,
    AST_PARAM_LIST,
    AST_COMPOUND_STMT,
    AST_STATEMENT_LIST,
    AST_EMPTY_STMT,
    AST_ASSIGN_STMT,
    AST_CALL_STMT,
    AST_CALL_EXPR,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FOR_STMT,
    AST_READ_STMT,
    AST_WRITE_STMT,
    AST_VAR_REF,
    AST_VARIABLE_LIST,
    AST_EXPRESSION_LIST,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_BOOL_LITERAL,
    AST_INT_LITERAL,
    AST_REAL_LITERAL,
    AST_CHAR_LITERAL,
    AST_STRING_LITERAL,
    AST_BREAK_STMT
};

struct AstNode {
    AstKind kind;
    AstLocation loc;
    std::string text;
    long long int_value;
    long long second_int_value;
    double real_value;
    bool flag;
    std::vector<AstNode *> children;
};

AstLocation ast_make_location(int first_line,
                              int first_column,
                              int last_line,
                              int last_column);

AstNode *ast_new(AstKind kind, AstLocation loc);
AstNode *ast_new_text(AstKind kind, AstLocation loc, const char *text);
AstNode *ast_new_int(AstKind kind, AstLocation loc, long long value);
AstNode *ast_new_real(AstKind kind, AstLocation loc, double value);

AstNode *ast_add_child(AstNode *parent, AstNode *child);
AstNode *ast_append_list(AstNode *list, AstNode *item);

AstNode *ast_make_identifier(const char *name, AstLocation loc);
AstNode *ast_make_identifier_list(AstNode *first, AstLocation loc);
AstNode *ast_make_basic_type(const char *name, AstLocation loc);
AstNode *ast_make_const_decl(const char *name, AstNode *value, AstLocation loc);
AstNode *ast_make_var_decl(AstNode *ids, AstNode *type, AstLocation loc);
AstNode *ast_make_period(int low, int high, AstLocation loc);
AstNode *ast_make_array_type(AstNode *periods, AstNode *base_type, AstLocation loc);
AstNode *ast_make_program_head(const char *name, AstNode *ids, AstLocation loc);
AstNode *ast_make_block(AstNode *consts,
                        AstNode *vars,
                        AstNode *subprograms,
                        AstNode *compound_stmt,
                        AstLocation loc);
AstNode *ast_make_program(AstNode *head, AstNode *body, AstLocation loc);
AstNode *ast_make_subprogram_head(bool is_function,
                                  const char *name,
                                  AstNode *params,
                                  AstNode *return_type,
                                  AstLocation loc);
AstNode *ast_make_subprogram(AstNode *head, AstNode *body, AstLocation loc);
AstNode *ast_make_param_group(bool by_ref, AstNode *ids, AstNode *type, AstLocation loc);
AstNode *ast_make_compound_stmt(AstNode *statements, AstLocation loc);
AstNode *ast_make_empty_stmt(AstLocation loc);
AstNode *ast_make_break_stmt(AstLocation loc);
AstNode *ast_make_bool_literal(bool value, AstLocation loc);
AstNode *ast_make_var_ref(const char *name, AstNode *indices, AstLocation loc);
AstNode *ast_make_call(AstKind kind, const char *name, AstNode *args, AstLocation loc);
AstNode *ast_make_assign_stmt(AstNode *target, AstNode *expr, AstLocation loc);
AstNode *ast_make_if_stmt(AstNode *cond,
                          AstNode *then_stmt,
                          AstNode *else_stmt,
                          AstLocation loc);
AstNode *ast_make_while_stmt(AstNode *cond, AstNode *body, AstLocation loc);
AstNode *ast_make_for_stmt(const char *name,
                           AstNode *start_expr,
                           AstNode *end_expr,
                           AstNode *body,
                           AstLocation loc);
AstNode *ast_make_read_stmt(AstNode *vars, AstLocation loc);
AstNode *ast_make_write_stmt(AstNode *exprs, AstLocation loc);
AstNode *ast_make_binary_expr(const char *op,
                              AstNode *lhs,
                              AstNode *rhs,
                              AstLocation loc);
AstNode *ast_make_unary_expr(const char *op, AstNode *operand, AstLocation loc);

const char *ast_kind_name(AstKind kind);
void ast_dump(FILE *out, const AstNode *node, int indent);
bool ast_validate(FILE *out, const AstNode *node);
void ast_free(AstNode *node);
