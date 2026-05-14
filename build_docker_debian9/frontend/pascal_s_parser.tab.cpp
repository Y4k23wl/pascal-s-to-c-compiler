/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "/work/frontend/pascal_s_parser.y" /* yacc.c:339  */

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

#line 123 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "pascal_s_parser.tab.h".  */
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
#line 61 "/work/frontend/pascal_s_parser.y" /* yacc.c:355  */

    char *sval;
    int ival;
    double fval;
    struct AstNode *node;

#line 230 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 261 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   145,   150,   158,   165,   170,   179,   182,
     189,   195,   203,   207,   211,   215,   220,   225,   229,   237,
     240,   247,   252,   259,   263,   270,   274,   278,   282,   289,
     294,   301,   309,   312,   319,   326,   331,   340,   343,   347,
     351,   363,   368,   375,   379,   386,   395,   402,   409,   413,
     425,   430,   434,   443,   456,   459,   463,   467,   471,   475,
     479,   483,   487,   492,   496,   505,   509,   521,   526,   533,
     542,   545,   549,   561,   566,   571,   576,   592,   597,   604,
     608,   616,   620,   628,   632,   640,   644,   648,   652,   657,
     670,   675,   679,   683,   688,   692,   696,   703,   707,   711,
     715,   719,   723,   730,   734,   738,   745,   749,   753,   757,
     761,   768,   772
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
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
  "term", "factor", "relop", "addop", "mulop", "num", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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

#define YYPACT_NINF -155

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-155)))

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
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

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,  -155,     7,   184,  -155,   206,   153,  -155,
     185,  -114,  -155,  -154,  -155,  -155,  -155,   204,  -155,    89,
    -155,   147,  -155,   -22,  -155,   -97,  -155,   -41,  -155,  -155,
     -77,   -58,   127,   128,   -73,  -155,  -155,  -155,    99
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,   114,    10,    14,    34,    17,    23,
      53,    54,   108,   109,    24,    42,    43,    77,   115,   116,
     117,   118,   106,    66,    67,    68,   147,    88,   100,    70,
     150,   151,    90,    91,    92,   135,   136,   142,    93
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
     '$$ = $1'.

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
#line 138 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_program((yyvsp[-3].node), (yyvsp[-1].node), AST_LOC((yyloc)));
          g_ast_root = (yyval.node);
      }
#line 1601 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 146 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_program_head((yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 1610 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 151 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_program_head((yyvsp[0].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 1619 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 159 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_block((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1627 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 166 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_identifier_list(ast_make_identifier((yyvsp[0].sval), AST_LOC((yylsp[0]))), AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 1636 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 171 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), ast_make_identifier((yyvsp[0].sval), AST_LOC((yylsp[0]))));
          free((yyvsp[0].sval));
      }
#line 1645 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 179 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
      }
#line 1653 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 183 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 1661 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 190 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_const_decl((yyvsp[-2].sval), (yyvsp[0].node), AST_LOC((yyloc))));
          free((yyvsp[-2].sval));
      }
#line 1671 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 196 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_const_decl((yyvsp[-2].sval), (yyvsp[0].node), AST_LOC((yylsp[-2]))));
          free((yyvsp[-2].sval));
      }
#line 1680 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 204 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1688 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 208 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1696 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 212 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1704 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 216 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new_text(AST_CHAR_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 1713 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 221 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 1722 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 226 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[0])));
      }
#line 1730 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 230 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[0])));
      }
#line 1738 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 237 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
      }
#line 1746 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 241 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 1754 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 248 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_var_decl((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc))));
      }
#line 1763 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 253 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_var_decl((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yylsp[-2]))));
      }
#line 1771 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 260 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1779 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 264 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_array_type((yyvsp[-3].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1787 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 271 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_basic_type("integer", AST_LOC((yylsp[0])));
      }
#line 1795 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 275 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_basic_type("real", AST_LOC((yylsp[0])));
      }
#line 1803 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 279 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_basic_type("boolean", AST_LOC((yylsp[0])));
      }
#line 1811 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 283 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_basic_type("char", AST_LOC((yylsp[0])));
      }
#line 1819 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 290 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_PERIOD_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_period((yyvsp[-2].ival), (yyvsp[0].ival), AST_LOC((yyloc))));
      }
#line 1828 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 295 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_period((yyvsp[-2].ival), (yyvsp[0].ival), AST_LOC((yylsp[-2]))));
      }
#line 1836 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 302 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.ival) = (yyvsp[0].ival);
      }
