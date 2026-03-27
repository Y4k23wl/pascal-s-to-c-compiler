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




/* Copy the first part of user declarations.  */
#line 1 "code/pascal_s_parser.y"

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
#line 61 "code/pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 193 of yacc.c.  */
#line 274 "code/pascal_s_parser.tab.c"
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
#line 299 "code/pascal_s_parser.tab.c"

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
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

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
      55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    22,    24,    28,    29,
      33,    37,    43,    46,    49,    51,    53,    55,    57,    58,
      62,    66,    72,    74,    81,    83,    85,    87,    89,    93,
      99,   101,   102,   106,   110,   114,   120,   121,   124,   128,
     132,   134,   138,   140,   142,   145,   149,   153,   157,   161,
     163,   167,   171,   175,   176,   180,   182,   184,   189,   196,
     201,   210,   215,   220,   225,   230,   232,   236,   239,   240,
     244,   248,   250,   254,   259,   264,   266,   270,   272,   276,
     278,   282,   284,   288,   290,   292,   296,   301,   306,   310,
     312,   314,   317,   320,   323,   325,   327,   329,   331,   333,
     335,   337,   339,   341,   343,   345,   347,   349,   351,   353
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      59,     0,    -1,    60,    47,    61,    48,    -1,     3,    32,
      50,    62,    51,    -1,     3,    32,    -1,    63,    66,    72,
      81,    -1,    32,    -1,    62,    49,    32,    -1,    -1,     4,
      64,    47,    -1,    32,    37,    65,    -1,    64,    47,    32,
      37,    65,    -1,    43,    96,    -1,    44,    96,    -1,    96,
      -1,    35,    -1,    26,    -1,    27,    -1,    -1,     5,    67,
      47,    -1,    62,    54,    68,    -1,    67,    47,    62,    54,
      68,    -1,    69,    -1,    19,    52,    70,    53,    20,    69,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,    71,
      55,    71,    -1,    70,    49,    71,    55,    71,    -1,    33,
      -1,    -1,    72,    73,    47,    -1,    74,    47,    80,    -1,
       6,    32,    75,    -1,     7,    32,    75,    54,    69,    -1,
      -1,    50,    51,    -1,    50,    76,    51,    -1,    50,     1,
      51,    -1,    77,    -1,    76,    47,    77,    -1,    78,    -1,
      79,    -1,     5,    79,    -1,    62,    54,    69,    -1,    63,
      66,    81,    -1,     8,    82,     9,    -1,     8,     1,     9,
      -1,    83,    -1,    82,    47,    83,    -1,    82,    47,     1,
      -1,    82,     1,    83,    -1,    -1,    85,    36,    89,    -1,
      87,    -1,    81,    -1,    10,    89,    11,    83,    -1,    10,
      89,    11,    83,    12,    83,    -1,    16,    89,    15,    83,
      -1,    13,    32,    36,    89,    14,    89,    15,    83,    -1,
      17,    50,    84,    51,    -1,    17,    50,     1,    51,    -1,
      18,    50,    88,    51,    -1,    18,    50,     1,    51,    -1,
      85,    -1,    84,    49,    85,    -1,    32,    86,    -1,    -1,
      52,    88,    53,    -1,    52,     1,    53,    -1,    32,    -1,
      32,    50,    51,    -1,    32,    50,    88,    51,    -1,    32,
      50,     1,    51,    -1,    89,    -1,    88,    49,    89,    -1,
      90,    -1,    90,    93,    90,    -1,    91,    -1,    90,    94,
      91,    -1,    92,    -1,    91,    95,    92,    -1,    96,    -1,
      85,    -1,    50,    89,    51,    -1,    32,    50,    88,    51,
      -1,    32,    50,     1,    51,    -1,    32,    50,    51,    -1,
      26,    -1,    27,    -1,    25,    92,    -1,    43,    92,    -1,
      44,    92,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    31,
      -1,    45,    -1,    46,    -1,    28,    -1,    29,    -1,    30,
      -1,    33,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   136,   136,   144,   149,   157,   164,   169,   178,   181,
     188,   194,   202,   206,   210,   214,   219,   223,   231,   234,
     241,   246,   253,   257,   264,   268,   272,   276,   283,   288,
     295,   303,   306,   313,   320,   325,   334,   337,   341,   345,
     357,   362,   369,   373,   380,   389,   396,   403,   407,   419,
     424,   428,   437,   450,   453,   457,   461,   465,   469,   473,
     477,   482,   486,   495,   499,   511,   516,   523,   532,   535,
     539,   551,   556,   561,   566,   582,   587,   594,   598,   606,
     610,   618,   622,   630,   634,   638,   642,   647,   660,   665,
     669,   673,   677,   681,   688,   692,   696,   700,   704,   708,
     715,   719,   723,   730,   734,   738,   742,   746,   753,   757
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "CONST", "VAR", "PROCEDURE",
  "FUNCTION", "BEGIN_KW", "END_KW", "IF", "THEN", "ELSE", "FOR", "TO",
  "DO", "WHILE", "READ", "WRITE", "ARRAY", "OF", "INTEGER", "REAL",
  "BOOLEAN", "CHAR", "NOT", "TRUE", "FALSE", "DIV", "MOD", "AND", "OR",
  "ID", "INT_CONST", "REAL_CONST", "CHAR_CONST", "ASSIGN", "EQ", "NE",
  "LT", "LE", "GT", "GE", "PLUS", "MINUS", "MUL", "SLASH", "SEMICOLON",
  "DOT", "COMMA", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "COLON", "RANGE",
  "LOWER_THAN_ELSE", "UMINUS", "$accept", "programstruct", "program_head",
  "program_body", "idlist", "const_declarations", "const_declaration",
  "const_value", "var_declarations", "var_declaration", "type",
  "basic_type", "period", "digits", "subprogram_declarations",
  "subprogram", "subprogram_head", "formal_parameter", "parameter_list",
  "parameter", "var_parameter", "value_parameter", "subprogram_body",
  "compound_statement", "statement_list", "statement", "variable_list",
  "variable", "id_varpart", "procedure_call", "expression_list",
  "expression", "simple_expression", "term", "factor", "relop", "addop",
  "mulop", "num", 0
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
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      71,    72,    72,    73,    74,    74,    75,    75,    75,    75,
      76,    76,    77,    77,    78,    79,    80,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    84,    85,    86,    86,
      86,    87,    87,    87,    87,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    93,    93,    93,    93,    93,
      94,    94,    94,    95,    95,    95,    95,    95,    96,    96
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     2,     2,     1,     1,     1,     1,     0,     3,
       3,     5,     1,     6,     1,     1,     1,     1,     3,     5,
       1,     0,     3,     3,     3,     5,     0,     2,     3,     3,
       1,     3,     1,     1,     2,     3,     3,     3,     3,     1,
       3,     3,     3,     0,     3,     1,     1,     4,     6,     4,
       8,     4,     4,     4,     4,     1,     3,     2,     0,     3,
       3,     1,     3,     4,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     3,     4,     4,     3,     1,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      18,     6,     0,     0,     0,     2,     0,    31,     0,     3,
       0,     9,     0,     0,     0,     7,    16,    17,   108,   109,
      15,     0,     0,    10,    14,     0,     0,    19,     0,     0,
       0,     0,     0,     5,    12,    13,     0,     0,    24,    25,
      26,    27,    20,    22,     0,    36,    36,     0,     0,     0,
       0,     0,     0,    71,    56,     0,    49,     0,    55,    32,
       8,    11,     0,     0,     0,    34,     0,    48,     0,    89,
      90,    68,     0,     0,     0,    84,     0,    77,    79,    81,
      83,     0,     0,     0,     0,     0,     0,    67,    53,    47,
       0,     0,    18,    33,    30,     0,     0,    21,     0,     0,
      37,     0,     0,    40,    42,    43,     0,    91,     0,    92,
      93,     0,    53,   102,    94,    95,    96,    97,    98,    99,
     100,   101,     0,     0,   105,   106,   107,   103,   104,     0,
       0,    53,     0,    68,     0,    65,     0,     0,    75,     0,
      72,     0,     0,     0,    52,    51,    50,    54,     0,     0,
       0,     0,    39,    44,     0,     0,    38,    35,     0,    88,
       0,    85,    57,    78,    80,    82,     0,    59,    62,     0,
      61,    64,     0,    63,    74,    73,    70,    69,    46,     0,
       0,    28,    45,    41,    87,    86,    53,     0,    66,    76,
       0,    23,    58,     0,    29,    53,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,   111,    10,    14,    33,    17,    23,
      52,    53,   105,   106,    24,    41,    42,    75,   112,   113,
     114,   115,   103,    64,    65,    66,   144,    85,    97,    68,
     147,   148,    87,    88,    89,   132,   133,   139,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -124
