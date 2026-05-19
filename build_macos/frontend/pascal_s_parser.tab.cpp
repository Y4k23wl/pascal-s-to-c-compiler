/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 61 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 193 of yacc.c.  */
#line 278 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/build/frontend/pascal_s_parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 303 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/build/frontend/pascal_s_parser.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNRULES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    22,    24,    28,    29,
      33,    37,    43,    46,    49,    51,    53,    55,    57,    59,
      60,    64,    68,    74,    76,    83,    85,    87,    89,    91,
      95,   101,   103,   104,   108,   112,   116,   122,   123,   126,
     130,   134,   136,   140,   142,   144,   147,   151,   155,   159,
     163,   165,   169,   173,   177,   178,   182,   184,   186,   188,
     193,   200,   205,   214,   219,   224,   229,   234,   236,   240,
     243,   244,   248,   252,   254,   258,   263,   268,   270,   274,
     276,   280,   282,   286,   288,   292,   294,   296,   300,   305,
     310,   314,   316,   318,   320,   323,   326,   329,   331,   333,
     335,   337,   339,   341,   343,   345,   347,   349,   351,   353,
     355,   357,   359
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    49,    63,    50,    -1,     3,    33,
      52,    64,    53,    -1,     3,    33,    -1,    65,    68,    74,
      83,    -1,    33,    -1,    64,    51,    33,    -1,    -1,     4,
      66,    49,    -1,    33,    39,    67,    -1,    66,    49,    33,
      39,    67,    -1,    45,    98,    -1,    46,    98,    -1,    98,
      -1,    36,    -1,    37,    -1,    27,    -1,    28,    -1,    -1,
       5,    69,    49,    -1,    64,    56,    70,    -1,    69,    49,
      64,    56,    70,    -1,    71,    -1,    20,    54,    72,    55,
      21,    71,    -1,    22,    -1,    23,    -1,    24,    -1,    25,
      -1,    73,    57,    73,    -1,    72,    51,    73,    57,    73,
      -1,    34,    -1,    -1,    74,    75,    49,    -1,    76,    49,
      82,    -1,     6,    33,    77,    -1,     7,    33,    77,    56,
      71,    -1,    -1,    52,    53,    -1,    52,    78,    53,    -1,
      52,     1,    53,    -1,    79,    -1,    78,    49,    79,    -1,
      80,    -1,    81,    -1,     5,    81,    -1,    64,    56,    71,
      -1,    65,    68,    83,    -1,     8,    84,     9,    -1,     8,
       1,     9,    -1,    85,    -1,    84,    49,    85,    -1,    84,
      49,     1,    -1,    84,     1,    85,    -1,    -1,    87,    38,
      91,    -1,    89,    -1,    17,    -1,    83,    -1,    10,    91,
      11,    85,    -1,    10,    91,    11,    85,    12,    85,    -1,
      16,    91,    15,    85,    -1,    13,    33,    38,    91,    14,
      91,    15,    85,    -1,    18,    52,    86,    53,    -1,    18,
      52,     1,    53,    -1,    19,    52,    90,    53,    -1,    19,
      52,     1,    53,    -1,    87,    -1,    86,    51,    87,    -1,
      33,    88,    -1,    -1,    54,    90,    55,    -1,    54,     1,
      55,    -1,    33,    -1,    33,    52,    53,    -1,    33,    52,
      90,    53,    -1,    33,    52,     1,    53,    -1,    91,    -1,
      90,    51,    91,    -1,    92,    -1,    92,    95,    92,    -1,
      93,    -1,    92,    96,    93,    -1,    94,    -1,    93,    97,
      94,    -1,    98,    -1,    87,    -1,    52,    91,    53,    -1,
      33,    52,    90,    53,    -1,    33,    52,     1,    53,    -1,
      33,    52,    53,    -1,    27,    -1,    28,    -1,    37,    -1,
      26,    94,    -1,    45,    94,    -1,    46,    94,    -1,    39,
      -1,    40,    -1,    41,    -1,    42,    -1,    43,    -1,    44,
      -1,    45,    -1,    46,    -1,    32,    -1,    47,    -1,    48,
      -1,    29,    -1,    30,    -1,    31,    -1,    34,    -1,    35,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   145,   150,   158,   165,   170,   179,   182,
     189,   195,   203,   207,   211,   215,   220,   225,   229,   237,
     240,   247,   252,   259,   263,   270,   274,   278,   282,   289,
     294,   301,   309,   312,   319,   326,   331,   340,   343,   347,
     351,   363,   368,   375,   379,   386,   395,   402,   409,   413,
     425,   430,   434,   442,   455,   458,   462,   466,   470,   474,
     478,   482,   486,   491,   495,   504,   508,   520,   525,   532,
     541,   544,   548,   560,   565,   570,   575,   591,   596,   603,
     607,   615,   619,   627,   631,   639,   643,   647,   651,   656,
     669,   674,   678,   682,   687,   691,   695,   702,   706,   710,
     714,   718,   722,   729,   733,   737,   744,   748,   752,   756,
     760,   767,   771
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "CONST", "VAR", "PROCEDURE",
  "FUNCTION", "BEGIN_KW", "END_KW", "IF", "THEN", "ELSE", "FOR", "TO",
  "DO", "WHILE", "BREAK", "READ", "WRITE", "ARRAY", "OF", "INTEGER",
  "REAL", "BOOLEAN", "CHAR", "NOT", "TRUE", "FALSE", "DIV", "MOD", "AND",
  "OR", "ID", "INT_CONST", "REAL_CONST", "CHAR_CONST", "STRING_CONST",
  "ASSIGN", "EQ", "NE", "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MUL",
  "SLASH", "SEMICOLON", "DOT", "COMMA", "LPAREN", "RPAREN", "LBRACK",
  "RBRACK", "COLON", "RANGE", "LOWER_THAN_ELSE", "UMINUS", "$accept",
  "programstruct", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type", "period",
  "digits", "subprogram_declarations", "subprogram", "subprogram_head",
  "formal_parameter", "parameter_list", "parameter", "var_parameter",
  "value_parameter", "subprogram_body", "compound_statement",
  "statement_list", "statement", "variable_list", "variable", "id_varpart",
  "procedure_call", "expression_list", "expression", "simple_expression",
  "term", "factor", "relop", "addop", "mulop", "num", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    74,    74,    75,    76,    76,    77,    77,    77,
      77,    78,    78,    79,    79,    80,    81,    82,    83,    83,
      84,    84,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    86,    86,    87,
      88,    88,    88,    89,    89,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    97,    97,    97,    97,
      97,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     2,     2,     1,     1,     1,     1,     1,     0,
       3,     3,     5,     1,     6,     1,     1,     1,     1,     3,
       5,     1,     0,     3,     3,     3,     5,     0,     2,     3,
       3,     1,     3,     1,     1,     2,     3,     3,     3,     3,
       1,     3,     3,     3,     0,     3,     1,     1,     1,     4,
       6,     4,     8,     4,     4,     4,     4,     1,     3,     2,
       0,     3,     3,     1,     3,     4,     4,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     3,     4,     4,
       3,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      19,     6,     0,     0,     0,     2,     0,    32,     0,     3,
       0,     9,     0,     0,     0,     7,    17,    18,   111,   112,
      15,    16,     0,     0,    10,    14,     0,     0,    20,     0,
       0,     0,     0,     0,     5,    12,    13,     0,     0,    25,
      26,    27,    28,    21,    23,     0,    37,    37,     0,     0,
       0,     0,    57,     0,     0,    73,    58,     0,    50,     0,
      56,    33,     8,    11,     0,     0,     0,    35,     0,    49,
       0,    91,    92,    70,    93,     0,     0,     0,    86,     0,
      79,    81,    83,    85,     0,     0,     0,     0,     0,     0,
      69,    54,    48,     0,     0,    19,    34,    31,     0,     0,
      22,     0,     0,    38,     0,     0,    41,    43,    44,     0,
      94,     0,    95,    96,     0,    54,   105,    97,    98,    99,
     100,   101,   102,   103,   104,     0,     0,   108,   109,   110,
     106,   107,     0,     0,    54,     0,    70,     0,    67,     0,
       0,    77,     0,    74,     0,     0,     0,    53,    52,    51,
      55,     0,     0,     0,     0,    40,    45,     0,     0,    39,
      36,     0,    90,     0,    87,    59,    80,    82,    84,     0,
      61,    64,     0,    63,    66,     0,    65,    76,    75,    72,
      71,    47,     0,     0,    29,    46,    42,    89,    88,    54,
       0,    68,    78,     0,    24,    60,     0,    30,    54,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,   114,    10,    14,    34,    17,    23,
      53,    54,   108,   109,    24,    42,    43,    77,   115,   116,
     117,   118,   106,    66,    67,    68,   147,    88,   100,    70,
     150,   151,    90,    91,    92,   135,   136,   142,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
      48,     6,    54,    49,    40,  -155,   113,    87,    95,    79,
     148,  -155,   -36,   108,   107,  -155,    87,  -155,   132,  -155,
     170,   137,   -19,   125,   130,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,    36,    36,  -155,  -155,   139,   205,    87,   166,
     167,    17,   152,   159,  -155,  -155,  -155,   170,   160,  -155,
    -155,  -155,  -155,  -155,  -155,   -13,   161,   161,   202,   157,
     193,   157,  -155,   179,   180,   123,  -155,    10,  -155,   195,
    -155,  -155,   113,  -155,   200,   205,    15,  -155,   181,  -155,
     157,  -155,  -155,   -12,  -155,   157,   157,   157,  -155,   224,
     178,    43,  -155,  -155,   198,   223,     8,    88,    30,   117,
    -155,    91,  -155,   163,   157,   148,  -155,  -155,    26,   182,
    -155,   187,    87,  -155,   104,    47,  -155,  -155,  -155,   164,
    -155,    60,  -155,  -155,   188,    91,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,   157,   157,  -155,  -155,  -155,
    -155,  -155,   157,   157,    91,   189,   190,    27,  -155,   192,
     106,  -155,   194,  -155,   115,   191,    75,  -155,  -155,  -155,
    -155,   235,   200,   227,   200,  -155,  -155,   164,    19,  -155,
    -155,   196,  -155,   142,  -155,   238,   103,    43,  -155,   237,
    -155,  -155,   219,  -155,  -155,   157,  -155,  -155,  -155,  -155,
    -155,  -155,   197,   164,  -155,  -155,  -155,  -155,  -155,    91,
     157,  -155,  -155,   200,  -155,  -155,   240,  -155,    91,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,  -155,     7,   184,  -155,   206,   153,  -155,
     185,  -114,  -155,  -154,  -155,  -155,  -155,   204,  -155,    89,
    -155,   147,  -155,   -22,  -155,   -97,  -155,   -41,  -155,  -155,
     -77,   -58,   127,   128,   -73,  -155,  -155,  -155,    99
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -71
static const yytype_int16 yytable[] =
{
      69,    89,    44,    95,   157,   170,   159,   120,   192,   145,
     194,   101,   122,   123,    12,    18,   111,    19,    58,   102,
     112,   154,   156,    22,   112,    41,   -54,    59,   175,   124,
      60,   152,    18,    61,    62,    63,    64,    37,    18,     4,
     121,   146,    99,    75,   173,    55,   160,   180,    11,   207,
      65,     1,    11,   195,     5,   148,    80,    81,    82,   103,
      69,   171,    69,    83,    28,    29,   -54,    84,   113,   178,
      28,    29,   137,   138,   139,    85,    86,   162,   182,   204,
     183,   163,    87,   153,    69,   179,    80,    81,    82,   149,
     140,   141,     7,    83,    28,    29,   168,    84,     6,    41,
     169,    59,   205,    69,    60,    85,    86,    61,    62,    63,
      64,   209,    87,   172,    80,    81,    82,     8,   155,    35,
      11,    83,    28,    29,    65,    84,   185,   202,    13,    15,
     190,    45,    46,    85,    86,   126,    39,    40,    41,   191,
      87,   201,   206,    80,    81,    82,    35,    20,   133,   134,
      83,    28,    29,    16,    84,    18,    21,   185,    69,   186,
     167,   -70,    85,    86,   158,    25,   185,    69,   188,    87,
      36,    41,   -54,    59,    38,    98,    60,    99,    47,    61,
      62,    63,    64,    80,    81,    82,    49,    50,    51,    52,
      83,    28,    29,   185,    84,   198,    65,    26,    27,    56,
      57,    71,    85,    86,    28,    29,    30,    31,    72,    87,
     126,    79,   -54,    76,    74,    32,    33,   127,   128,   129,
     130,   131,   132,   133,   134,    48,    94,    49,    50,    51,
      52,    96,    97,   104,   107,   125,   143,   119,   144,   164,
     165,   174,   181,    41,    99,   184,   189,   187,   193,   197,
     199,   200,   146,    73,   203,   208,   105,   196,   161,   166,
     110,    78,   176,     0,   177
};

