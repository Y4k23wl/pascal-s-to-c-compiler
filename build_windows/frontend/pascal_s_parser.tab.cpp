/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"

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

#line 128 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "pascal_s_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_CONST = 4,                      /* CONST  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_PROCEDURE = 6,                  /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 7,                   /* FUNCTION  */
  YYSYMBOL_BEGIN_KW = 8,                   /* BEGIN_KW  */
  YYSYMBOL_END_KW = 9,                     /* END_KW  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_TO = 14,                        /* TO  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_WHILE = 16,                     /* WHILE  */
  YYSYMBOL_BREAK = 17,                     /* BREAK  */
  YYSYMBOL_READ = 18,                      /* READ  */
  YYSYMBOL_WRITE = 19,                     /* WRITE  */
  YYSYMBOL_ARRAY = 20,                     /* ARRAY  */
  YYSYMBOL_OF = 21,                        /* OF  */
  YYSYMBOL_INTEGER = 22,                   /* INTEGER  */
  YYSYMBOL_REAL = 23,                      /* REAL  */
  YYSYMBOL_BOOLEAN = 24,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 25,                      /* CHAR  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_TRUE = 27,                      /* TRUE  */
  YYSYMBOL_FALSE = 28,                     /* FALSE  */
  YYSYMBOL_DIV = 29,                       /* DIV  */
  YYSYMBOL_MOD = 30,                       /* MOD  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_ID = 33,                        /* ID  */
  YYSYMBOL_INT_CONST = 34,                 /* INT_CONST  */
  YYSYMBOL_REAL_CONST = 35,                /* REAL_CONST  */
  YYSYMBOL_CHAR_CONST = 36,                /* CHAR_CONST  */
  YYSYMBOL_STRING_CONST = 37,              /* STRING_CONST  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_NE = 40,                        /* NE  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_PLUS = 45,                      /* PLUS  */
  YYSYMBOL_MINUS = 46,                     /* MINUS  */
  YYSYMBOL_MUL = 47,                       /* MUL  */
  YYSYMBOL_SLASH = 48,                     /* SLASH  */
  YYSYMBOL_SEMICOLON = 49,                 /* SEMICOLON  */
  YYSYMBOL_DOT = 50,                       /* DOT  */
  YYSYMBOL_COMMA = 51,                     /* COMMA  */
  YYSYMBOL_LPAREN = 52,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 53,                    /* RPAREN  */
  YYSYMBOL_LBRACK = 54,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 55,                    /* RBRACK  */
  YYSYMBOL_COLON = 56,                     /* COLON  */
  YYSYMBOL_RANGE = 57,                     /* RANGE  */
  YYSYMBOL_LOWER_THAN_ELSE = 58,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UMINUS = 59,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_programstruct = 61,             /* programstruct  */
  YYSYMBOL_program_head = 62,              /* program_head  */
  YYSYMBOL_program_body = 63,              /* program_body  */
  YYSYMBOL_idlist = 64,                    /* idlist  */
  YYSYMBOL_const_declarations = 65,        /* const_declarations  */
  YYSYMBOL_const_declaration = 66,         /* const_declaration  */
  YYSYMBOL_const_value = 67,               /* const_value  */
  YYSYMBOL_var_declarations = 68,          /* var_declarations  */
  YYSYMBOL_var_declaration = 69,           /* var_declaration  */
  YYSYMBOL_type = 70,                      /* type  */
  YYSYMBOL_basic_type = 71,                /* basic_type  */
  YYSYMBOL_period = 72,                    /* period  */
  YYSYMBOL_digits = 73,                    /* digits  */
  YYSYMBOL_subprogram_declarations = 74,   /* subprogram_declarations  */
  YYSYMBOL_subprogram = 75,                /* subprogram  */
  YYSYMBOL_subprogram_head = 76,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 77,          /* formal_parameter  */
  YYSYMBOL_parameter_list = 78,            /* parameter_list  */
  YYSYMBOL_parameter = 79,                 /* parameter  */
  YYSYMBOL_var_parameter = 80,             /* var_parameter  */
  YYSYMBOL_value_parameter = 81,           /* value_parameter  */
  YYSYMBOL_subprogram_body = 82,           /* subprogram_body  */
  YYSYMBOL_compound_statement = 83,        /* compound_statement  */
  YYSYMBOL_statement_list = 84,            /* statement_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_variable_list = 86,             /* variable_list  */
  YYSYMBOL_variable = 87,                  /* variable  */
  YYSYMBOL_id_varpart = 88,                /* id_varpart  */
  YYSYMBOL_procedure_call = 89,            /* procedure_call  */
  YYSYMBOL_expression_list = 90,           /* expression_list  */
  YYSYMBOL_expression = 91,                /* expression  */
  YYSYMBOL_simple_expression = 92,         /* simple_expression  */
  YYSYMBOL_term = 93,                      /* term  */
  YYSYMBOL_factor = 94,                    /* factor  */
  YYSYMBOL_relop = 95,                     /* relop  */
  YYSYMBOL_addop = 96,                     /* addop  */
  YYSYMBOL_mulop = 97,                     /* mulop  */
  YYSYMBOL_num = 98                        /* num  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "CONST",
  "VAR", "PROCEDURE", "FUNCTION", "BEGIN_KW", "END_KW", "IF", "THEN",
  "ELSE", "FOR", "TO", "DO", "WHILE", "BREAK", "READ", "WRITE", "ARRAY",
  "OF", "INTEGER", "REAL", "BOOLEAN", "CHAR", "NOT", "TRUE", "FALSE",
  "DIV", "MOD", "AND", "OR", "ID", "INT_CONST", "REAL_CONST", "CHAR_CONST",
  "STRING_CONST", "ASSIGN", "EQ", "NE", "LT", "LE", "GT", "GE", "PLUS",
  "MINUS", "MUL", "SLASH", "SEMICOLON", "DOT", "COMMA", "LPAREN", "RPAREN",
  "LBRACK", "RBRACK", "COLON", "RANGE", "LOWER_THAN_ELSE", "UMINUS",
  "$accept", "programstruct", "program_head", "program_body", "idlist",
  "const_declarations", "const_declaration", "const_value",
  "var_declarations", "var_declaration", "type", "basic_type", "period",
  "digits", "subprogram_declarations", "subprogram", "subprogram_head",
  "formal_parameter", "parameter_list", "parameter", "var_parameter",
  "value_parameter", "subprogram_body", "compound_statement",
  "statement_list", "statement", "variable_list", "variable", "id_varpart",
  "procedure_call", "expression_list", "expression", "simple_expression",
  "term", "factor", "relop", "addop", "mulop", "num", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-155)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
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
static const yytype_int8 yydefact[] =
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
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     9,   114,    10,    14,    34,    17,    23,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programstruct: program_head SEMICOLON program_body DOT  */
#line 138 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_program((yyvsp[-3].node), (yyvsp[-1].node), AST_LOC((yyloc)));
          g_ast_root = (yyval.node);
      }
