%option noyywrap nodefault yylineno caseless

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pascal_s_parser.tab.h"

#define MAX_ID_LEN 8

static int g_line = 1;
static int g_col = 1;

static void mark_token_start(void) {
    yylloc.first_line = g_line;
    yylloc.first_column = g_col;
}

static void advance_position(const char *text) {
    const unsigned char *p = (const unsigned char *)text;
    while (*p != '\0') {
        if (*p == '\n') {
            g_line += 1;
            g_col = 1;
        } else {
            g_col += 1;
        }
        ++p;
    }
    yylloc.last_line = g_line;
    yylloc.last_column = g_col;
}

static char *dup_text(const char *s) {
    size_t n = strlen(s);
    char *p = (char *)malloc(n + 1);
    if (p == NULL) {
        fprintf(stderr, "out of memory while duplicating token text\n");
        exit(EXIT_FAILURE);
    }
    memcpy(p, s, n + 1);
    return p;
}

static char *normalize_id(const char *src) {
    size_t n = strlen(src);
    size_t m = n > MAX_ID_LEN ? MAX_ID_LEN : n;
    char *p = (char *)malloc(m + 1);
    size_t i;
    if (p == NULL) {
        fprintf(stderr, "out of memory while normalizing identifier\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < m; ++i) {
        p[i] = (char)tolower((unsigned char)src[i]);
    }
    p[m] = '\0';
    return p;
}

#define RETURN_SIMPLE_TOKEN(tok) \
    do { \
        mark_token_start(); \
        advance_position(yytext); \
        return (tok); \
    } while (0)

%}

%x COMMENT

DIGIT          [0-9]
ID_START       [A-Za-z]
ID_CHAR        [A-Za-z0-9]
INT            {DIGIT}+
EXP            [eE][+-]?{DIGIT}+
REAL1          {DIGIT}+\.{DIGIT}+({EXP})?
REAL2          {DIGIT}+{EXP}
CHAR_LIT       '([^\\'\n]|\\[nrt'\\])'
BAD_CHAR_LIT   '[^'\n]*\n

%%

[ \t\r]+                   { advance_position(yytext); }
\n+                         { advance_position(yytext); }

"{"                         { BEGIN(COMMENT); advance_position(yytext); }
<COMMENT>[^\n}]+            { advance_position(yytext); }
<COMMENT>\n                 { advance_position(yytext); }
<COMMENT>"}"                { BEGIN(INITIAL); advance_position(yytext); }
<COMMENT><<EOF>>             {
                                fprintf(stderr,
                                        "[词法错误] 行：%d，列：%d - 未闭合注释\n",
                                        g_line,
                                        g_col);
                                return 0;
                             }

":="                        { RETURN_SIMPLE_TOKEN(ASSIGN); }
"<="                        { RETURN_SIMPLE_TOKEN(LE); }
">="                        { RETURN_SIMPLE_TOKEN(GE); }
"<>"                        { RETURN_SIMPLE_TOKEN(NE); }
".."                        { RETURN_SIMPLE_TOKEN(RANGE); }

"="                         { RETURN_SIMPLE_TOKEN(EQ); }
"<"                         { RETURN_SIMPLE_TOKEN(LT); }
">"                         { RETURN_SIMPLE_TOKEN(GT); }
"+"                         { RETURN_SIMPLE_TOKEN(PLUS); }
"-"                         { RETURN_SIMPLE_TOKEN(MINUS); }
"*"                         { RETURN_SIMPLE_TOKEN(MUL); }
"/"                         { RETURN_SIMPLE_TOKEN(SLASH); }
";"                         { RETURN_SIMPLE_TOKEN(SEMICOLON); }
"."                         { RETURN_SIMPLE_TOKEN(DOT); }
","                         { RETURN_SIMPLE_TOKEN(COMMA); }
"("                         { RETURN_SIMPLE_TOKEN(LPAREN); }
")"                         { RETURN_SIMPLE_TOKEN(RPAREN); }
"["                         { RETURN_SIMPLE_TOKEN(LBRACK); }
"]"                         { RETURN_SIMPLE_TOKEN(RBRACK); }
":"                         { RETURN_SIMPLE_TOKEN(COLON); }