#line 1844 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 309 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc)));
      }
#line 1852 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 313 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[-1].node));
      }
#line 1860 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 320 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_subprogram((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1868 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 327 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_subprogram_head(false, (yyvsp[-1].sval), (yyvsp[0].node), NULL, AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 1877 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 332 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_subprogram_head(true, (yyvsp[-3].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 1886 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 340 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 1894 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 344 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 1902 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 348 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 1910 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 352 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "形参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 1923 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 364 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 1932 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 369 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1940 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 376 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1948 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 380 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1956 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 387 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyvsp[0].node)->flag = true;
          (yyvsp[0].node)->loc = AST_LOC((yyloc));
          (yyval.node) = (yyvsp[0].node);
      }
#line 1966 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 396 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_param_group(false, (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1974 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 403 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_block((yyvsp[-2].node), (yyvsp[-1].node), ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc))), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1982 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 410 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_compound_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 1990 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 414 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "复合语句内部存在语法错误，已恢复到 end");
          yyerrok;
          (yyval.node) = ast_make_compound_stmt(ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2003 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 426 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2012 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 431 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2020 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 435 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[0]).first_line,
                         (yylsp[0]).first_column,
                         "语法恢复",
                         "语句存在语法错误，已跳过到下一个分号或 end 后继续");
          yyerrok;
          (yyval.node) = (yyvsp[-2].node);
      }
#line 2033 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 444 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "语句之间可能缺少分号，已恢复并继续");
          yyerrok;
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2046 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 456 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_empty_stmt(AST_LOC((yyloc)));
      }
#line 2054 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 460 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_assign_stmt((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2062 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 464 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2070 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 468 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_break_stmt(AST_LOC((yylsp[0])));
      }
#line 2078 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 472 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2086 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 476 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[-2].node), (yyvsp[0].node), NULL, AST_LOC((yyloc)));
      }
#line 2094 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 480 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_if_stmt((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2102 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 484 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_while_stmt((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2110 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 488 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_for_stmt((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-6].sval));
      }
#line 2119 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 493 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_read_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 2127 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 497 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "read 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_read_stmt(ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2140 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 506 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_write_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 2148 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 510 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "write 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_write_stmt(ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2161 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 522 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2170 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 527 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2178 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 534 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_var_ref((yyvsp[-1].sval), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2187 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 542 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = NULL;
      }
#line 2195 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 546 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2203 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 550 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "数组下标列表存在语法错误，已恢复到右中括号");
          yyerrok;
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
      }
#line 2216 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 562 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[0].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 2225 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 567 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[-2].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[-2].sval));
      }
#line 2234 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 572 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2243 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 577 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_call(AST_CALL_STMT,
                             (yyvsp[-3].sval),
                             ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))),
                             AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2260 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 593 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2269 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 598 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2277 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 605 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2285 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 609 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2294 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 617 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2302 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 621 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2311 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 629 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2319 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 633 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2328 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 641 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2336 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 645 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2344 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 649 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2352 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 653 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2361 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 658 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "函数调用实参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_call(AST_CALL_EXPR,
                             (yyvsp[-3].sval),
                             ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))),
                             AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2378 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 671 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[-2].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[-2].sval));
      }
#line 2387 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 676 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[0])));
      }
#line 2395 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 680 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[0])));
      }
#line 2403 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 684 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 2412 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 689 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_unary_expr("not", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2420 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 693 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_unary_expr("+", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2428 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 697 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2436 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 704 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("=");
      }
#line 2444 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 708 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("<>");
      }
#line 2452 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 712 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("<");
      }
#line 2460 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 716 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("<=");
      }
#line 2468 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 720 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text(">");
      }
#line 2476 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 724 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text(">=");
      }
#line 2484 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 731 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("+");
      }
#line 2492 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 735 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("-");
      }
#line 2500 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 739 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("or");
      }
#line 2508 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 746 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("*");
      }
#line 2516 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 750 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("/");
      }
#line 2524 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 754 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("div");
      }
#line 2532 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 758 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("mod");
      }
#line 2540 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 762 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.sval) = dup_text("and");
      }
#line 2548 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 769 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new_int(AST_INT_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].ival));
      }
#line 2556 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 773 "/work/frontend/pascal_s_parser.y" /* yacc.c:1646  */
    {
          (yyval.node) = ast_new_real(AST_REAL_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].fval));
      }
#line 2564 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 2568 "/work/build_docker_debian9/frontend/pascal_s_parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 778 "/work/frontend/pascal_s_parser.y" /* yacc.c:1906  */


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