#line 1761 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 3: /* program_head: PROGRAM ID LPAREN idlist RPAREN  */
#line 146 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_program_head((yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 1770 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 4: /* program_head: PROGRAM ID  */
#line 151 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_program_head((yyvsp[0].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 1779 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 5: /* program_body: const_declarations var_declarations subprogram_declarations compound_statement  */
#line 159 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_block((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1787 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 6: /* idlist: ID  */
#line 166 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_identifier_list(ast_make_identifier((yyvsp[0].sval), AST_LOC((yylsp[0]))), AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 1796 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 7: /* idlist: idlist COMMA ID  */
#line 171 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), ast_make_identifier((yyvsp[0].sval), AST_LOC((yylsp[0]))));
          free((yyvsp[0].sval));
      }
#line 1805 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 8: /* const_declarations: %empty  */
#line 179 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
      }
#line 1813 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 9: /* const_declarations: CONST const_declaration SEMICOLON  */
#line 183 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 1821 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 10: /* const_declaration: ID EQ const_value  */
#line 190 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_CONST_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_const_decl((yyvsp[-2].sval), (yyvsp[0].node), AST_LOC((yyloc))));
          free((yyvsp[-2].sval));
      }
#line 1831 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 11: /* const_declaration: const_declaration SEMICOLON ID EQ const_value  */
#line 196 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_const_decl((yyvsp[-2].sval), (yyvsp[0].node), AST_LOC((yylsp[-2]))));
          free((yyvsp[-2].sval));
      }