"program"                   { RETURN_SIMPLE_TOKEN(PROGRAM); }
"const"                     { RETURN_SIMPLE_TOKEN(CONST); }
"var"                       { RETURN_SIMPLE_TOKEN(VAR); }
"procedure"                 { RETURN_SIMPLE_TOKEN(PROCEDURE); }
"function"                  { RETURN_SIMPLE_TOKEN(FUNCTION); }
"begin"                     { RETURN_SIMPLE_TOKEN(BEGIN_KW); }
"end"                       { RETURN_SIMPLE_TOKEN(END_KW); }
"if"                        { RETURN_SIMPLE_TOKEN(IF); }
"then"                      { RETURN_SIMPLE_TOKEN(THEN); }
"else"                      { RETURN_SIMPLE_TOKEN(ELSE); }
"for"                       { RETURN_SIMPLE_TOKEN(FOR); }
"to"                        { RETURN_SIMPLE_TOKEN(TO); }
"do"                        { RETURN_SIMPLE_TOKEN(DO); }
"read"                      { RETURN_SIMPLE_TOKEN(READ); }
"write"                     { RETURN_SIMPLE_TOKEN(WRITE); }
"array"                     { RETURN_SIMPLE_TOKEN(ARRAY); }
"of"                        { RETURN_SIMPLE_TOKEN(OF); }
"integer"                   { RETURN_SIMPLE_TOKEN(INTEGER); }
"real"                      { RETURN_SIMPLE_TOKEN(REAL); }
"boolean"                   { RETURN_SIMPLE_TOKEN(BOOLEAN); }
"char"                      { RETURN_SIMPLE_TOKEN(CHAR); }
"not"                       { RETURN_SIMPLE_TOKEN(NOT); }
"div"                       { RETURN_SIMPLE_TOKEN(DIV); }
"mod"                       { RETURN_SIMPLE_TOKEN(MOD); }
"and"                       { RETURN_SIMPLE_TOKEN(AND); }
"or"                        { RETURN_SIMPLE_TOKEN(OR); }

{REAL1}|{REAL2}              {
                                mark_token_start();
                                yylval.fval = strtod(yytext, NULL);
                                advance_position(yytext);
                                return REAL_CONST;
                             }

{INT}                        {
                                mark_token_start();
                                yylval.ival = (int)strtol(yytext, NULL, 10);
                                advance_position(yytext);
                                return INT_CONST;
                             }

{CHAR_LIT}                   {
                                mark_token_start();
                                yylval.sval = dup_text(yytext);
                                advance_position(yytext);
                                return CHAR_CONST;
                             }

{BAD_CHAR_LIT}               {
                                fprintf(stderr,
                                        "[词法错误] 行：%d，列：%d - 未闭合字符常量\n",
                                        g_line,
                                        g_col);
                                advance_position(yytext);
                             }

{ID_START}{ID_CHAR}*         {
                                mark_token_start();
                                yylval.sval = normalize_id(yytext);
                                advance_position(yytext);
                                return ID;
                             }

{DIGIT}+{ID_START}{ID_CHAR}* {
                                fprintf(stderr,
                                        "[词法错误] 行：%d，列：%d - 非法标识符：%s（以数字开头）\n",
                                        g_line,
                                        g_col,
                                        yytext);
                                advance_position(yytext);
                             }

<<EOF>>                      { return 0; }

.                            {
                                fprintf(stderr,
                                        "[词法错误] 行：%d，列：%d - 非法字符：%s\n",
                                        g_line,
                                        g_col,
                                        yytext);
                                advance_position(yytext);
                             }

%%
