%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *msg);

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
}

%start programstruct

/* Keywords */
%token PROGRAM CONST VAR PROCEDURE FUNCTION
%token BEGIN_KW END_KW
%token IF THEN ELSE
%token FOR TO DO
%token READ WRITE
%token ARRAY OF
%token INTEGER REAL BOOLEAN CHAR
%token NOT
%token DIV MOD AND OR

/* Identifiers and constants */
%token <sval> ID
%token <ival> INT_CONST
%token <fval> REAL_CONST
%token <sval> CHAR_CONST

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
    ;

program_head
    : PROGRAM ID LPAREN idlist RPAREN
    | PROGRAM ID
    ;

program_body
    : const_declarations var_declarations subprogram_declarations compound_statement
    ;

idlist
    : ID
    | idlist COMMA ID
    ;

const_declarations
    : /* empty */
    | CONST const_declaration SEMICOLON
    ;

const_declaration
    : ID EQ const_value
    | const_declaration SEMICOLON ID EQ const_value
    ;

const_value
    : PLUS num
    | MINUS num
    | num
    | CHAR_CONST
    ;

var_declarations
    : /* empty */
    | VAR var_declaration SEMICOLON
    ;

var_declaration
    : idlist COLON type
    | var_declaration SEMICOLON idlist COLON type
    ;

type
    : basic_type
    | ARRAY LBRACK period RBRACK OF basic_type
    ;

basic_type
    : INTEGER
    | REAL
    | BOOLEAN
    | CHAR
    ;

period
    : digits RANGE digits
    | period COMMA digits RANGE digits
    ;

digits
    : INT_CONST
    ;

subprogram_declarations
    : /* empty */
    | subprogram_declarations subprogram SEMICOLON
    ;

subprogram
    : subprogram_head SEMICOLON subprogram_body
    ;

subprogram_head
    : PROCEDURE ID formal_parameter
    | FUNCTION ID formal_parameter COLON basic_type
    ;

formal_parameter
    : /* empty */
    | LPAREN parameter_list RPAREN
    ;

parameter_list
    : parameter
    | parameter_list SEMICOLON parameter
    ;

parameter
    : var_parameter
    | value_parameter
    ;

var_parameter
    : VAR value_parameter
    ;

value_parameter
    : idlist COLON basic_type
    ;

subprogram_body
    : const_declarations var_declarations compound_statement
    ;

compound_statement
    : BEGIN_KW statement_list END_KW
    ;

statement_list
    : statement
    | statement_list SEMICOLON statement
    ;

statement
    : /* empty */
    | variable assignop expression
    | procedure_call
    | compound_statement
    | IF expression THEN statement %prec LOWER_THAN_ELSE
    | IF expression THEN statement ELSE statement
    | FOR ID assignop expression TO expression DO statement
    | READ LPAREN variable_list RPAREN
    | WRITE LPAREN expression_list RPAREN
    ;

variable_list
    : variable
    | variable_list COMMA variable
    ;

variable
    : ID id_varpart
    ;

id_varpart
    : /* empty */
    | LBRACK expression_list RBRACK
    ;

procedure_call
    : ID
    | ID LPAREN expression_list RPAREN
    ;

expression_list
    : expression
    | expression_list COMMA expression
    ;

expression
    : simple_expression
    | simple_expression relop simple_expression
    ;

simple_expression
    : term
    | simple_expression addop term
    ;

term
    : factor
    | term mulop factor
    ;

factor
    : num
    | variable
    | LPAREN expression RPAREN
    | ID LPAREN expression_list RPAREN
    | NOT factor
    | MINUS factor %prec UMINUS
    ;

assignop
    : ASSIGN
    ;

relop
    : EQ
    | NE
    | LT
    | LE
    | GT
    | GE
    ;

addop
    : PLUS
    | MINUS
    | OR
    ;

mulop
    : MUL
    | SLASH
    | DIV
    | MOD
    | AND
    ;

num
    : INT_CONST
    | REAL_CONST
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "parse error at %d:%d: %s\n",
            yylloc.first_line,
            yylloc.first_column,
            msg);
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    return yyparse();
}
