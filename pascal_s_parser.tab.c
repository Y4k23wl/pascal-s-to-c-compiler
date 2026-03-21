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




/* Copy the first part of user declarations.  */
#line 1 "pascal_s_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.hpp"

int yylex(void);
void yyerror(const char *msg);
void yyrestart(FILE *input_file);
void lexer_reset_position(void);

AstNode *g_ast_root = NULL;
static int g_parse_failed = 0;

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
#line 50 "pascal_s_parser.y"
{
    char *sval;
    int ival;
    double fval;
    struct AstNode *node;
}
/* Line 193 of yacc.c.  */
#line 257 "pascal_s_parser.tab.c"
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
#line 282 "pascal_s_parser.tab.c"

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
#define YYLAST   177

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNRULES -- Number of states.  */
#define YYNSTATES  177

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    22,    24,    28,    29,
      33,    37,    43,    46,    49,    51,    53,    54,    58,    62,
      68,    70,    77,    79,    81,    83,    85,    89,    95,    97,
      98,   102,   106,   110,   116,   117,   121,   123,   127,   129,
     131,   134,   138,   142,   146,   148,   152,   153,   157,   159,
     161,   166,   173,   182,   187,   192,   194,   198,   201,   202,
     206,   208,   213,   215,   219,   221,   225,   227,   231,   233,
     237,   239,   241,   245,   250,   253,   256,   258,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     284,   286
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    44,    58,    45,    -1,     3,    29,
      47,    59,    48,    -1,     3,    29,    -1,    60,    63,    69,
      78,    -1,    29,    -1,    59,    46,    29,    -1,    -1,     4,
      61,    44,    -1,    29,    34,    62,    -1,    61,    44,    29,
      34,    62,    -1,    40,    93,    -1,    41,    93,    -1,    93,
      -1,    32,    -1,    -1,     5,    64,    44,    -1,    59,    51,
      65,    -1,    64,    44,    59,    51,    65,    -1,    66,    -1,
      18,    49,    67,    50,    19,    66,    -1,    20,    -1,    21,
      -1,    22,    -1,    23,    -1,    68,    52,    68,    -1,    67,
      46,    68,    52,    68,    -1,    30,    -1,    -1,    69,    70,
      44,    -1,    71,    44,    77,    -1,     6,    29,    72,    -1,
       7,    29,    72,    51,    66,    -1,    -1,    47,    73,    48,
      -1,    74,    -1,    73,    44,    74,    -1,    75,    -1,    76,
      -1,     5,    76,    -1,    59,    51,    66,    -1,    60,    63,
      78,    -1,     8,    79,     9,    -1,    80,    -1,    79,    44,
      80,    -1,    -1,    82,    33,    86,    -1,    84,    -1,    78,
      -1,    10,    86,    11,    80,    -1,    10,    86,    11,    80,
      12,    80,    -1,    13,    29,    33,    86,    14,    86,    15,
      80,    -1,    16,    47,    81,    48,    -1,    17,    47,    85,
      48,    -1,    82,    -1,    81,    46,    82,    -1,    29,    83,
      -1,    -1,    49,    85,    50,    -1,    29,    -1,    29,    47,
      85,    48,    -1,    86,    -1,    85,    46,    86,    -1,    87,
      -1,    87,    90,    87,    -1,    88,    -1,    87,    91,    88,
      -1,    89,    -1,    88,    92,    89,    -1,    93,    -1,    82,
      -1,    47,    86,    48,    -1,    29,    47,    85,    48,    -1,
      24,    89,    -1,    41,    89,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,
      41,    -1,    28,    -1,    42,    -1,    43,    -1,    25,    -1,
      26,    -1,    27,    -1,    30,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   124,   124,   132,   137,   145,   152,   157,   166,   169,
     176,   182,   190,   194,   198,   202,   211,   214,   221,   226,
     233,   237,   244,   248,   252,   256,   263,   268,   275,   283,
     286,   293,   300,   305,   314,   317,   324,   329,   336,   340,
     347,   356,   363,   370,   377,   382,   390,   393,   397,   401,
     405,   409,   413,   418,   422,   429,   434,   441,   450,   453,
     460,   465,   473,   478,   485,   489,   497,   501,   509,   513,
     521,   525,   529,   533,   538,   542,   549,   553,   557,   561,
     565,   569,   576,   580,   584,   591,   595,   599,   603,   607,
     614,   618
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "CONST", "VAR", "PROCEDURE",
  "FUNCTION", "BEGIN_KW", "END_KW", "IF", "THEN", "ELSE", "FOR", "TO",
  "DO", "READ", "WRITE", "ARRAY", "OF", "INTEGER", "REAL", "BOOLEAN",
  "CHAR", "NOT", "DIV", "MOD", "AND", "OR", "ID", "INT_CONST",
  "REAL_CONST", "CHAR_CONST", "ASSIGN", "EQ", "NE", "LT", "LE", "GT", "GE",
  "PLUS", "MINUS", "MUL", "SLASH", "SEMICOLON", "DOT", "COMMA", "LPAREN",
  "RPAREN", "LBRACK", "RBRACK", "COLON", "RANGE", "LOWER_THAN_ELSE",
  "UMINUS", "$accept", "programstruct", "program_head", "program_body",
  "idlist", "const_declarations", "const_declaration", "const_value",
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
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    67,    67,    68,    69,
      69,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    76,    77,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    89,    89,    89,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    92,    92,    92,    92,    92,
      93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     4,     1,     3,     0,     3,
       3,     5,     2,     2,     1,     1,     0,     3,     3,     5,
       1,     6,     1,     1,     1,     1,     3,     5,     1,     0,
       3,     3,     3,     5,     0,     3,     1,     3,     1,     1,
       2,     3,     3,     3,     1,     3,     0,     3,     1,     1,
       4,     6,     8,     4,     4,     1,     3,     2,     0,     3,
       1,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     3,     4,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      16,     6,     0,     0,     0,     2,     0,    29,     0,     3,
       0,     9,     0,     0,     0,     7,    90,    91,    15,     0,
       0,    10,    14,     0,     0,    17,     0,     0,    46,     0,
       0,     5,    12,    13,     0,     0,    22,    23,    24,    25,
      18,    20,     0,    34,    34,     0,     0,     0,     0,    60,
      49,     0,    44,     0,    48,    30,     8,    11,     0,     0,
       0,    32,     0,     0,    58,     0,     0,    71,     0,    64,
      66,    68,    70,     0,     0,     0,     0,     0,    57,    43,
      46,     0,    16,    31,    28,     0,     0,    19,     0,     0,
       0,    36,    38,    39,     0,    74,     0,    75,     0,    46,
      84,    76,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    87,    88,    89,    85,    86,     0,     0,    58,     0,
      55,     0,    62,     0,     0,    45,    47,     0,     0,     0,
       0,    40,     0,     0,    35,    33,     0,    72,    50,    65,
      67,    69,     0,     0,    53,     0,    54,    61,    59,    42,
       0,     0,    26,    41,    37,    73,    46,     0,    56,    63,
       0,    21,    51,     0,    27,    46,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    99,    10,    14,    31,    17,    23,
      50,    51,    95,    96,    24,    39,    40,    71,   100,   101,
     102,   103,    93,    60,    61,    62,   129,    77,    88,    64,
     131,   132,    79,    80,    81,   119,   120,   126,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -129
