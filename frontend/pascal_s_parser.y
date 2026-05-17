%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.hpp"

int yylex(void);
void yyerror(const char *msg);
void yyrestart(FILE *input_file);
void lexer_reset_position(void);
int lexer_had_error(void);
int lexer_error_count(void);
int lexer_scan_terminated_early(void);

AstNode *g_ast_root = NULL;
static int g_parse_failed = 0;
static int g_parse_error_count = 0;
static int g_parse_error_limit_hit = 0;
static int g_parse_stop_requested = 0;
static const int kMaxParseErrors = 20;

static char *dup_text(const char *text) {
    size_t len = strlen(text);
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        fprintf(stderr, "out of memory while duplicating parser text\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copy, text, len + 1);
    return copy;
}

#define AST_LOC(loc) \
    ast_make_location((loc).first_line, (loc).first_column, (loc).last_line, (loc).last_column)

static void parser_note_at(int line, int col, const char *stage, const char *msg) {
    fprintf(stderr, "[%s] 行：%d，列：%d - %s\n", stage, line, col, msg);
}

/*
 * This file is a parser-side contract for the Flex group.
 *
 * Assumptions used to make the grammar practical in Bison:
 * 1. The original RTF line wraps are normalized into sequential symbols.
 * 2. `e` becomes an empty production.
 * 3. `func_id assignop expression` is merged into the normal assignment
 *    production to avoid a reduce/reduce overlap with `variable`.
 *    The "function name can be assigned inside its own body" rule should be
 *    checked during semantic analysis, not lexical analysis.
 * 4. `assignop`, `relop`, `addop`, and `mulop` are expanded into concrete
 *    tokens below.
 * 5. Character constants are exposed as `CHAR_CONST` instead of the literal
 *    `' letter '` pattern from the original document.
 */
%}

%error-verbose
%locations

%union {
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}

%start programstruct
%expect 2

/* Keywords */
%token PROGRAM CONST VAR PROCEDURE FUNCTION
%token BEGIN_KW END_KW
%token IF THEN ELSE
%token FOR TO DO WHILE BREAK
%token READ WRITE
%token ARRAY OF
%token INTEGER REAL BOOLEAN CHAR
%token NOT TRUE FALSE
%token DIV MOD AND OR

/* Identifiers and constants */
%token <sval> ID
%token <ival> INT_CONST
%token <fval> REAL_CONST
%token <sval> CHAR_CONST
%token <sval> STRING_CONST

/* Operators and delimiters */
%token ASSIGN      /* := */
%token EQ          /* =  */
%token NE          /* <> */
%token LT          /* <  */
%token LE          /* <= */
%token GT          /* >  */
%token GE          /* >= */
%token PLUS        /* +  */
%token MINUS       /* -  */
%token MUL         /* *  */
%token SLASH       /* /  */
%token SEMICOLON   /* ;  */
%token DOT         /* .  */
%token COMMA       /* ,  */
%token LPAREN      /* (  */
%token RPAREN      /* )  */
%token LBRACK      /* [  */
%token RBRACK      /* ]  */
%token COLON       /* :  */
%token RANGE       /* .. */

%type <node> programstruct
%type <node> program_head program_body
%type <node> idlist
%type <node> const_declarations const_declaration const_value
%type <node> var_declarations var_declaration
%type <node> type basic_type period
%type <ival> digits
%type <node> subprogram_declarations subprogram subprogram_head
%type <node> formal_parameter parameter_list parameter var_parameter value_parameter
%type <node> subprogram_body
%type <node> compound_statement statement_list statement
%type <node> variable_list variable id_varpart procedure_call expression_list
%type <node> expression simple_expression term factor num
%type <sval> relop addop mulop

/* Precedence helpers */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc EQ NE LT LE GT GE
%left OR PLUS MINUS
%left AND MUL SLASH DIV MOD
%right NOT UMINUS

%%

programstruct
    : program_head SEMICOLON program_body DOT
      {
          $$ = ast_make_program($1, $3, AST_LOC(@$));
          g_ast_root = $$;
      }
    ;

program_head
    : PROGRAM ID LPAREN idlist RPAREN
      {
          $$ = ast_make_program_head($2, $4, AST_LOC(@$));
          free($2);
      }
    | PROGRAM ID
      {
          $$ = ast_make_program_head($2, NULL, AST_LOC(@$));
          free($2);
      }
    ;