static const yytype_int16 yycheck[] =
{
      41,    59,    24,    61,   101,   119,   103,    80,   162,     1,
     164,     1,    85,    86,     7,    51,     1,    53,     1,     9,
       5,    98,    99,    16,     5,     8,     9,    10,   125,    87,
      13,     1,    51,    16,    17,    18,    19,    56,    51,    33,
      52,    33,    54,    56,   121,    38,   104,   144,    33,   203,
      33,     3,    33,   167,     0,    96,    26,    27,    28,    49,
     101,     1,   103,    33,    34,    35,    49,    37,    53,   142,
      34,    35,    29,    30,    31,    45,    46,    51,    51,   193,
      53,    55,    52,    53,   125,   143,    26,    27,    28,     1,
      47,    48,    52,    33,    34,    35,    49,    37,    49,     8,
      53,    10,   199,   144,    13,    45,    46,    16,    17,    18,
      19,   208,    52,    53,    26,    27,    28,     4,     1,    20,
      33,    33,    34,    35,    33,    37,    51,   185,    33,    50,
      55,    32,    33,    45,    46,    32,     6,     7,     8,   161,
      52,   182,   200,    26,    27,    28,    47,    39,    45,    46,
      33,    34,    35,     5,    37,    51,    49,    51,   199,    53,
      56,    38,    45,    46,     1,    33,    51,   208,    53,    52,
      33,     8,     9,    10,    49,    52,    13,    54,    39,    16,
      17,    18,    19,    26,    27,    28,    22,    23,    24,    25,
      33,    34,    35,    51,    37,    53,    33,    27,    28,    33,
      33,    49,    45,    46,    34,    35,    36,    37,    49,    52,
      32,     9,    49,    52,    54,    45,    46,    39,    40,    41,
      42,    43,    44,    45,    46,    20,    33,    22,    23,    24,
      25,    52,    52,    38,    34,    11,    38,    56,    15,    57,
      53,    53,    53,     8,    54,    53,    55,    53,    21,    53,
      12,    14,    33,    47,    57,    15,    72,   168,   105,   112,
      75,    57,   135,    -1,   136
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    61,    62,    33,     0,    49,    52,     4,    63,
      65,    33,    64,    33,    66,    50,     5,    68,    51,    53,
      39,    49,    64,    69,    74,    33,    27,    28,    34,    35,
      36,    37,    45,    46,    67,    98,    33,    56,    49,     6,
       7,     8,    75,    76,    83,    98,    98,    39,    20,    22,
      23,    24,    25,    70,    71,    64,    33,    33,     1,    10,
      13,    16,    17,    18,    19,    33,    83,    84,    85,    87,
      89,    49,    49,    67,    54,    56,    52,    77,    77,     9,
      26,    27,    28,    33,    37,    45,    46,    52,    87,    91,
      92,    93,    94,    98,    33,    91,    52,    52,    52,    54,
      88,     1,     9,    49,    38,    65,    82,    34,    72,    73,
      70,     1,     5,    53,    64,    78,    79,    80,    81,    56,
      94,    52,    94,    94,    91,    11,    32,    39,    40,    41,
      42,    43,    44,    45,    46,    95,    96,    29,    30,    31,
      47,    48,    97,    38,    15,     1,    33,    86,    87,     1,
      90,    91,     1,    53,    90,     1,    90,    85,     1,    85,
      91,    68,    51,    55,    57,    53,    81,    56,    49,    53,
      71,     1,    53,    90,    53,    85,    92,    93,    94,    91,
      85,    53,    51,    53,    53,    51,    53,    53,    53,    55,
      55,    83,    73,    21,    73,    71,    79,    53,    53,    12,
      14,    87,    91,    57,    71,    85,    91,    73,    15,    85
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 138 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          g_ast_root = (yyval.node);
      ;}
    break;

  case 3:
#line 146 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 4:
#line 151 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (2)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (2)].sval));
      ;}
    break;

  case 5:
#line 159 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 6:
#line 166 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_identifier_list(ast_make_identifier((yyvsp[(1) - (1)].sval), AST_LOC((yylsp[(1) - (1)]))), AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 7:
#line 171 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), ast_make_identifier((yyvsp[(3) - (3)].sval), AST_LOC((yylsp[(3) - (3)]))));
          free((yyvsp[(3) - (3)].sval));
      ;}
    break;

  case 8:
#line 179 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 9:
#line 183 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 10:
#line 190 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_const_decl((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 11:
#line 196 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_const_decl((yyvsp[(3) - (5)].sval), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
          free((yyvsp[(3) - (5)].sval));
      ;}
    break;

  case 12:
#line 204 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 13:
#line 208 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 14:
#line 212 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 15:
#line 216 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_text(AST_CHAR_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 16:
#line 221 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 17:
#line 226 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 18:
#line 230 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 19:
#line 237 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 20:
#line 241 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 21:
#line 248 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_var_decl((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
      ;}
    break;

  case 22:
#line 253 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_var_decl((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 23:
#line 260 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 24:
#line 264 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_array_type((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 25:
#line 271 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("integer", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 26:
#line 275 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("real", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 27:
#line 279 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("boolean", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 28:
#line 283 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("char", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 29:
#line 290 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PERIOD_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_period((yyvsp[(1) - (3)].ival), (yyvsp[(3) - (3)].ival), AST_LOC((yyloc))));
      ;}
    break;

  case 30:
#line 295 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_period((yyvsp[(3) - (5)].ival), (yyvsp[(5) - (5)].ival), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 31:
#line 302 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.ival) = (yyvsp[(1) - (1)].ival);
      ;}
    break;

  case 32:
#line 309 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 33:
#line 313 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
      ;}
    break;

  case 34:
#line 320 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 35:
#line 327 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(false, (yyvsp[(2) - (3)].sval), (yyvsp[(3) - (3)].node), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 36:
#line 332 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(true, (yyvsp[(2) - (5)].sval), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 37:
#line 340 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 38:
#line 344 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 39:
#line 348 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 40:
#line 352 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "形参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 41:
#line 364 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 42:
#line 369 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 43:
#line 376 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 44:
#line 380 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 45:
#line 387 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyvsp[(2) - (2)].node)->flag = true;
          (yyvsp[(2) - (2)].node)->loc = AST_LOC((yyloc));
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 46:
#line 396 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_param_group(false, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 47:
#line 403 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc))), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 48:
#line 410 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_compound_stmt((yyvsp[(2) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 49:
#line 414 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "复合语句内部存在语法错误，已恢复到 end");
          yyerrok;
          (yyval.node) = ast_make_compound_stmt(ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 50:
#line 426 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 51:
#line 431 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 52:
#line 435 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (3)]).first_line,
                         (yylsp[(3) - (3)]).first_column,
                         "语法恢复",
                         "语句存在语法错误，已跳过到下一个分号或 end 后继续");
          (yyval.node) = (yyvsp[(1) - (3)].node);
      ;}
    break;

  case 53:
#line 443 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "语句之间可能缺少分号，已恢复并继续");
          yyerrok;
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 54:
#line 455 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_empty_stmt(AST_LOC((yyloc)));
      ;}
    break;

  case 55:
#line 459 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_assign_stmt((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 56:
#line 463 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 57:
#line 467 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_break_stmt(AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 58:
#line 471 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 59:
#line 475 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), NULL, AST_LOC((yyloc)));
      ;}
    break;

  case 60:
#line 479 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 61:
#line 483 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_while_stmt((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 62:
#line 487 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_for_stmt((yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].node), (yyvsp[(6) - (8)].node), (yyvsp[(8) - (8)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (8)].sval));
      ;}
    break;

  case 63:
#line 492 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_read_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 64:
#line 496 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "read 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_read_stmt(ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 65:
#line 505 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_write_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 66:
#line 509 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "write 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_write_stmt(ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 67:
#line 521 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 68:
#line 526 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 69:
#line 533 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_var_ref((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (2)].sval));
      ;}
    break;

  case 70:
#line 541 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = NULL;
      ;}
    break;

  case 71:
#line 545 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 72:
#line 549 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "数组下标列表存在语法错误，已恢复到右中括号");
          yyerrok;
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 73:
#line 561 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (1)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 74:
#line 566 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (3)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 75:
#line 571 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 76:
#line 576 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_call(AST_CALL_STMT,
                             (yyvsp[(1) - (4)].sval),
                             ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))),
                             AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 77:
#line 592 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 78:
#line 597 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 79:
#line 604 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 80:
#line 608 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 81:
#line 616 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 82:
#line 620 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 83:
#line 628 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 84:
#line 632 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 85:
#line 640 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 86:
#line 644 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 87:
#line 648 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 88:
#line 652 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 89:
#line 657 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "函数调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_call(AST_CALL_EXPR,
                             (yyvsp[(1) - (4)].sval),
                             ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))),
                             AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 90:
#line 670 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[(1) - (3)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 91:
#line 675 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 92:
#line 679 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 93:
#line 683 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 94:
#line 688 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("not", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 95:
#line 692 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("+", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 96:
#line 696 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 97:
#line 703 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("=");
      ;}
    break;

  case 98:
#line 707 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<>");
      ;}
    break;

  case 99:
#line 711 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<");
      ;}
    break;

  case 100:
#line 715 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<=");
      ;}
    break;

  case 101:
#line 719 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">");
      ;}
    break;

  case 102:
#line 723 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">=");
      ;}
    break;

  case 103:
#line 730 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("+");
      ;}
    break;

  case 104:
#line 734 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("-");
      ;}
    break;

  case 105:
#line 738 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("or");
      ;}
    break;

  case 106:
#line 745 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("*");
      ;}
    break;

  case 107:
#line 749 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("/");
      ;}
    break;

  case 108:
#line 753 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("div");
      ;}
    break;

  case 109:
#line 757 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("mod");
      ;}
    break;

  case 110:
#line 761 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("and");
      ;}
    break;

  case 111:
#line 768 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_int(AST_INT_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 112:
#line 772 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_real(AST_REAL_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].fval));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2590 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/build/frontend/pascal_s_parser.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 777 "/Users/yuanweitu/Desktop/college/\347\274\226\350\257\221\350\257\276\350\256\276/code/frontend/pascal_s_parser.y"


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

