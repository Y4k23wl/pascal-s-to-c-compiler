/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     READ = 272,
     WRITE = 273,
     ARRAY = 274,
     OF = 275,
     INTEGER = 276,
     REAL = 277,
     BOOLEAN = 278,
     CHAR = 279,
     NOT = 280,
     TRUE = 281,
     FALSE = 282,
     DIV = 283,
     MOD = 284,
     AND = 285,
     OR = 286,
     ID = 287,
     INT_CONST = 288,
     REAL_CONST = 289,
     CHAR_CONST = 290,
     ASSIGN = 291,
     EQ = 292,
     NE = 293,
     LT = 294,
     LE = 295,
     GT = 296,
     GE = 297,
     PLUS = 298,
     MINUS = 299,
     MUL = 300,
     SLASH = 301,
     SEMICOLON = 302,
     DOT = 303,
     COMMA = 304,
     LPAREN = 305,
     RPAREN = 306,
     LBRACK = 307,
     RBRACK = 308,
     COLON = 309,
     RANGE = 310,
     LOWER_THAN_ELSE = 311,
     UMINUS = 312
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define CONST 259
#define VAR 260
#define PROCEDURE 261
#define FUNCTION 262
#define BEGIN_KW 263
#define END_KW 264
#define IF 265
#define THEN 266
#define ELSE 267
#define FOR 268
#define TO 269
#define DO 270
#define WHILE 271
#define READ 272
#define WRITE 273
#define ARRAY 274
#define OF 275
#define INTEGER 276
#define REAL 277
#define BOOLEAN 278
#define CHAR 279
#define NOT 280
#define TRUE 281
#define FALSE 282
#define DIV 283
#define MOD 284
#define AND 285
#define OR 286
#define ID 287
#define INT_CONST 288
#define REAL_CONST 289
#define CHAR_CONST 290
#define ASSIGN 291
#define EQ 292
#define NE 293
#define LT 294
#define LE 295
#define GT 296
#define GE 297
#define PLUS 298
#define MINUS 299
#define MUL 300
#define SLASH 301
#define SEMICOLON 302
#define DOT 303
#define COMMA 304
#define LPAREN 305
#define RPAREN 306
#define LBRACK 307
#define RBRACK 308
#define COLON 309
#define RANGE 310
#define LOWER_THAN_ELSE 311
#define UMINUS 312




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 61 "code/pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 1529 of yacc.c.  */
#line 170 "code/pascal_s_parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