program_body
    : const_declarations var_declarations subprogram_declarations compound_statement
      {
          $$ = ast_make_block($1, $2, $3, $4, AST_LOC(@$));
      }
    ;

idlist
    : ID
      {
          $$ = ast_make_identifier_list(ast_make_identifier($1, AST_LOC(@1)), AST_LOC(@$));
          free($1);
      }
    | idlist COMMA ID
      {
          $$ = ast_append_list($1, ast_make_identifier($3, AST_LOC(@3)));
          free($3);
      }
    ;

const_declarations
    : /* empty */
      {
          $$ = ast_new(AST_CONST_DECL_LIST, AST_LOC(@$));
      }
    | CONST const_declaration SEMICOLON
      {
          $$ = $2;
      }
    ;

const_declaration
    : ID EQ const_value
      {
          $$ = ast_new(AST_CONST_DECL_LIST, AST_LOC(@$));
          ast_append_list($$, ast_make_const_decl($1, $3, AST_LOC(@$)));
          free($1);
      }
    | const_declaration SEMICOLON ID EQ const_value
      {
          $$ = ast_append_list($1, ast_make_const_decl($3, $5, AST_LOC(@3)));
          free($3);
      }
    ;

const_value
    : PLUS num
      {
          $$ = $2;
      }
    | MINUS num
      {
          $$ = ast_make_unary_expr("-", $2, AST_LOC(@$));
      }
    | num
      {
          $$ = $1;
      }
    | CHAR_CONST
      {
          $$ = ast_new_text(AST_CHAR_LITERAL, AST_LOC(@1), $1);
          free($1);
      }
    | STRING_CONST
      {
          $$ = ast_new_text(AST_STRING_LITERAL, AST_LOC(@1), $1);
          free($1);
      }
    | TRUE
      {
          $$ = ast_make_bool_literal(true, AST_LOC(@1));
      }
    | FALSE
      {
          $$ = ast_make_bool_literal(false, AST_LOC(@1));
      }
    ;

var_declarations
    : /* empty */
      {
          $$ = ast_new(AST_VAR_DECL_LIST, AST_LOC(@$));
      }
    | VAR var_declaration SEMICOLON
      {
          $$ = $2;
      }
    ;

var_declaration
    : idlist COLON type
      {
          $$ = ast_new(AST_VAR_DECL_LIST, AST_LOC(@$));
          ast_append_list($$, ast_make_var_decl($1, $3, AST_LOC(@$)));
      }
    | var_declaration SEMICOLON idlist COLON type
      {
          $$ = ast_append_list($1, ast_make_var_decl($3, $5, AST_LOC(@3)));
      }
    ;

type
    : basic_type
      {
          $$ = $1;
      }
    | ARRAY LBRACK period RBRACK OF basic_type
      {
          $$ = ast_make_array_type($3, $6, AST_LOC(@$));
      }
    ;

basic_type
    : INTEGER
      {
          $$ = ast_make_basic_type("integer", AST_LOC(@1));
      }
    | REAL
      {
          $$ = ast_make_basic_type("real", AST_LOC(@1));
      }
    | BOOLEAN
      {
          $$ = ast_make_basic_type("boolean", AST_LOC(@1));
      }
    | CHAR
      {
          $$ = ast_make_basic_type("char", AST_LOC(@1));
      }
    ;

period
    : digits RANGE digits
      {
          $$ = ast_new(AST_PERIOD_LIST, AST_LOC(@$));
          ast_append_list($$, ast_make_period($1, $3, AST_LOC(@$)));
      }
    | period COMMA digits RANGE digits
      {
          $$ = ast_append_list($1, ast_make_period($3, $5, AST_LOC(@3)));
      }
    ;

digits
    : INT_CONST
      {
          $$ = $1;
      }
    ;

subprogram_declarations
    : /* empty */
      {
          $$ = ast_new(AST_SUBPROGRAM_LIST, AST_LOC(@$));
      }
    | subprogram_declarations subprogram SEMICOLON
      {
          $$ = ast_append_list($1, $2);
      }
    ;

subprogram
    : subprogram_head SEMICOLON subprogram_body
      {
          $$ = ast_make_subprogram($1, $3, AST_LOC(@$));
      }
    ;

