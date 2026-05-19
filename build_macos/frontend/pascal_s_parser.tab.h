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
#define BREAK 272
#define READ 273
#define WRITE 274
#define ARRAY 275
#define OF 276
#define INTEGER 277
#define REAL 278
#define BOOLEAN 279
#define CHAR 280
#define NOT 281
#define TRUE 282
#define FALSE 283
#define DIV 284
#define MOD 285
#define AND 286
#define OR 287
#define ID 288
#define INT_CONST 289
#define REAL_CONST 290
#define CHAR_CONST 291
#define STRING_CONST 292
#define ASSIGN 293
#define EQ 294
#define NE 295
#define LT 296
#define LE 297
#define GT 298
#define GE 299
#define PLUS 300
#define MINUS 301
#define MUL 302
#define SLASH 303
#define SEMICOLON 304
#define DOT 305
#define COMMA 306
#define LPAREN 307
#define RPAREN 308
#define LBRACK 309
#define RBRACK 310
#define COLON 311
#define RANGE 312
#define LOWER_THAN_ELSE 313
#define UMINUS 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 61 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 1529 of yacc.c.  */
#line 174 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/build/frontend/pascal_s_parser.tab.h"
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
