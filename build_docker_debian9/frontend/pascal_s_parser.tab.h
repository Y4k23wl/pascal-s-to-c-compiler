/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_WORK_BUILD_DOCKER_DEBIAN9_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED
# define YY_YY_WORK_BUILD_DOCKER_DEBIAN9_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    CONST = 259,
    VAR = 260,
    PROCEDURE = 261,
    FUNCTION = 262,
    BEGIN_KW = 263,
    END_KW = 264,
    IF = 265,
    THEN = 266,
    ELSE = 267,
    FOR = 268,
    TO = 269,
    DO = 270,
    WHILE = 271,
    BREAK = 272,
    READ = 273,
    WRITE = 274,
    ARRAY = 275,
    OF = 276,
    INTEGER = 277,
    REAL = 278,
    BOOLEAN = 279,
    CHAR = 280,
    NOT = 281,
    TRUE = 282,
    FALSE = 283,
    DIV = 284,
    MOD = 285,
    AND = 286,
    OR = 287,
    ID = 288,
    INT_CONST = 289,
    REAL_CONST = 290,
    CHAR_CONST = 291,
    STRING_CONST = 292,
    ASSIGN = 293,
    EQ = 294,
    NE = 295,
    LT = 296,
    LE = 297,
    GT = 298,
    GE = 299,
    PLUS = 300,
    MINUS = 301,
    MUL = 302,
    SLASH = 303,
    SEMICOLON = 304,
    DOT = 305,
    COMMA = 306,
    LPAREN = 307,
    RPAREN = 308,
    LBRACK = 309,
    RBRACK = 310,
    COLON = 311,
    RANGE = 312,
    LOWER_THAN_ELSE = 313,
    UMINUS = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 61 "/work/frontend/pascal_s_parser.y" /* yacc.c:1909  */

    char *sval;
    int ival;
    double fval;
    struct AstNode *node;

#line 121 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_WORK_BUILD_DOCKER_DEBIAN9_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED  */