subprogram_head
    : PROCEDURE ID formal_parameter
      {
          $$ = ast_make_subprogram_head(false, $2, $3, NULL, AST_LOC(@$));
          free($2);
      }
    | FUNCTION ID formal_parameter COLON basic_type
      {
          $$ = ast_make_subprogram_head(true, $2, $3, $5, AST_LOC(@$));
          free($2);
      }
    ;

formal_parameter
    : /* empty */
      {
          $$ = ast_new(AST_PARAM_LIST, AST_LOC(@$));
      }
    | LPAREN RPAREN
      {
          $$ = ast_new(AST_PARAM_LIST, AST_LOC(@$));
      }
    | LPAREN parameter_list RPAREN
      {
          $$ = $2;
      }
    | LPAREN error RPAREN
      {
          parser_note_at(@2.first_line,
                         @2.first_column,
                         "语法恢复",
                         "形参列表存在语法错误，已恢复到右括号");
          yyerrok;
          $$ = ast_new(AST_PARAM_LIST, AST_LOC(@$));
      }
    ;

parameter_list
    : parameter
      {
          $$ = ast_new(AST_PARAM_LIST, AST_LOC(@$));
          ast_append_list($$, $1);
      }
    | parameter_list SEMICOLON parameter
      {
          $$ = ast_append_list($1, $3);
      }
    ;

parameter
    : var_parameter
      {
          $$ = $1;
      }
    | value_parameter
      {
          $$ = $1;
      }
    ;

var_parameter
    : VAR value_parameter
      {
          $2->flag = true;
          $2->loc = AST_LOC(@$);
          $$ = $2;
      }
    ;

value_parameter
    : idlist COLON basic_type
      {
          $$ = ast_make_param_group(false, $1, $3, AST_LOC(@$));
      }
    ;

subprogram_body
    : const_declarations var_declarations compound_statement
      {
          $$ = ast_make_block($1, $2, ast_new(AST_SUBPROGRAM_LIST, AST_LOC(@$)), $3, AST_LOC(@$));
      }
    ;

compound_statement
    : BEGIN_KW statement_list END_KW
      {
          $$ = ast_make_compound_stmt($2, AST_LOC(@$));
      }
    | BEGIN_KW error END_KW
      {
          parser_note_at(@2.first_line,
                         @2.first_column,
                         "语法恢复",
                         "复合语句内部存在语法错误，已恢复到 end");
          yyerrok;
          $$ = ast_make_compound_stmt(ast_new(AST_STATEMENT_LIST, AST_LOC(@$)), AST_LOC(@$));
      }
    ;

statement_list
    : statement
      {
          $$ = ast_new(AST_STATEMENT_LIST, AST_LOC(@$));
          ast_append_list($$, $1);
      }
    | statement_list SEMICOLON statement
      {
          $$ = ast_append_list($1, $3);
      }
    | statement_list SEMICOLON error
      {
          parser_note_at(@3.first_line,
                         @3.first_column,
                         "语法恢复",
                         "语句存在语法错误，已跳过到下一个分号或 end 后继续");
          $$ = $1;
      }
    | statement_list error statement
      {
          parser_note_at(@2.first_line,
                         @2.first_column,
                         "语法恢复",
                         "语句之间可能缺少分号，已恢复并继续");
          yyerrok;
          $$ = ast_append_list($1, $3);
      }
    ;

