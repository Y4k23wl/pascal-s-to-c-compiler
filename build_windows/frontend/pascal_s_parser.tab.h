/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_C_USERS_A_DESKTOP_PASCAL_S_TO_C_COMPILER_MAIN_BUILD_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED
# define YY_YY_C_USERS_A_DESKTOP_PASCAL_S_TO_C_COMPILER_MAIN_BUILD_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    CONST = 259,                   /* CONST  */
    VAR = 260,                     /* VAR  */
    PROCEDURE = 261,               /* PROCEDURE  */
    FUNCTION = 262,                /* FUNCTION  */
    BEGIN_KW = 263,                /* BEGIN_KW  */
    END_KW = 264,                  /* END_KW  */
    IF = 265,                      /* IF  */
    THEN = 266,                    /* THEN  */
    ELSE = 267,                    /* ELSE  */
    FOR = 268,                     /* FOR  */
    TO = 269,                      /* TO  */
    DO = 270,                      /* DO  */
    WHILE = 271,                   /* WHILE  */
    BREAK = 272,                   /* BREAK  */
    READ = 273,                    /* READ  */
    WRITE = 274,                   /* WRITE  */
    ARRAY = 275,                   /* ARRAY  */
    OF = 276,                      /* OF  */
    INTEGER = 277,                 /* INTEGER  */
    REAL = 278,                    /* REAL  */
    BOOLEAN = 279,                 /* BOOLEAN  */
    CHAR = 280,                    /* CHAR  */
    NOT = 281,                     /* NOT  */
    TRUE = 282,                    /* TRUE  */
    FALSE = 283,                   /* FALSE  */
    DIV = 284,                     /* DIV  */
    MOD = 285,                     /* MOD  */
    AND = 286,                     /* AND  */
    OR = 287,                      /* OR  */
    ID = 288,                      /* ID  */
    INT_CONST = 289,               /* INT_CONST  */
    REAL_CONST = 290,              /* REAL_CONST  */
    CHAR_CONST = 291,              /* CHAR_CONST  */
    STRING_CONST = 292,            /* STRING_CONST  */
    ASSIGN = 293,                  /* ASSIGN  */
    EQ = 294,                      /* EQ  */
    NE = 295,                      /* NE  */
    LT = 296,                      /* LT  */
    LE = 297,                      /* LE  */
    GT = 298,                      /* GT  */
    GE = 299,                      /* GE  */
    PLUS = 300,                    /* PLUS  */
    MINUS = 301,                   /* MINUS  */
    MUL = 302,                     /* MUL  */
    SLASH = 303,                   /* SLASH  */
    SEMICOLON = 304,               /* SEMICOLON  */
    DOT = 305,                     /* DOT  */
    COMMA = 306,                   /* COMMA  */
    LPAREN = 307,                  /* LPAREN  */
    RPAREN = 308,                  /* RPAREN  */
    LBRACK = 309,                  /* LBRACK  */
    RBRACK = 310,                  /* RBRACK  */
    COLON = 311,                   /* COLON  */
    RANGE = 312,                   /* RANGE  */
    LOWER_THAN_ELSE = 313,         /* LOWER_THAN_ELSE  */
    UMINUS = 314                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 61 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"

    char *sval;
    int ival;
    double fval;
    struct AstNode *node;

#line 130 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.h"

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


#endif /* !YY_YY_C_USERS_A_DESKTOP_PASCAL_S_TO_C_COMPILER_MAIN_BUILD_FRONTEND_PASCAL_S_PARSER_TAB_H_INCLUDED  */