#line 1840 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 12: /* const_value: PLUS num  */
#line 204 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1848 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 13: /* const_value: MINUS num  */
#line 208 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1856 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 14: /* const_value: num  */
#line 212 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1864 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 15: /* const_value: CHAR_CONST  */
#line 216 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new_text(AST_CHAR_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 1873 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 16: /* const_value: STRING_CONST  */
#line 221 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 1882 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 17: /* const_value: TRUE  */
#line 226 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[0])));
      }
#line 1890 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 18: /* const_value: FALSE  */
#line 230 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[0])));
      }
#line 1898 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 19: /* var_declarations: %empty  */
#line 237 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
      }
#line 1906 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 20: /* var_declarations: VAR var_declaration SEMICOLON  */
#line 241 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 1914 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 21: /* var_declaration: idlist COLON type  */
#line 248 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_VAR_DECL_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_var_decl((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc))));
      }
#line 1923 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 22: /* var_declaration: var_declaration SEMICOLON idlist COLON type  */
#line 253 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_var_decl((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yylsp[-2]))));
      }
#line 1931 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 23: /* type: basic_type  */
#line 260 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1939 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 24: /* type: ARRAY LBRACK period RBRACK OF basic_type  */
#line 264 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_array_type((yyvsp[-3].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 1947 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 25: /* basic_type: INTEGER  */
#line 271 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_basic_type("integer", AST_LOC((yylsp[0])));
      }
#line 1955 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 26: /* basic_type: REAL  */
#line 275 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_basic_type("real", AST_LOC((yylsp[0])));
      }
#line 1963 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 27: /* basic_type: BOOLEAN  */
#line 279 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_basic_type("boolean", AST_LOC((yylsp[0])));
      }
#line 1971 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 28: /* basic_type: CHAR  */
#line 283 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_basic_type("char", AST_LOC((yylsp[0])));
      }
#line 1979 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 29: /* period: digits RANGE digits  */
#line 290 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_PERIOD_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), ast_make_period((yyvsp[-2].ival), (yyvsp[0].ival), AST_LOC((yyloc))));
      }
#line 1988 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 30: /* period: period COMMA digits RANGE digits  */
#line 295 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-4].node), ast_make_period((yyvsp[-2].ival), (yyvsp[0].ival), AST_LOC((yylsp[-2]))));
      }
#line 1996 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 31: /* digits: INT_CONST  */
#line 302 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.ival) = (yyvsp[0].ival);
      }
#line 2004 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 32: /* subprogram_declarations: %empty  */
#line 309 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc)));
      }
#line 2012 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 33: /* subprogram_declarations: subprogram_declarations subprogram SEMICOLON  */
#line 313 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[-1].node));
      }
#line 2020 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 34: /* subprogram: subprogram_head SEMICOLON subprogram_body  */
#line 320 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_subprogram((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2028 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 35: /* subprogram_head: PROCEDURE ID formal_parameter  */
#line 327 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_subprogram_head(false, (yyvsp[-1].sval), (yyvsp[0].node), NULL, AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2037 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 36: /* subprogram_head: FUNCTION ID formal_parameter COLON basic_type  */
#line 332 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_subprogram_head(true, (yyvsp[-3].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2046 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 37: /* formal_parameter: %empty  */
#line 340 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 2054 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 38: /* formal_parameter: LPAREN RPAREN  */
#line 344 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 2062 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 39: /* formal_parameter: LPAREN parameter_list RPAREN  */
#line 348 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2070 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 40: /* formal_parameter: LPAREN error RPAREN  */
#line 352 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "形参列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
      }
#line 2083 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 41: /* parameter_list: parameter  */
#line 364 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_PARAM_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2092 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 42: /* parameter_list: parameter_list SEMICOLON parameter  */
#line 369 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2100 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 43: /* parameter: var_parameter  */
#line 376 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2108 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 44: /* parameter: value_parameter  */
#line 380 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2116 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 45: /* var_parameter: VAR value_parameter  */
#line 387 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyvsp[0].node)->flag = true;
          (yyvsp[0].node)->loc = AST_LOC((yyloc));
          (yyval.node) = (yyvsp[0].node);
      }