statement
    : /* empty */
      {
          $$ = ast_make_empty_stmt(AST_LOC(@$));
      }
    | variable ASSIGN expression
      {
          $$ = ast_make_assign_stmt($1, $3, AST_LOC(@$));
      }
    | procedure_call
      {
          $$ = $1;
      }
    | BREAK
      {
          $$ = ast_make_break_stmt(AST_LOC(@1));
      }
    | compound_statement
      {
          $$ = $1;
      }
    | IF expression THEN statement %prec LOWER_THAN_ELSE
      {
          $$ = ast_make_if_stmt($2, $4, NULL, AST_LOC(@$));
      }
    | IF expression THEN statement ELSE statement
      {
          $$ = ast_make_if_stmt($2, $4, $6, AST_LOC(@$));
      }
    | WHILE expression DO statement
      {
          $$ = ast_make_while_stmt($2, $4, AST_LOC(@$));
      }
    | FOR ID ASSIGN expression TO expression DO statement
      {
          $$ = ast_make_for_stmt($2, $4, $6, $8, AST_LOC(@$));
          free($2);
      }
    | READ LPAREN variable_list RPAREN
      {
          $$ = ast_make_read_stmt($3, AST_LOC(@$));
      }
    | READ LPAREN error RPAREN
      {
          parser_note_at(@3.first_line,
                         @3.first_column,
                         "语法恢复",
                         "read 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          $$ = ast_make_read_stmt(ast_new(AST_VARIABLE_LIST, AST_LOC(@$)), AST_LOC(@$));
      }
    | WRITE LPAREN expression_list RPAREN
      {
          $$ = ast_make_write_stmt($3, AST_LOC(@$));
      }
    | WRITE LPAREN error RPAREN
      {
          parser_note_at(@3.first_line,
                         @3.first_column,
                         "语法恢复",
                         "write 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          $$ = ast_make_write_stmt(ast_new(AST_EXPRESSION_LIST, AST_LOC(@$)), AST_LOC(@$));
      }
    ;

variable_list
    : variable
      {
          $$ = ast_new(AST_VARIABLE_LIST, AST_LOC(@$));
          ast_append_list($$, $1);
      }
    | variable_list COMMA variable
      {
          $$ = ast_append_list($1, $3);
      }
    ;

variable
    : ID id_varpart
      {
          $$ = ast_make_var_ref($1, $2, AST_LOC(@$));
          free($1);
      }
    ;

id_varpart
    : /* empty */
      {
          $$ = NULL;
      }
    | LBRACK expression_list RBRACK
      {
          $$ = $2;
      }
    | LBRACK error RBRACK
      {
          parser_note_at(@2.first_line,
                         @2.first_column,
                         "语法恢复",
                         "数组下标列表存在语法错误，已恢复到右中括号");
          yyerrok;
          $$ = ast_new(AST_EXPRESSION_LIST, AST_LOC(@$));
      }
    ;

procedure_call
    : ID
      {
          $$ = ast_make_call(AST_CALL_STMT, $1, NULL, AST_LOC(@$));
          free($1);
      }
    | ID LPAREN RPAREN
      {
          $$ = ast_make_call(AST_CALL_STMT, $1, NULL, AST_LOC(@$));
          free($1);
      }
    | ID LPAREN expression_list RPAREN
      {
          $$ = ast_make_call(AST_CALL_STMT, $1, $3, AST_LOC(@$));
          free($1);
      }
    | ID LPAREN error RPAREN
      {
          parser_note_at(@3.first_line,
                         @3.first_column,
                         "语法恢复",
                         "调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          $$ = ast_make_call(AST_CALL_STMT,
                             $1,
                             ast_new(AST_EXPRESSION_LIST, AST_LOC(@$)),
                             AST_LOC(@$));
          free($1);
      }
    ;

expression_list
    : expression
      {
          $$ = ast_new(AST_EXPRESSION_LIST, AST_LOC(@$));
          ast_append_list($$, $1);
      }
    | expression_list COMMA expression
      {
          $$ = ast_append_list($1, $3);
      }
    ;

expression
    : simple_expression
      {
          $$ = $1;
      }
    | simple_expression relop simple_expression
      {
          $$ = ast_make_binary_expr($2, $1, $3, AST_LOC(@$));
          free($2);
      }
    ;

simple_expression
    : term
      {
          $$ = $1;
      }
    | simple_expression addop term
      {
          $$ = ast_make_binary_expr($2, $1, $3, AST_LOC(@$));
          free($2);
      }
    ;

term
    : factor
      {
          $$ = $1;
      }
    | term mulop factor
      {
          $$ = ast_make_binary_expr($2, $1, $3, AST_LOC(@$));
          free($2);
      }
    ;

factor
    : num
      {
          $$ = $1;
      }
    | variable
      {
          $$ = $1;
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
    | ID LPAREN expression_list RPAREN
      {
          $$ = ast_make_call(AST_CALL_EXPR, $1, $3, AST_LOC(@$));
          free($1);
      }
    | ID LPAREN error RPAREN
      {
          parser_note_at(@3.first_line,
                         @3.first_column,
                         "语法恢复",
                         "函数调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          $$ = ast_make_call(AST_CALL_EXPR,
                             $1,
                             ast_new(AST_EXPRESSION_LIST, AST_LOC(@$)),
                             AST_LOC(@$));
          free($1);
      }
    | ID LPAREN RPAREN
      {
          $$ = ast_make_call(AST_CALL_EXPR, $1, NULL, AST_LOC(@$));
          free($1);
      }
    | TRUE
      {
          $$ = ast_make_bool_literal(true, AST_LOC(@1));
      }
    | FALSE
      {
          $$ = ast_make_bool_literal(false, AST_LOC(@1));
      }
    | STRING_CONST
      {
          $$ = ast_new_text(AST_STRING_LITERAL, AST_LOC(@1), $1);
          free($1);
      }
    | NOT factor
      {
          $$ = ast_make_unary_expr("not", $2, AST_LOC(@$));
      }
    | PLUS factor %prec UMINUS
      {
          $$ = ast_make_unary_expr("+", $2, AST_LOC(@$));
      }
    | MINUS factor %prec UMINUS
      {
          $$ = ast_make_unary_expr("-", $2, AST_LOC(@$));
      }
    ;

relop
    : EQ
      {
          $$ = dup_text("=");
      }
    | NE
      {
          $$ = dup_text("<>");
      }
    | LT
      {
          $$ = dup_text("<");
      }
    | LE
      {
          $$ = dup_text("<=");
      }
    | GT
      {
          $$ = dup_text(">");
      }
    | GE
      {
          $$ = dup_text(">=");
      }
    ;

addop
    : PLUS
      {
          $$ = dup_text("+");
      }
    | MINUS
      {
          $$ = dup_text("-");
      }
    | OR
      {
          $$ = dup_text("or");
      }
    ;

mulop
    : MUL
      {
          $$ = dup_text("*");
      }
    | SLASH
      {
          $$ = dup_text("/");
      }
    | DIV
      {
          $$ = dup_text("div");
      }
    | MOD
      {
          $$ = dup_text("mod");
      }
    | AND
      {
          $$ = dup_text("and");
      }
    ;

num
    : INT_CONST
      {
          $$ = ast_new_int(AST_INT_LITERAL, AST_LOC(@1), $1);
      }
    | REAL_CONST
      {
          $$ = ast_new_real(AST_REAL_LITERAL, AST_LOC(@1), $1);
      }
    ;

%%

void yyerror(const char *msg) {
    if (lexer_scan_terminated_early()) {
        g_parse_failed = 1;
        return;
    }

    g_parse_failed = 1;
    if (g_parse_error_limit_hit) {
        return;
    }

    g_parse_error_count += 1;
    parser_note_at(yylloc.first_line, yylloc.first_column, "语法错误", msg);

    if (g_parse_error_count >= kMaxParseErrors) {
        g_parse_error_limit_hit = 1;
        g_parse_stop_requested = 1;
        parser_note_at(yylloc.first_line,
                       yylloc.first_column,
                       "语法错误",
                       "语法错误过多，停止继续分析");
    }
}

int pascal_s_should_stop_scanning(void) {
    return g_parse_stop_requested;
}

AstNode *pascal_s_get_ast_root(void) {
    return g_ast_root;
}

AstNode *parse_pascal_stream(FILE *input) {
    g_parse_failed = 0;
    g_parse_error_count = 0;
    g_parse_error_limit_hit = 0;
    g_parse_stop_requested = 0;
    g_ast_root = NULL;
    lexer_reset_position();
    yyrestart(input);

    if (yyparse() != 0 || g_parse_failed) {
        ast_free(g_ast_root);
        g_ast_root = NULL;
    }
    return g_ast_root;
}

AstNode *parse_pascal_file(const char *path) {
    FILE *input = fopen(path, "r");
    AstNode *root;

    if (input == NULL) {
        perror(path);
        return NULL;
    }

    root = parse_pascal_stream(input);
    fclose(input);
    return root;
}

bool pascal_s_had_lexical_error(void) {
    return lexer_had_error() != 0;
}

int pascal_s_lexical_error_count(void) {
    return lexer_error_count();
}

bool pascal_s_had_syntax_error(void) {
    return g_parse_error_count > 0;
}

int pascal_s_syntax_error_count(void) {
    return g_parse_error_count;
}
