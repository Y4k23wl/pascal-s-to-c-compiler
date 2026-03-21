#pragma once

#include <cstdio>

#include "ast.hpp"

extern AstNode *g_ast_root;

AstNode *pascal_s_get_ast_root(void);
AstNode *parse_pascal_stream(FILE *input);
AstNode *parse_pascal_file(const char *path);