#line 2126 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 46: /* value_parameter: idlist COLON basic_type  */
#line 396 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_param_group(false, (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2134 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 47: /* subprogram_body: const_declarations var_declarations compound_statement  */
#line 403 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_block((yyvsp[-2].node), (yyvsp[-1].node), ast_new(AST_SUBPROGRAM_LIST, AST_LOC((yyloc))), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2142 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 48: /* compound_statement: BEGIN_KW statement_list END_KW  */
#line 410 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_compound_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 2150 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 49: /* compound_statement: BEGIN_KW error END_KW  */
#line 414 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "复合语句内部存在语法错误，已恢复到 end");
          yyerrok;
          (yyval.node) = ast_make_compound_stmt(ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2163 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 50: /* statement_list: statement  */
#line 426 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_STATEMENT_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2172 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 51: /* statement_list: statement_list SEMICOLON statement  */
#line 431 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2180 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 52: /* statement_list: statement_list SEMICOLON error  */
#line 435 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[0]).first_line,
                         (yylsp[0]).first_column,
                         "语法恢复",
                         "语句存在语法错误，已跳过到下一个分号或 end 后继续");
          (yyval.node) = (yyvsp[-2].node);
      }
#line 2192 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 53: /* statement_list: statement_list error statement  */
#line 443 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "语句之间可能缺少分号，已恢复并继续");
          yyerrok;
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2205 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 54: /* statement: %empty  */
#line 455 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_empty_stmt(AST_LOC((yyloc)));
      }
#line 2213 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 55: /* statement: variable ASSIGN expression  */
#line 459 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_assign_stmt((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2221 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 56: /* statement: procedure_call  */
#line 463 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2229 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 57: /* statement: BREAK  */
#line 467 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_break_stmt(AST_LOC((yylsp[0])));
      }
#line 2237 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 58: /* statement: compound_statement  */
#line 471 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2245 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 59: /* statement: IF expression THEN statement  */
#line 475 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_if_stmt((yyvsp[-2].node), (yyvsp[0].node), NULL, AST_LOC((yyloc)));
      }
#line 2253 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 60: /* statement: IF expression THEN statement ELSE statement  */
#line 479 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_if_stmt((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2261 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 61: /* statement: WHILE expression DO statement  */
#line 483 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_while_stmt((yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2269 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 62: /* statement: FOR ID ASSIGN expression TO expression DO statement  */
#line 487 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_for_stmt((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-6].sval));
      }
#line 2278 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 63: /* statement: READ LPAREN variable_list RPAREN  */
#line 492 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_read_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 2286 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 64: /* statement: READ LPAREN error RPAREN  */
#line 496 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "read 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_read_stmt(ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2299 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 65: /* statement: WRITE LPAREN expression_list RPAREN  */
#line 505 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_write_stmt((yyvsp[-1].node), AST_LOC((yyloc)));
      }
#line 2307 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 66: /* statement: WRITE LPAREN error RPAREN  */
#line 509 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "write 参数列表存在语法错误，已恢复到右括号");
          yyerrok;
          (yyval.node) = ast_make_write_stmt(ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc))), AST_LOC((yyloc)));
      }
#line 2320 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 67: /* variable_list: variable  */
#line 521 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_VARIABLE_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2329 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 68: /* variable_list: variable_list COMMA variable  */
#line 526 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2337 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 69: /* variable: ID id_varpart  */
#line 533 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_var_ref((yyvsp[-1].sval), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2346 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 70: /* id_varpart: %empty  */
#line 541 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2354 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 71: /* id_varpart: LBRACK expression_list RBRACK  */
#line 545 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2362 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 72: /* id_varpart: LBRACK error RBRACK  */
#line 549 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          parser_note_at((yylsp[-1]).first_line,
                         (yylsp[-1]).first_column,
                         "语法恢复",
                         "数组下标列表存在语法错误，已恢复到右中括号");
          yyerrok;
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
      }
#line 2375 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 73: /* procedure_call: ID  */
#line 561 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[0].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[0].sval));
      }
#line 2384 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 74: /* procedure_call: ID LPAREN RPAREN  */
#line 566 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[-2].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[-2].sval));
      }
#line 2393 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 75: /* procedure_call: ID LPAREN expression_list RPAREN  */
#line 571 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_call(AST_CALL_STMT, (yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2402 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 76: /* procedure_call: ID LPAREN error RPAREN  */
#line 576 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
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
#line 2419 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 77: /* expression_list: expression  */
#line 592 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new(AST_EXPRESSION_LIST, AST_LOC((yyloc)));
          ast_append_list((yyval.node), (yyvsp[0].node));
      }
