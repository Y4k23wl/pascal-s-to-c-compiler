#pragma once

#include <cstdio>

#include "ast.hpp"

extern AstNode *g_ast_root;

AstNode *pascal_s_get_ast_root(void);
AstNode *parse_pascal_stream(FILE *input);
AstNode *parse_pascal_file(const char *path);
bool pascal_s_had_lexical_error(void);
int pascal_s_lexical_error_count(void);
bool pascal_s_had_syntax_error(void);
int pascal_s_syntax_error_count(void);
