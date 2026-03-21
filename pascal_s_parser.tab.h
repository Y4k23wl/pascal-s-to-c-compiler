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
     READ = 271,
     WRITE = 272,
     ARRAY = 273,
     OF = 274,
     INTEGER = 275,
     REAL = 276,
     BOOLEAN = 277,
     CHAR = 278,
     NOT = 279,
     DIV = 280,
     MOD = 281,
     AND = 282,
     OR = 283,
     ID = 284,
     INT_CONST = 285,
     REAL_CONST = 286,
     CHAR_CONST = 287,
     ASSIGN = 288,
     EQ = 289,
     NE = 290,
     LT = 291,
     LE = 292,
     GT = 293,
     GE = 294,
     PLUS = 295,
     MINUS = 296,
     MUL = 297,
     SLASH = 298,
     SEMICOLON = 299,
     DOT = 300,
     COMMA = 301,
     LPAREN = 302,
     RPAREN = 303,
     LBRACK = 304,
     RBRACK = 305,
     COLON = 306,
     RANGE = 307,
     LOWER_THAN_ELSE = 308,
     UMINUS = 309
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
#define READ 271
#define WRITE 272
#define ARRAY 273
#define OF 274
#define INTEGER 275
#define REAL 276
#define BOOLEAN 277
#define CHAR 278
#define NOT 279
#define DIV 280
#define MOD 281
#define AND 282
#define OR 283
#define ID 284
#define INT_CONST 285
#define REAL_CONST 286
#define CHAR_CONST 287
#define ASSIGN 288
#define EQ 289
#define NE 290
#define LT 291
#define LE 292
#define GT 293
#define GE 294
#define PLUS 295
#define MINUS 296
#define MUL 297
#define SLASH 298
#define SEMICOLON 299
#define DOT 300
#define COMMA 301
#define LPAREN 302
#define RPAREN 303
#define LBRACK 304
#define RBRACK 305
#define COLON 306
#define RANGE 307
#define LOWER_THAN_ELSE 308
#define UMINUS 309




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 50 "pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 1529 of yacc.c.  */
#line 164 "pascal_s_parser.tab.h"
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