static const yytype_int16 yypact[] =
{
      14,    -6,    38,     0,    20,  -129,    73,    52,    68,    57,
      98,  -129,   -22,    92,    69,  -129,    52,  -129,    83,  -129,
      43,   100,     3,    86,   103,  -129,  -129,  -129,  -129,    55,
      55,  -129,  -129,    97,    78,    52,   104,   105,    40,    88,
      91,  -129,  -129,  -129,    43,    87,  -129,  -129,  -129,  -129,
    -129,  -129,    15,    93,    93,    -2,   109,    94,    95,   -13,
    -129,    -1,  -129,   106,  -129,  -129,    73,  -129,   113,    78,
       6,  -129,    96,    -2,    70,    -2,    -2,  -129,   133,    54,
      37,  -129,  -129,   112,   117,    -2,    -2,    -2,  -129,  -129,
      40,    -2,    98,  -129,  -129,     1,    99,  -129,    52,    19,
      11,  -129,  -129,  -129,    85,  -129,    -2,  -129,   101,    40,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,    -2,
      -2,  -129,  -129,  -129,  -129,  -129,    -2,    -2,   107,    72,
    -129,    75,  -129,    76,    22,  -129,  -129,   140,   113,   131,
     113,  -129,    85,     6,  -129,  -129,    79,  -129,   141,    -9,
      37,  -129,   138,   117,  -129,    -2,  -129,  -129,  -129,  -129,
     102,    85,  -129,  -129,  -129,  -129,    40,    -2,  -129,  -129,
     113,  -129,  -129,   142,  -129,    40,  -129
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,  -129,     2,    89,  -129,   114,    67,  -129,
     108,  -101,  -129,  -128,  -129,  -129,  -129,   110,  -129,    17,
    -129,    63,  -129,   -23,  -129,   -88,  -129,   -38,  -129,  -129,
     -73,   -51,    44,    42,   -68,  -129,  -129,  -129,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -59
static const yytype_int16 yytable[] =
{
      63,    41,   135,   145,    78,   105,    32,   107,    89,    12,
     160,    98,   162,   133,   134,    42,    43,     1,    22,   110,
     -58,   148,    73,     4,    18,   108,    19,    74,    26,    27,
      32,   117,   118,   146,    86,    11,    87,    52,     5,    75,
     136,   163,   174,    90,     6,    76,   130,   138,    38,    18,
      55,   139,    63,    56,    34,   143,    57,    58,   151,   144,
     171,    18,   121,   122,   123,    18,    69,     7,   155,    59,
     142,    63,   158,    26,    27,    28,   152,     8,   172,   124,
     125,    11,   110,    29,    30,    26,    27,   176,   111,   112,
     113,   114,   115,   116,   117,   118,    45,    13,    46,    47,
      48,    49,    15,    16,   169,    46,    47,    48,    49,    36,
      37,    38,    25,    21,   159,   168,   173,   106,   153,    87,
     154,   155,   155,   156,   157,   155,    20,   165,    63,    33,
      35,    44,    65,    53,    54,    66,    68,    63,    83,    91,
      70,    84,    85,    94,   109,   127,   128,   104,    38,   147,
     161,   140,   167,   166,   170,    92,    87,   175,    67,   137,
     164,   141,   150,   149,    72,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97
};

static const yytype_int16 yycheck[] =
{
      38,    24,    90,   104,    55,    73,    20,    75,     9,     7,
     138,     5,   140,    86,    87,    29,    30,     3,    16,    28,
      33,   109,    24,    29,    46,    76,    48,    29,    30,    31,
      44,    40,    41,   106,    47,    29,    49,    35,     0,    41,
      91,   142,   170,    44,    44,    47,    84,    46,     8,    46,
      10,    50,    90,    13,    51,    44,    16,    17,   126,    48,
     161,    46,    25,    26,    27,    46,    51,    47,    46,    29,
      51,   109,    50,    30,    31,    32,   127,     4,   166,    42,
      43,    29,    28,    40,    41,    30,    31,   175,    34,    35,
      36,    37,    38,    39,    40,    41,    18,    29,    20,    21,
      22,    23,    45,     5,   155,    20,    21,    22,    23,     6,
       7,     8,    29,    44,   137,   153,   167,    47,    46,    49,
      48,    46,    46,    48,    48,    46,    34,    48,   166,    29,
      44,    34,    44,    29,    29,    44,    49,   175,    29,    33,
      47,    47,    47,    30,    11,    33,    29,    51,     8,    48,
      19,    52,    14,    12,    52,    66,    49,    15,    44,    92,
     143,    98,   120,   119,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    56,    57,    29,     0,    44,    47,     4,    58,
      60,    29,    59,    29,    61,    45,     5,    63,    46,    48,
      34,    44,    59,    64,    69,    29,    30,    31,    32,    40,
      41,    62,    93,    29,    51,    44,     6,     7,     8,    70,
      71,    78,    93,    93,    34,    18,    20,    21,    22,    23,
      65,    66,    59,    29,    29,    10,    13,    16,    17,    29,
      78,    79,    80,    82,    84,    44,    44,    62,    49,    51,
      47,    72,    72,    24,    29,    41,    47,    82,    86,    87,
      88,    89,    93,    29,    47,    47,    47,    49,    83,     9,
      44,    33,    60,    77,    30,    67,    68,    65,     5,    59,
      73,    74,    75,    76,    51,    89,    47,    89,    86,    11,
      28,    34,    35,    36,    37,    38,    39,    40,    41,    90,
      91,    25,    26,    27,    42,    43,    92,    33,    29,    81,
      82,    85,    86,    85,    85,    80,    86,    63,    46,    50,
      52,    76,    51,    44,    48,    66,    85,    48,    80,    87,
      88,    89,    86,    46,    48,    46,    48,    48,    50,    78,
      68,    19,    68,    66,    74,    48,    12,    14,    82,    86,
      52,    66,    80,    86,    68,    15,    80
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
#line 125 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          g_ast_root = (yyval.node);
      ;}
    break;

  case 3:
#line 133 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (5)].sval), (yyvsp[(4) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 4:
#line 138 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_program_head((yyvsp[(2) - (2)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (2)].sval));
      ;}
    break;

  case 5:
#line 146 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 6:
#line 153 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_identifier_list(ast_make_identifier((yyvsp[(1) - (1)].sval), AST_LOC((yylsp[(1) - (1)]))), AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 7:
#line 158 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), ast_make_identifier((yyvsp[(3) - (3)].sval), AST_LOC((yylsp[(3) - (3)]))));
          free((yyvsp[(3) - (3)].sval));
      ;}
    break;

  case 8:
#line 166 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 9:
#line 170 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 10:
#line 177 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_const_decl((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
          free((yyvsp[(1) - (3)].sval));
      ;}
    break;

  case 11:
#line 183 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_const_decl((yyvsp[(3) - (5)].sval), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
          free((yyvsp[(3) - (5)].sval));
      ;}
    break;

  case 12:
#line 191 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 13:
#line 195 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 14:
#line 199 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 15:
#line 203 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new_text(AST_CHAR_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 16:
#line 211 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 17:
#line 215 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 18:
#line 222 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_var_decl((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc))));
      ;}
    break;

  case 19:
#line 227 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_var_decl((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 20:
#line 234 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 21:
#line 238 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_array_type((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 22:
#line 245 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("integer", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 23:
#line 249 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("real", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 24:
#line 253 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("boolean", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 25:
#line 257 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_basic_type("char", AST_LOC((yylsp[(1) - (1)])));
      ;}
    break;

  case 26:
#line 264 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PERIOD_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_period((yyvsp[(1) - (3)].ival), (yyvsp[(3) - (3)].ival), AST_LOC((yyloc))));
      ;}
    break;

  case 27:
#line 269 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (5)].node), ast_make_period((yyvsp[(3) - (5)].ival), (yyvsp[(5) - (5)].ival), AST_LOC((yylsp[(3) - (5)]))));
      ;}
    break;

  case 28:
#line 276 "pascal_s_parser.y"
    {
          (yyval.ival) = (yyvsp[(1) - (1)].ival);
      ;}
    break;

  case 29:
#line 283 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 30:
#line 287 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
      ;}
    break;

  case 31:
#line 294 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 32:
#line 301 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(false, (yyvsp[(2) - (3)].sval), (yyvsp[(3) - (3)].node), NULL, AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 33:
#line 306 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_subprogram_head(true, (yyvsp[(2) - (5)].sval), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (5)].sval));
      ;}
    break;

  case 34:
#line 314 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      ;}
    break;

  case 35:
#line 318 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 36:
#line 325 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 37:
#line 330 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 38:
#line 337 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 39:
#line 341 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 40:
#line 348 "pascal_s_parser.y"
    {
          (yyvsp[(2) - (2)].node)->flag = true;
          (yyvsp[(2) - (2)].node)->loc = AST_LOC((yyloc));
          (yyval.node) = (yyvsp[(2) - (2)].node);
      ;}
    break;

  case 41:
#line 357 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_param_group(false, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 42:
#line 364 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_block((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc))), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 43:
#line 371 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_compound_stmt((yyvsp[(2) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 44:
#line 378 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 45:
#line 383 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 46:
#line 390 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_empty_stmt(AST_LOC((yyloc)));
      ;}
    break;

  case 47:
#line 394 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_assign_stmt((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 48:
#line 398 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 49:
#line 402 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 50:
#line 406 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node), NULL, AST_LOC((yyloc)));
      ;}
    break;

  case 51:
#line 410 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 52:
#line 414 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_for_stmt((yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].node), (yyvsp[(6) - (8)].node), (yyvsp[(8) - (8)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (8)].sval));
      ;}
    break;

  case 53:
#line 419 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_read_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 54:
#line 423 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_write_stmt((yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 55:
#line 430 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 56:
#line 435 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 57:
#line 442 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_var_ref((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (2)].sval));
      ;}
    break;

  case 58:
#line 450 "pascal_s_parser.y"
    {
          (yyval.node) = NULL;
      ;}
    break;

  case 59:
#line 454 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 60:
#line 461 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (1)].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[(1) - (1)].sval));
      ;}
    break;

  case 61:
#line 466 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 62:
#line 474 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[(1) - (1)].node));
      ;}
    break;

  case 63:
#line 479 "pascal_s_parser.y"
    {
          (yyval.node) = ast_append_list((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      ;}
    break;

  case 64:
#line 486 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 65:
#line 490 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 66:
#line 498 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 67:
#line 502 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 68:
#line 510 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 69:
#line 514 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), AST_LOC((yyloc)));
          free((yyvsp[(2) - (3)].sval));
      ;}
    break;

  case 70:
#line 522 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 71:
#line 526 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(1) - (1)].node);
      ;}
    break;

  case 72:
#line 530 "pascal_s_parser.y"
    {
          (yyval.node) = (yyvsp[(2) - (3)].node);
      ;}
    break;

  case 73:
#line 534 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), AST_LOC((yyloc)));
          free((yyvsp[(1) - (4)].sval));
      ;}
    break;

  case 74:
#line 539 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("not", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 75:
#line 543 "pascal_s_parser.y"
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[(2) - (2)].node), AST_LOC((yyloc)));
      ;}
    break;

  case 76:
#line 550 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("=");
      ;}
    break;

  case 77:
#line 554 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<>");
      ;}
    break;

  case 78:
#line 558 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<");
      ;}
    break;

  case 79:
#line 562 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("<=");
      ;}
    break;

  case 80:
#line 566 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">");
      ;}
    break;

  case 81:
#line 570 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text(">=");
      ;}
    break;

  case 82:
#line 577 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("+");
      ;}
    break;

  case 83:
#line 581 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("-");
      ;}
    break;

  case 84:
#line 585 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("or");
      ;}
    break;

  case 85:
#line 592 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("*");
      ;}
    break;

  case 86:
#line 596 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("/");
      ;}
    break;

  case 87:
#line 600 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("div");
      ;}
    break;

  case 88:
#line 604 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("mod");
      ;}
    break;

  case 89:
#line 608 "pascal_s_parser.y"
    {
          (yyval.sval) = dup_text("and");
      ;}
    break;

  case 90:
#line 615 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new_int(AST_INT_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].ival));
      ;}
    break;

  case 91:
#line 619 "pascal_s_parser.y"
    {
          (yyval.node) = ast_new_real(AST_REAL_LITERAL, AST_LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].fval));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2321 "pascal_s_parser.tab.c"
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


#line 624 "pascal_s_parser.y"


void yyerror(const char *msg) {
    g_parse_failed = 1;
    fprintf(stderr,
            "parse error at %d:%d: %s\n",
            yylloc.first_line,
            yylloc.first_column,
            msg);
}

AstNode *pascal_s_get_ast_root(void) {
    return g_ast_root;
}

AstNode *parse_pascal_stream(FILE *input) {
    g_parse_failed = 0;
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