#line 2428 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 78: /* expression_list: expression_list COMMA expression  */
#line 597 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_append_list((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2436 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 79: /* expression: simple_expression  */
#line 604 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2444 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 80: /* expression: simple_expression relop simple_expression  */
#line 608 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2453 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 81: /* simple_expression: term  */
#line 616 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2461 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 82: /* simple_expression: simple_expression addop term  */
#line 620 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2470 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 83: /* term: factor  */
#line 628 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2478 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 84: /* term: term mulop factor  */
#line 632 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_binary_expr((yyvsp[-1].sval), (yyvsp[-2].node), (yyvsp[0].node), AST_LOC((yyloc)));
          free((yyvsp[-1].sval));
      }
#line 2487 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 85: /* factor: num  */
#line 640 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2495 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 86: /* factor: variable  */
#line 644 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2503 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 87: /* factor: LPAREN expression RPAREN  */
#line 648 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2511 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 88: /* factor: ID LPAREN expression_list RPAREN  */
#line 652 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[-3].sval), (yyvsp[-1].node), AST_LOC((yyloc)));
          free((yyvsp[-3].sval));
      }
#line 2520 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 89: /* factor: ID LPAREN error RPAREN  */
#line 657 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
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
#line 2537 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 90: /* factor: ID LPAREN RPAREN  */
#line 670 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_call(AST_CALL_EXPR, (yyvsp[-2].sval), NULL, AST_LOC((yyloc)));
          free((yyvsp[-2].sval));
      }
#line 2546 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 91: /* factor: TRUE  */
#line 675 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_bool_literal(true, AST_LOC((yylsp[0])));
      }
#line 2554 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 92: /* factor: FALSE  */
#line 679 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_bool_literal(false, AST_LOC((yylsp[0])));
      }
#line 2562 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 93: /* factor: STRING_CONST  */
#line 683 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new_text(AST_STRING_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].sval));
          free((yyvsp[0].sval));
      }
#line 2571 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 94: /* factor: NOT factor  */
#line 688 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_unary_expr("not", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2579 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 95: /* factor: PLUS factor  */
#line 692 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_unary_expr("+", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2587 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 96: /* factor: MINUS factor  */
#line 696 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_make_unary_expr("-", (yyvsp[0].node), AST_LOC((yyloc)));
      }
#line 2595 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 97: /* relop: EQ  */
#line 703 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("=");
      }
#line 2603 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 98: /* relop: NE  */
#line 707 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("<>");
      }
#line 2611 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 99: /* relop: LT  */
#line 711 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("<");
      }
#line 2619 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 100: /* relop: LE  */
#line 715 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("<=");
      }
#line 2627 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 101: /* relop: GT  */
#line 719 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text(">");
      }
#line 2635 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 102: /* relop: GE  */
#line 723 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text(">=");
      }
#line 2643 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 103: /* addop: PLUS  */
#line 730 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("+");
      }
#line 2651 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 104: /* addop: MINUS  */
#line 734 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("-");
      }
#line 2659 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 105: /* addop: OR  */
#line 738 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("or");
      }
#line 2667 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 106: /* mulop: MUL  */
#line 745 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("*");
      }
#line 2675 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 107: /* mulop: SLASH  */
#line 749 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("/");
      }
#line 2683 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 108: /* mulop: DIV  */
#line 753 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("div");
      }
#line 2691 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 109: /* mulop: MOD  */
#line 757 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("mod");
      }
#line 2699 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 110: /* mulop: AND  */
#line 761 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.sval) = dup_text("and");
      }
#line 2707 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 111: /* num: INT_CONST  */
#line 768 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new_int(AST_INT_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].ival));
      }
#line 2715 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;

  case 112: /* num: REAL_CONST  */
#line 772 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"
      {
          (yyval.node) = ast_new_real(AST_REAL_LITERAL, AST_LOC((yylsp[0])), (yyvsp[0].fval));
      }
#line 2723 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"
    break;


#line 2727 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/build/frontend/pascal_s_parser.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 777 "C:/Users/A/Desktop/pascal-s-to-c-compiler-main/frontend/pascal_s_parser.y"


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