static const yytype_int16 yypact[] =
{
      32,    13,    56,    25,    28,  -124,    90,    72,    73,    70,
     118,  -124,   -37,    95,    91,  -124,    72,  -124,   110,  -124,
     169,   115,   -31,   103,   191,  -124,  -124,  -124,  -124,  -124,
    -124,    51,    51,  -124,  -124,   114,    52,    72,   134,   135,
     111,   132,   138,  -124,  -124,  -124,   169,   126,  -124,  -124,
    -124,  -124,  -124,  -124,     0,   141,   141,   173,   137,   168,
     137,   160,   161,   105,  -124,    12,  -124,   165,  -124,  -124,
      90,  -124,   181,    52,    14,  -124,   152,  -124,   137,  -124,
    -124,    65,   137,   137,   137,  -124,   216,   178,   131,  -124,
    -124,   192,   214,    10,     7,    36,    66,  -124,   176,  -124,
     136,   137,   118,  -124,  -124,   -29,   177,  -124,   179,    72,
    -124,    54,    79,  -124,  -124,  -124,   151,  -124,    63,  -124,
    -124,   180,   176,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,   137,   137,  -124,  -124,  -124,  -124,  -124,   137,
     137,   176,   182,   183,   139,  -124,   185,   156,  -124,   186,
    -124,   174,   187,    82,  -124,  -124,  -124,  -124,   226,   181,
     218,   181,  -124,  -124,   151,    11,  -124,  -124,   188,  -124,
     175,  -124,   229,   -14,   131,  -124,   228,  -124,  -124,   211,
    -124,  -124,   137,  -124,  -124,  -124,  -124,  -124,  -124,   189,
     151,  -124,  -124,  -124,  -124,  -124,   176,   137,  -124,  -124,
     181,  -124,  -124,   230,  -124,   176,  -124
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,  -124,    15,   184,  -124,   200,   145,  -124,
     190,  -109,  -124,  -123,  -124,  -124,  -124,   193,  -124,    83,
    -124,   142,  -124,   -22,  -124,   -94,  -124,   -40,  -124,  -124,
     -70,   -57,   120,   117,   -73,  -124,  -124,  -124,   102
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -69
static const yytype_int16 yytable[] =
{
      67,    86,    43,    92,   154,   117,   156,   167,   146,   119,
     120,   142,    18,    98,    19,   108,   109,   123,    18,   109,
     159,    99,    12,    36,   160,   151,   153,   121,   172,   130,
     131,    22,    78,    79,    80,     1,   189,   149,   191,    81,
      28,    29,   143,    11,   157,     4,    11,   177,   170,    18,
      82,    83,    54,   145,    73,   192,     5,    84,    67,   100,
      67,    78,    79,    80,   168,   110,   175,   152,    81,    28,
      29,    47,     6,    48,    49,    50,    51,   204,     7,    82,
      83,   201,    67,   176,    28,    29,    84,   150,    78,    79,
      80,    78,    79,    80,     8,    81,    28,    29,    81,    28,
      29,    67,   202,    18,    11,    13,    82,    83,   164,    82,
      83,   206,    57,    84,   169,   118,    84,    96,    15,    40,
     -53,    58,    34,    16,    59,   199,   165,    60,    61,    62,
     166,   182,    20,    44,    45,   187,   188,   155,    21,   198,
     203,   -68,    25,    63,    40,   -53,    58,    35,    34,    59,
      37,    46,    60,    61,    62,    95,    67,    96,   -53,   134,
     135,   136,    78,    79,    80,    67,    55,    56,    63,    81,
      28,    29,    48,    49,    50,    51,   137,   138,    72,    69,
      82,    83,    77,   -53,    40,    70,    58,    84,   179,    59,
     180,    74,    60,    61,    62,    26,    27,    38,    39,    40,
      91,   101,    28,    29,    30,   182,   116,   183,    63,   123,
      93,    94,    31,    32,   104,   124,   125,   126,   127,   128,
     129,   130,   131,   182,   182,   185,   195,   122,   140,   141,
     162,   171,   161,   178,    40,    96,   181,   184,   190,   194,
     186,   196,   197,   143,   200,   205,    71,   158,   193,    76,
     174,   163,   173,     0,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   107
};

static const yytype_int16 yycheck[] =
{
      40,    58,    24,    60,    98,    78,   100,   116,     1,    82,
      83,     1,    49,     1,    51,     1,     5,    31,    49,     5,
      49,     9,     7,    54,    53,    95,    96,    84,   122,    43,
      44,    16,    25,    26,    27,     3,   159,     1,   161,    32,
      33,    34,    32,    32,   101,    32,    32,   141,   118,    49,
      43,    44,    37,    93,    54,   164,     0,    50,    98,    47,
     100,    25,    26,    27,     1,    51,   139,     1,    32,    33,
      34,    19,    47,    21,    22,    23,    24,   200,    50,    43,
      44,   190,   122,   140,    33,    34,    50,    51,    25,    26,
      27,    25,    26,    27,     4,    32,    33,    34,    32,    33,
      34,   141,   196,    49,    32,    32,    43,    44,    54,    43,
      44,   205,     1,    50,    51,    50,    50,    52,    48,     8,
       9,    10,    20,     5,    13,   182,    47,    16,    17,    18,
      51,    49,    37,    31,    32,    53,   158,     1,    47,   179,
     197,    36,    32,    32,     8,     9,    10,    32,    46,    13,
      47,    37,    16,    17,    18,    50,   196,    52,    47,    28,
      29,    30,    25,    26,    27,   205,    32,    32,    32,    32,
      33,    34,    21,    22,    23,    24,    45,    46,    52,    47,
      43,    44,     9,    47,     8,    47,    10,    50,    49,    13,
      51,    50,    16,    17,    18,    26,    27,     6,     7,     8,
      32,    36,    33,    34,    35,    49,    54,    51,    32,    31,
      50,    50,    43,    44,    33,    37,    38,    39,    40,    41,
      42,    43,    44,    49,    49,    51,    51,    11,    36,    15,
      51,    51,    55,    51,     8,    52,    51,    51,    20,    51,
      53,    12,    14,    32,    55,    15,    46,   102,   165,    56,
     133,   109,   132,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    59,    60,    32,     0,    47,    50,     4,    61,
      63,    32,    62,    32,    64,    48,     5,    66,    49,    51,
      37,    47,    62,    67,    72,    32,    26,    27,    33,    34,
      35,    43,    44,    65,    96,    32,    54,    47,     6,     7,
       8,    73,    74,    81,    96,    96,    37,    19,    21,    22,
      23,    24,    68,    69,    62,    32,    32,     1,    10,    13,
      16,    17,    18,    32,    81,    82,    83,    85,    87,    47,
      47,    65,    52,    54,    50,    75,    75,     9,    25,    26,
      27,    32,    43,    44,    50,    85,    89,    90,    91,    92,
      96,    32,    89,    50,    50,    50,    52,    86,     1,     9,
      47,    36,    63,    80,    33,    70,    71,    68,     1,     5,
      51,    62,    76,    77,    78,    79,    54,    92,    50,    92,
      92,    89,    11,    31,    37,    38,    39,    40,    41,    42,
      43,    44,    93,    94,    28,    29,    30,    45,    46,    95,
      36,    15,     1,    32,    84,    85,     1,    88,    89,     1,
      51,    88,     1,    88,    83,     1,    83,    89,    66,    49,
      53,    55,    51,    79,    54,    47,    51,    69,     1,    51,
      88,    51,    83,    90,    91,    92,    89,    83,    51,    49,
      51,    51,    49,    51,    51,    51,    53,    53,    81,    71,
      20,    71,    69,    77,    51,    51,    12,    14,    85,    89,
      55,    69,    83,    89,    71,    15,    83
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
#line 137 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          g_ast_root = (yyval.node);
      ;}
    break;

  case 3:
#line 145 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 4:
#line 150 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (2)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (2)].sval));
      ;}
    break;

  case 5:
#line 158 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 6:
#line 165 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_identifier_list(ast_make_identifier((yyvsp[(1) - (1)].sval), AST_LOC((yylsp[(1) - (1)]))), AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 7:
#line 170 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), ast_make_identifier((yyvsp[(3) - (3)].sval), AST_LOC((yylsp[(3) - (3)]))));
          free((yyvsp[(3) - (3)].sval));
      ;}
    break;

  case 8:
#line 178 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 9:
#line 182 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 10:
#line 189 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_const_decl((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 11:
#line 195 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_const_decl((yyvsp[(3) - (5)].sval), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
          free((yyvsp[(3) - (5)].sval));
      ;}
    break;

  case 12:
#line 203 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 13:
#line 207 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 14:
#line 211 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 15:
#line 215 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_text(AST_CHAR_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 16:
#line 220 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 17:
#line 224 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 18:
#line 231 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 19:
#line 235 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 20:
#line 242 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_var_decl((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
      ;}
    break;

  case 21:
#line 247 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_var_decl((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 22:
#line 254 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 23:
#line 258 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_array_type((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 24:
#line 265 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("integer", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 25:
#line 269 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("real", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 26:
#line 273 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("boolean", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 27:
#line 277 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("char", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 28:
#line 284 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PERIOD_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_period((yyvsp[(1) - (3)].ival), (yyvsp[(3) - (3)].ival), AST_LOC((yyloc))));
      ;}
    break;

  case 29:
#line 289 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_period((yyvsp[(3) - (5)].ival), (yyvsp[(5) - (5)].ival), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 30:
#line 296 "code/pascal_s_parser.y"
    {
          (yyval.ival) = (yyvsp[(1) - (1)].ival);
      ;}
    break;

  case 31:
#line 303 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 32:
#line 307 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
      ;}
    break;

  case 33:
#line 314 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 34:
#line 321 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(false, (yyvsp[(2) - (3)].sval), (yyvsp[(3) - (3)].node), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 35:
#line 326 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(true, (yyvsp[(2) - (5)].sval), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 36:
#line 334 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 37:
#line 338 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 38:
#line 342 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 39:
#line 346 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "形参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 40:
#line 358 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 41:
#line 363 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 42:
#line 370 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 43:
#line 374 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 44:
#line 381 "code/pascal_s_parser.y"
    {
          (yyvsp[(2) - (2)].node)->flag = true;
          (yyvsp[(2) - (2)].node)->loc = AST_LOC((yyloc));
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 45:
#line 390 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_param_group(false, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 46:
#line 397 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc))), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 47:
#line 404 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_compound_stmt((yyvsp[(2) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 48:
#line 408 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "复合语句内部存在语法错误，已恢复到 end");
          yyerrok;
          (yyval.node) = ast_make_compound_stmt(ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 49:
#line 420 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 50:
#line 425 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 51:
#line 429 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (3)]).first_line,
                         (yylsp[(3) - (3)]).first_column,
                         "语法恢复",
                         "语句存在语法错误，已跳过到下一个分号或 end 后继续");
          yyerrok;
          (yyval.node) = (yyvsp[(1) - (3)].node);
      ;}
    break;

  case 52:
#line 438 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "语句之间可能缺少分号，已恢复并继续");
          yyerrok;
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 53:
#line 450 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_empty_stmt(AST_LOC((yyloc)));
      ;}
    break;

  case 54:
#line 454 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_assign_stmt((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 55:
#line 458 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 56:
#line 462 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 57:
#line 466 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), NULL, AST_LOC((yyloc)));
      ;}
    break;

  case 58:
#line 470 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 59:
#line 474 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_while_stmt((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 60:
#line 478 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_for_stmt((yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].node), (yyvsp[(6) - (8)].node), (yyvsp[(8) - (8)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (8)].sval));
      ;}
    break;

  case 61:
#line 483 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_read_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 62:
#line 487 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "read 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_read_stmt(ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 63:
#line 496 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_write_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 64:
#line 500 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(3) - (4)]).first_line,
                         (yylsp[(3) - (4)]).first_column,
                         "语法恢复",
                         "write 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_write_stmt(ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      ;}
    break;

  case 65:
#line 512 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 66:
#line 517 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 67:
#line 524 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_var_ref((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (2)].sval));
      ;}
    break;

  case 68:
#line 532 "code/pascal_s_parser.y"
    {
          (yyval.node) = NULL;
      ;}
    break;

  case 69:
#line 536 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 70:
#line 540 "code/pascal_s_parser.y"
    {
          parser_note_at((yylsp[(2) - (3)]).first_line,
                         (yylsp[(2) - (3)]).first_column,
                         "语法恢复",
                         "数组下标列表存在语法错误，已恢复到右中括号");
          yyerrok;
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 71:
#line 552 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (1)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 72:
#line 557 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (3)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 73:
#line 562 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 74:
#line 567 "code/pascal_s_parser.y"
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

  case 75:
#line 583 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 76:
#line 588 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 77:
#line 595 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 78:
#line 599 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 79:
#line 607 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 80:
#line 611 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 81:
#line 619 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 82:
#line 623 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 83:
#line 631 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 84:
#line 635 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 85:
#line 639 "code/pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 86:
#line 643 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 87:
#line 648 "code/pascal_s_parser.y"
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

  case 88:
#line 661 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[(1) - (3)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 89:
#line 666 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 90:
#line 670 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 91:
#line 674 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("not", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 92:
#line 678 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("+", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 93:
#line 682 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 94:
#line 689 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("=");
      ;}
    break;

  case 95:
#line 693 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<>");
      ;}
    break;

  case 96:
#line 697 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<");
      ;}
    break;

  case 97:
#line 701 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<=");
      ;}
    break;

  case 98:
#line 705 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">");
      ;}
    break;

  case 99:
#line 709 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">=");
      ;}
    break;

  case 100:
#line 716 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("+");
      ;}
    break;

  case 101:
#line 720 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("-");
      ;}
    break;

  case 102:
#line 724 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("or");
      ;}
    break;

  case 103:
#line 731 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("*");
      ;}
    break;

  case 104:
#line 735 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("/");
      ;}
    break;

  case 105:
#line 739 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("div");
      ;}
    break;

  case 106:
#line 743 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("mod");
      ;}
    break;

  case 107:
#line 747 "code/pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("and");
      ;}
    break;

  case 108:
#line 754 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_int(AST_INT_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 109:
#line 758 "code/pascal_s_parser.y"
    {
          (yyval.node) = ast_new_real(AST_REAL_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].fval));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2559 "code/pascal_s_parser.tab.c"
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


#line 763 "code/pascal_s_parser.y"


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

