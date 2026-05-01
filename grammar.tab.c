/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar.y"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <optional>
#include <vector>
#include <string>
#include <map>

extern int yylex();
extern int yyparse();

void parsing_failure();

extern FILE* yyin;
extern FILE* yyout;

int last_label = 0;

typedef struct {
    int last_id = -1;
    std::map<std::string, int> variables;
} Scope;

std::vector<Scope> scopes;
std::vector<std::vector<int>> if_label_ids;
std::vector<int> for_label_ids;

int variable_lookup(const std::string& name);
int find_last_taken_id();
int create_variable(const std::string& name);

void yyerror(const char* s);

void write_reg_operation(int addr_dest) {
    fprintf(yyout, "WRITE [%d], ax\n", addr_dest);
}

void write_num_operation(int addr_dest, int num) {
    fprintf(yyout, "WRITE [%d], %d\n", addr_dest, num);
}

void load_operation(int addr_src) {
    fprintf(yyout, "LOAD ax, [%d]\n", addr_src);
}

void push_num_operation(int num) {
    fprintf(yyout, "PUSH %d\n", num);
}

void push_reg_operation() {
    fprintf(yyout, "PUSH ax\n");
}

void pop_operation() {
    fprintf(yyout, "POP ax\n");
}

void sum_operation() {
    fprintf(yyout, "SUM\n");
}

void sub_operation() {
    fprintf(yyout, "SUB\n");
}

void mul_operation() {
    fprintf(yyout, "MUL\n");
}

void div_operation() {
    fprintf(yyout, "DIV\n");
}

void mod_operation() {
    fprintf(yyout, "MOD\n");
}

void or_operation() {
    fprintf(yyout, "OR\n");
}

void xor_operation() {
    fprintf(yyout, "XOR\n");
}

void and_operation() {
    fprintf(yyout, "AND\n");
}

void lshift_operation() {
    fprintf(yyout, "LSHIFT\n");
}

void rshift_operation() {
    fprintf(yyout, "RSHIFT\n");
}

void logical_or_operation() {
    fprintf(yyout, "CMP OR\n");
}

void logical_and_operation() {
    fprintf(yyout, "CMPLAND\n");
}

void and_not_operation() {
    fprintf(yyout, "CMP ANDNOT\n");
}

void equal_operation() {
    fprintf(yyout, "CMP EQ\n");
}

void not_equal_operation() {
    fprintf(yyout, "CMP NEQ\n");
}

void lower_operation() {
    fprintf(yyout, "CMP LW\n");
}

void greater_operation() {
    fprintf(yyout, "CMP GT\n");
}

void lower_or_equal_operation() {
    fprintf(yyout, "CMP LWEQ\n");
}

void greater_or_equal_operation() {
    fprintf(yyout, "CMP GTEQ\n");
}

void print_operation() {
    fprintf(yyout, "PRINT ax\n");
}

void label_operation(int label_num) {
    fprintf(yyout, "\n%d:\n", label_num);
}

void jmp_operation(int label_num) {
    fprintf(yyout, "JMP %d\n", label_num);
}

void halt_operation() {
    fprintf(yyout, "HALT\n");
}

void cmp_operation() {
    fprintf(yyout, "CMP\n");
}

void jmp_equal_operation(int label_num) {
    fprintf(yyout, "JMPEQ %d\n", label_num);
}


#line 231 "grammar.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
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
    INT = 258,
    UINT = 259,
    INT8 = 260,
    INT16 = 261,
    INT32 = 262,
    INT64 = 263,
    UINT8 = 264,
    UINT16 = 265,
    UINT32 = 266,
    UINT64 = 267,
    NL = 268,
    PACKAGE = 269,
    FUNC = 270,
    VAR = 271,
    SEMICOLON = 272,
    IF = 273,
    ELSE = 274,
    FOR = 275,
    BREAK = 276,
    CONTINUE = 277,
    RETURN = 278,
    EQ = 279,
    NE = 280,
    LE = 281,
    GE = 282,
    LAND = 283,
    LOR = 284,
    ANDNOT = 285,
    LSHIFT = 286,
    RSHIFT = 287,
    PLUSEQ = 288,
    MINUSEQ = 289,
    STAREQ = 290,
    DIVEQ = 291,
    MODEQ = 292,
    ANDEQ = 293,
    OREQ = 294,
    XOREQ = 295,
    LSHIFTEQ = 296,
    RSHIFTEQ = 297,
    ANDNOTEQ = 298,
    DEFINE = 299,
    INC = 300,
    DEC = 301,
    PRINT = 302,
    NUMBER = 303,
    NAME = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 162 "grammar.y"

    int element_count;
    int val;
    char *str;

#line 339 "grammar.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   338

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  311

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,     2,     2,    62,    63,     2,
      50,    51,    60,    56,    53,    57,     2,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      64,    52,    65,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,    58,    55,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   193,   193,   194,   197,   198,   199,   202,   203,   208,
     211,   217,   218,   221,   222,   223,   226,   232,   239,   249,
     254,   261,   262,   266,   276,   280,   281,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   297,   307,   308,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     326,   330,   336,   342,   348,   351,   352,   355,   358,   361,
     366,   367,   370,   373,   376,   379,   382,   385,   390,   391,
     392,   398,   405,   408,   413,   416,   420,   423,   424,   429,
     430,   435,   436,   439,   444,   445,   448,   451,   454,   459,
     460,   463,   466,   469,   474,   475,   478,   481,   484,   487,
     490,   493,   499,   500,   506,   507,   513,   520,   524,   529,
     532,   536,   539,   545,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   566,   567,   568,   569,   570,
     571,   572,   573,   574,   575,   576,   577,   581,   590,   603,
     613,   625,   637,   645,   646,   647,   648,   651,   660,   661,
     662,   665,   676,   684,   685,   686,   687,   690,   699,   700,
     701,   704,   713,   720,   728,   737,   748,   757,   766,   777,
     780,   785,   786,   793,   794,   795,   799
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "UINT", "INT8", "INT16", "INT32",
  "INT64", "UINT8", "UINT16", "UINT32", "UINT64", "NL", "PACKAGE", "FUNC",
  "VAR", "SEMICOLON", "IF", "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN",
  "EQ", "NE", "LE", "GE", "LAND", "LOR", "ANDNOT", "LSHIFT", "RSHIFT",
  "PLUSEQ", "MINUSEQ", "STAREQ", "DIVEQ", "MODEQ", "ANDEQ", "OREQ",
  "XOREQ", "LSHIFTEQ", "RSHIFTEQ", "ANDNOTEQ", "DEFINE", "INC", "DEC",
  "PRINT", "NUMBER", "NAME", "'('", "')'", "'='", "','", "'{'", "'}'",
  "'+'", "'-'", "'|'", "'^'", "'*'", "'/'", "'%'", "'&'", "'<'", "'>'",
  "'!'", "$accept", "program", "package_clause", "global_decls",
  "global_decl", "func_token", "main_decl", "var_decl", "var_spec_list",
  "var_spec", "identifier_list", "expression_list", "short_var_decl",
  "type", "statement_list", "statement", "block", "loop_statement_list",
  "loop_statement", "loop_block", "continue_stmt", "break_stmt",
  "return_stmt", "expression", "additive_expr", "multiplicative_expr",
  "unary_expr", "primary_expr", "operand", "logical_expression",
  "logical_expression_or", "logical_expression_and",
  "logical_equality_expr", "logical_relational_expr",
  "logical_additive_expr", "logical_multiplicative_expr",
  "logical_unary_expr", "logical_primary_expr", "logical_operand",
  "variable_assignment", "assignment", "logical_assignment",
  "inc_dec_stmt", "if_token", "else_if_token", "else_token", "if_stmt",
  "elif_stmt", "else_stmt", "if_stmt_loop", "elif_stmt_loop",
  "else_stmt_loop", "if_comparison", "if_block", "if_loop_block",
  "for_token", "for_stmt", "for_var_init", "for_comparison", "for_post",
  "print_stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      40,    41,    61,    44,   123,   125,    43,    45,   124,    94,
      42,    47,    37,    38,    60,    62,    33
};
# endif

#define YYPACT_NINF (-238)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-165)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      19,   -11,    42,    16,    28,  -238,  -238,    -1,  -238,    41,
      18,  -238,  -238,  -238,    20,    25,  -238,    17,    16,    32,
      25,    30,    74,  -238,    38,    40,  -238,    45,  -238,  -238,
      25,  -238,  -238,    38,    38,    38,    38,  -238,    61,    54,
      70,  -238,  -238,  -238,    38,    62,  -238,    47,  -238,  -238,
    -238,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,  -238,   202,  -238,  -238,  -238,    70,    70,
      70,    70,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,    67,   247,  -238,     0,  -238,     5,  -238,  -238,
    -238,  -238,   260,  -238,   248,  -238,  -238,    75,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,  -238,
    -238,    38,    38,   202,  -238,  -238,   -14,    38,   272,   272,
     272,   272,    81,   101,  -238,    97,   106,    31,    14,    64,
     145,  -238,  -238,  -238,    62,   179,  -238,  -238,    82,   112,
      84,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,    87,  -238,  -238,  -238,  -238,
    -238,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   121,   122,  -238,  -238,  -238,   105,  -238,     8,  -238,
    -238,  -238,  -238,  -238,  -238,   260,  -238,  -238,  -238,  -238,
     272,  -238,  -238,    62,   106,    31,    14,    14,    64,    64,
      64,    64,   145,   145,   145,   145,  -238,  -238,  -238,  -238,
    -238,  -238,  -238,   140,   260,    62,  -238,  -238,   179,  -238,
     146,    82,  -238,   148,  -238,   122,  -238,   149,    62,  -238,
    -238,   272,   143,   122,   124,  -238,  -238,   272,   121,   122,
      82,   260,    82,  -238,  -238,   226,  -238,  -238,  -238,    82,
      62,  -238,  -238,  -238,   122,   161,    82,  -238,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   130,
     131,  -238,   163,  -238,  -238,   272,   143,   122,  -238,  -238,
    -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,  -238,
       9,   150,   140,  -238,    82,  -238,  -238,   147,   163,  -238,
    -238
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     9,     0,     2,     5,
       0,     8,     7,     3,    19,     0,    11,     0,     4,     0,
       0,     0,    13,    24,     0,    16,     6,     0,    20,    12,
      14,    74,    73,     0,     0,     0,     0,    18,    21,    54,
      55,    60,    68,    72,     0,     0,    15,     0,    69,    70,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,    27,    10,    75,    22,    56,    57,
      58,    59,    67,    64,    65,    61,    62,    63,    66,   139,
     165,    53,     0,    19,    28,     0,    33,     0,    25,    35,
      29,    30,     0,    31,   169,    32,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     138,     0,     0,    27,    36,   109,   108,     0,     0,     0,
       0,     0,     0,     0,   162,    76,    77,    79,    81,    84,
      89,    94,   102,   107,     0,    39,   170,   166,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,    23,   113,    26,     0,   108,   104,   105,   106,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,     0,    52,    51,    40,     0,    44,     0,    37,
      46,    45,    47,    41,    42,     0,    48,    43,    49,   167,
     171,   176,   110,     0,    78,    80,    82,    83,    87,    88,
      85,    86,    90,    91,    92,    93,   101,    98,    99,    95,
      96,    97,   100,   141,     0,     0,   143,   144,    39,    50,
       0,     0,   172,     0,   163,     0,   140,     0,     0,   151,
      38,     0,   152,     0,   173,   145,   146,     0,   147,     0,
       0,     0,     0,   153,   154,     0,   125,   174,   175,     0,
       0,   148,   149,   164,     0,     0,     0,   161,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,     0,   155,   156,     0,   157,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   111,
       0,     0,     0,   150,     0,   158,   159,     0,     0,   112,
     160
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -238,  -238,  -238,   180,  -238,  -238,  -238,   -60,   174,   210,
      -7,   -27,   -87,  -238,  -238,   110,   -44,  -238,    -9,   -92,
    -238,  -238,  -129,    44,  -238,   117,   196,  -238,  -238,   -85,
    -238,    65,    66,  -100,    68,    69,    35,  -238,  -238,   -56,
    -124,  -238,  -125,  -123,  -228,  -217,  -238,  -214,  -206,  -238,
    -237,  -236,  -158,  -184,  -232,  -238,  -121,  -238,  -238,  -238,
    -119
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     8,     9,    10,    11,    12,    21,    22,
     122,    37,    86,    25,    87,    88,   187,   188,   189,   263,
     190,   191,    89,    38,    39,    40,    41,    42,    43,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   256,
      90,   257,    91,    92,   224,   225,    93,   226,   227,   196,
     253,   254,   134,   182,   243,    94,    95,   139,   233,   259,
      96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    65,   137,   203,    84,   123,   192,   136,    17,   138,
     194,   193,   195,    28,   197,   251,   198,    63,   264,   235,
      23,   245,   113,    17,    67,   228,   252,   283,   284,   246,
     -19,     6,     7,     1,   287,   261,   251,   231,     4,    20,
     166,   167,     5,   262,   111,    13,   199,   252,    14,    15,
     305,   306,   112,    84,   249,   164,   165,    85,    18,   251,
     114,   279,   280,   229,   206,   207,   238,    19,   303,    24,
     252,   310,   308,    20,    14,   185,   282,    47,   168,   169,
     251,    29,    27,   250,   152,   153,    31,    32,    33,   260,
     181,    30,    44,   266,    34,    35,    45,    36,    66,   192,
      56,    57,    58,   194,   193,   195,    85,   197,   230,   198,
      52,    53,    54,    55,    51,   232,    64,    97,   161,   258,
     170,   171,   172,   173,   140,   111,   162,   304,   186,   200,
      59,    60,    61,    62,   163,   201,   135,   237,   202,   242,
    -163,   223,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   157,   158,   159,   160,   112,   236,   234,
     267,   155,  -164,   241,   265,   244,   247,   281,   185,    68,
      69,    70,    71,   255,   286,   174,   175,   176,   285,   299,
     300,   239,   302,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   248,     7,   309,    79,    26,    80,
     183,   184,    81,   307,    46,   177,   178,   179,   180,   216,
     217,   218,   219,   220,   221,   222,   234,    16,     7,   240,
      79,   186,    80,   154,   301,    81,    82,   204,    83,   205,
      48,    49,    50,    64,   208,   209,   210,   211,     0,   212,
     213,   214,   215,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    72,    73,    74,    75,    76,    77,    78,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
       0,   109,   110,     0,     0,     0,     0,     0,   279,   280,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,   109,   110,     0,     0,   115,   116,   117,     0,
      20,     0,   135,     0,   118,   119,     0,   120,   115,   116,
     117,     0,     0,     0,   121,     0,   118,   119,     0,   120,
     115,   156,   117,     0,     0,     0,   121,     0,   118,   119,
       0,   120,     0,     0,     0,     0,     0,     0,   121
};

static const yytype_int16 yycheck[] =
{
       7,    45,    94,   161,    64,    92,   135,    94,    15,    94,
     135,   135,   135,    20,   135,   243,   135,    44,   250,   203,
       3,   235,    17,    30,    51,    17,   243,   264,   264,   235,
      44,    15,    16,    14,   266,   249,   264,   195,    49,    53,
      26,    27,     0,   249,    44,    17,   138,   264,    49,    50,
     287,   287,    52,   113,   238,    24,    25,    64,    17,   287,
      55,    52,    53,    55,   164,   165,   224,    49,   282,    52,
     287,   308,   304,    53,    49,   135,   260,    33,    64,    65,
     308,    51,    50,   241,   111,   112,    48,    49,    50,   247,
     134,    17,    52,   251,    56,    57,    51,    59,    51,   228,
      30,    31,    32,   228,   228,   228,   113,   228,   195,   228,
      56,    57,    58,    59,    53,   200,    54,    50,    17,   244,
      56,    57,    58,    59,    49,    44,    29,   285,   135,    17,
      60,    61,    62,    63,    28,    51,    54,   224,    51,   231,
      19,    19,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   118,   119,   120,   121,    52,    18,   203,
     252,   117,    19,    17,   251,    17,    17,   259,   228,    52,
      53,    54,    55,    49,   266,    30,    31,    32,    17,    49,
      49,   225,    19,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   238,    16,    49,    18,    18,    20,
      21,    22,    23,    53,    30,    60,    61,    62,    63,   174,
     175,   176,   177,   178,   179,   180,   260,     7,    16,   228,
      18,   228,    20,   113,   280,    23,    47,   162,    49,   163,
      34,    35,    36,    54,   166,   167,   168,   169,    -1,   170,
     171,   172,   173,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    49,    56,    57,    58,    59,    60,    61,    62,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    53,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    -1,    -1,    48,    49,    50,    -1,
      53,    -1,    54,    -1,    56,    57,    -1,    59,    48,    49,
      50,    -1,    -1,    -1,    66,    -1,    56,    57,    -1,    59,
      48,    49,    50,    -1,    -1,    -1,    66,    -1,    56,    57,
      -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    68,    69,    49,     0,    15,    16,    70,    71,
      72,    73,    74,    17,    49,    50,    76,    77,    17,    49,
      53,    75,    76,     3,    52,    80,    70,    50,    77,    51,
      17,    48,    49,    50,    56,    57,    59,    78,    90,    91,
      92,    93,    94,    95,    52,    51,    75,    90,    93,    93,
      93,    53,    56,    57,    58,    59,    30,    31,    32,    60,
      61,    62,    63,    78,    54,    83,    51,    78,    92,    92,
      92,    92,    93,    93,    93,    93,    93,    93,    93,    18,
      20,    23,    47,    49,    74,    77,    79,    81,    82,    89,
     107,   109,   110,   113,   122,   123,   127,    50,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    45,
      46,    44,    52,    17,    55,    48,    49,    50,    56,    57,
      59,    66,    77,    79,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   119,    54,    79,    86,    96,   124,
      49,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    78,    78,    82,    90,    49,   103,   103,   103,
     103,    17,    29,    28,    24,    25,    26,    27,    64,    65,
      56,    57,    58,    59,    30,    31,    32,    60,    61,    62,
      63,    83,   120,    21,    22,    74,    77,    83,    84,    85,
      87,    88,    89,   107,   109,   110,   116,   123,   127,    86,
      17,    51,    51,   119,    98,    99,   100,   100,   101,   101,
     101,   101,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   103,   103,    19,   111,   112,   114,   115,    17,    55,
      79,   119,    96,   125,    83,   120,    18,    79,   119,    83,
      85,    17,    86,   121,    17,   114,   115,    17,    83,   120,
     119,   111,   112,   117,   118,    49,   106,   108,   109,   126,
     119,   114,   115,    86,   121,    79,   119,    86,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    52,
      53,    86,   120,   117,   118,    17,    86,   121,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    49,
      49,   106,    19,   114,   119,   117,   118,    53,   121,    49,
     117
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    70,    70,    70,    71,    71,    72,
      73,    74,    74,    75,    75,    75,    76,    76,    76,    77,
      77,    78,    78,    79,    80,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    84,    84,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      86,    87,    88,    89,    90,    91,    91,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    94,    95,    95,    95,    96,    97,    97,    98,
      98,    99,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   104,   105,   105,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   109,   110,
     111,   112,   113,   113,   113,   113,   113,   114,   114,   114,
     114,   115,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   118,   119,   120,   121,   122,   123,   123,   123,   124,
     124,   125,   125,   126,   126,   126,   127
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     3,     1,     1,     1,
       5,     2,     4,     1,     2,     3,     2,     4,     3,     1,
       3,     1,     3,     3,     1,     1,     3,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     3,     1,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     2,     2,     2,     1,     1,     1,
       3,     3,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       2,     1,     3,     4,     4,     6,     6,     3,     4,     4,
       6,     2,     3,     4,     4,     6,     6,     3,     4,     4,
       6,     2,     1,     1,     1,     1,     2,     3,     7,     0,
       1,     0,     1,     0,     1,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9:
#line 208 "grammar.y"
           { scopes.push_back({}); printf("Entered scope\n"); }
#line 1757 "grammar.tab.c"
    break;

  case 10:
#line 211 "grammar.y"
                                    {
        scopes.pop_back(); printf("Left scope\n");
    }
#line 1765 "grammar.tab.c"
    break;

  case 16:
#line 226 "grammar.y"
                           {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - (yyvsp[-1].val); i <= last_variable_id; ++i) {
            write_num_operation(i, 0);
        }
    }
#line 1776 "grammar.tab.c"
    break;

  case 17:
#line 232 "grammar.y"
                                               {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - (yyvsp[-3].val); i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
#line 1788 "grammar.tab.c"
    break;

  case 18:
#line 239 "grammar.y"
                                          {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - (yyvsp[-2].val); i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
#line 1800 "grammar.tab.c"
    break;

  case 19:
#line 249 "grammar.y"
           {
        create_variable((yyvsp[0].str));
        
        (yyval.val) = 0;
    }
#line 1810 "grammar.tab.c"
    break;

  case 20:
#line 254 "grammar.y"
                               {
        create_variable((yyvsp[-2].str));

        (yyval.val) = (yyvsp[0].val) + 1;
    }
#line 1820 "grammar.tab.c"
    break;

  case 23:
#line 266 "grammar.y"
                                             {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - (yyvsp[-2].val); i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
#line 1832 "grammar.tab.c"
    break;

  case 51:
#line 330 "grammar.y"
               {
        jmp_operation(for_label_ids.back() + 1);
    }
#line 1840 "grammar.tab.c"
    break;

  case 52:
#line 336 "grammar.y"
            {
        jmp_operation(for_label_ids.back() + 1);
    }
#line 1848 "grammar.tab.c"
    break;

  case 53:
#line 342 "grammar.y"
             {
        halt_operation();
    }
#line 1856 "grammar.tab.c"
    break;

  case 56:
#line 352 "grammar.y"
                                            {
        sum_operation();
    }
#line 1864 "grammar.tab.c"
    break;

  case 57:
#line 355 "grammar.y"
                                            {
        sub_operation();
    }
#line 1872 "grammar.tab.c"
    break;

  case 58:
#line 358 "grammar.y"
                                            {
        or_operation();
    }
#line 1880 "grammar.tab.c"
    break;

  case 59:
#line 361 "grammar.y"
                                            {
        xor_operation();
    }
#line 1888 "grammar.tab.c"
    break;

  case 61:
#line 367 "grammar.y"
                                         {
        mul_operation();
    }
#line 1896 "grammar.tab.c"
    break;

  case 62:
#line 370 "grammar.y"
                                         {
        div_operation();
    }
#line 1904 "grammar.tab.c"
    break;

  case 63:
#line 373 "grammar.y"
                                         {
        mod_operation();
    }
#line 1912 "grammar.tab.c"
    break;

  case 64:
#line 376 "grammar.y"
                                            {
        lshift_operation();
    }
#line 1920 "grammar.tab.c"
    break;

  case 65:
#line 379 "grammar.y"
                                            {
        rshift_operation();
    }
#line 1928 "grammar.tab.c"
    break;

  case 66:
#line 382 "grammar.y"
                                         {
        and_operation();
    }
#line 1936 "grammar.tab.c"
    break;

  case 67:
#line 385 "grammar.y"
                                            {
        and_not_operation();
    }
#line 1944 "grammar.tab.c"
    break;

  case 70:
#line 392 "grammar.y"
                     {
        pop_operation();
        push_num_operation(0);
        push_reg_operation();
        sub_operation();
    }
#line 1955 "grammar.tab.c"
    break;

  case 71:
#line 398 "grammar.y"
                     {
        push_num_operation(0xFFFFFFFF);
        xor_operation();
    }
#line 1964 "grammar.tab.c"
    break;

  case 73:
#line 408 "grammar.y"
           {
        int variable_addr = variable_lookup((yyvsp[0].str));
        load_operation(variable_addr);
        push_reg_operation();
    }
#line 1974 "grammar.tab.c"
    break;

  case 74:
#line 413 "grammar.y"
             {
        push_num_operation((yyvsp[0].val));
    }
#line 1982 "grammar.tab.c"
    break;

  case 78:
#line 424 "grammar.y"
                                                       {
        logical_or_operation();
    }
#line 1990 "grammar.tab.c"
    break;

  case 80:
#line 430 "grammar.y"
                                                        {
        logical_and_operation();
    }
#line 1998 "grammar.tab.c"
    break;

  case 82:
#line 436 "grammar.y"
                                                       {
        equal_operation();
    }
#line 2006 "grammar.tab.c"
    break;

  case 83:
#line 439 "grammar.y"
                                                       {
        not_equal_operation();
    }
#line 2014 "grammar.tab.c"
    break;

  case 85:
#line 445 "grammar.y"
                                                        {
        lower_operation();
    }
#line 2022 "grammar.tab.c"
    break;

  case 86:
#line 448 "grammar.y"
                                                        {
        greater_operation();
    }
#line 2030 "grammar.tab.c"
    break;

  case 87:
#line 451 "grammar.y"
                                                       {
        lower_or_equal_operation();
    }
#line 2038 "grammar.tab.c"
    break;

  case 88:
#line 454 "grammar.y"
                                                       {
        greater_or_equal_operation();
    }
#line 2046 "grammar.tab.c"
    break;

  case 90:
#line 460 "grammar.y"
                                                            {
        sum_operation();
    }
#line 2054 "grammar.tab.c"
    break;

  case 91:
#line 463 "grammar.y"
                                                            {
        sub_operation();
    }
#line 2062 "grammar.tab.c"
    break;

  case 92:
#line 466 "grammar.y"
                                                            {
        or_operation();
    }
#line 2070 "grammar.tab.c"
    break;

  case 93:
#line 469 "grammar.y"
                                                            {
        xor_operation();
    }
#line 2078 "grammar.tab.c"
    break;

  case 95:
#line 475 "grammar.y"
                                                         {
        mul_operation();
    }
#line 2086 "grammar.tab.c"
    break;

  case 96:
#line 478 "grammar.y"
                                                         {
        div_operation();
    }
#line 2094 "grammar.tab.c"
    break;

  case 97:
#line 481 "grammar.y"
                                                         {
        mod_operation();
    }
#line 2102 "grammar.tab.c"
    break;

  case 98:
#line 484 "grammar.y"
                                                            {
        lshift_operation();
    }
#line 2110 "grammar.tab.c"
    break;

  case 99:
#line 487 "grammar.y"
                                                            {
        rshift_operation();
    }
#line 2118 "grammar.tab.c"
    break;

  case 100:
#line 490 "grammar.y"
                                                         {
        and_operation();
    }
#line 2126 "grammar.tab.c"
    break;

  case 101:
#line 493 "grammar.y"
                                                            {
        and_not_operation();
    }
#line 2134 "grammar.tab.c"
    break;

  case 103:
#line 500 "grammar.y"
                             {
        pop_operation();
        push_reg_operation();
        push_reg_operation();
        xor_operation();
    }
#line 2145 "grammar.tab.c"
    break;

  case 105:
#line 507 "grammar.y"
                             {
        pop_operation();
        push_num_operation(0);
        push_reg_operation();
        sub_operation();
    }
#line 2156 "grammar.tab.c"
    break;

  case 106:
#line 513 "grammar.y"
                             {
        push_num_operation(0xFFFFFFFF);
        xor_operation();
    }
#line 2165 "grammar.tab.c"
    break;

  case 108:
#line 524 "grammar.y"
           {
        int variable_addr = variable_lookup((yyvsp[0].str));
        load_operation(variable_addr);
        push_reg_operation();
    }
#line 2175 "grammar.tab.c"
    break;

  case 109:
#line 529 "grammar.y"
             {
        push_num_operation((yyvsp[0].val));
    }
#line 2183 "grammar.tab.c"
    break;

  case 111:
#line 536 "grammar.y"
                    {
        printf("%s = %s\n", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 2191 "grammar.tab.c"
    break;

  case 112:
#line 539 "grammar.y"
                                            {
        printf("%s = %s\n", (yyvsp[-4].str), (yyvsp[0].str));
    }
#line 2199 "grammar.tab.c"
    break;

  case 113:
#line 545 "grammar.y"
                                          {
        int last_variable_id = find_last_taken_id();
        for (int i = last_variable_id - (yyvsp[-2].val); i <= last_variable_id; ++i) {
            pop_operation();
            write_reg_operation(i);
        }
    }
#line 2211 "grammar.tab.c"
    break;

  case 137:
#line 581 "grammar.y"
                { 
        int variable_addr = variable_lookup((yyvsp[-1].str));

        load_operation(variable_addr);
        push_reg_operation();
        push_num_operation(1);
        sum_operation();
        write_reg_operation(variable_addr);
    }
#line 2225 "grammar.tab.c"
    break;

  case 138:
#line 590 "grammar.y"
                {
        int variable_addr = variable_lookup((yyvsp[-1].str));

        load_operation(variable_addr);
        push_reg_operation();
        push_num_operation(1);
        sum_operation();
        pop_operation();
        write_reg_operation(variable_addr);
    }
#line 2240 "grammar.tab.c"
    break;

  case 139:
#line 603 "grammar.y"
         {
        scopes.push_back({});
        printf("Entered scope\n");

        if_label_ids.push_back({last_label + 1});

        last_label += 1;
    }
#line 2253 "grammar.tab.c"
    break;

  case 140:
#line 613 "grammar.y"
              {
        scopes.push_back({});
        printf("Entered scope\n");

        int new_id = if_label_ids.back().back() + 1;
        label_operation(new_id);
        if_label_ids.back().push_back(new_id);

        last_label += 1;
    }
#line 2268 "grammar.tab.c"
    break;

  case 141:
#line 625 "grammar.y"
           {
        scopes.push_back({});
        printf("Entered scope\n");

        int new_id = if_label_ids.back().back() + 1;
        label_operation(new_id);
        if_label_ids.back().push_back(new_id);

        last_label += 1;
    }
#line 2283 "grammar.tab.c"
    break;

  case 142:
#line 637 "grammar.y"
                                   {
        scopes.pop_back();
        printf("Left if scope\n");

        label_operation(if_label_ids.back().front());

        if_label_ids.pop_back();
    }
#line 2296 "grammar.tab.c"
    break;

  case 147:
#line 651 "grammar.y"
                                        {
        scopes.pop_back();
        printf("Left else if scope\n");

        last_label -= 1;

        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
#line 2310 "grammar.tab.c"
    break;

  case 151:
#line 665 "grammar.y"
                       {
        scopes.pop_back();
        printf("Left if scope\n");

        label_operation(if_label_ids.back().front());
        
        if_label_ids.pop_back();
    }
#line 2323 "grammar.tab.c"
    break;

  case 152:
#line 676 "grammar.y"
                                        {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation(if_label_ids.back().front());
        
        if_label_ids.pop_back();
    }
#line 2336 "grammar.tab.c"
    break;

  case 157:
#line 690 "grammar.y"
                                             {
        scopes.pop_back();
        printf("Left scope\n");

        last_label -= 1;

        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
#line 2350 "grammar.tab.c"
    break;

  case 161:
#line 704 "grammar.y"
                            {
        scopes.pop_back();
        printf("Left scope\n");

        label_operation(if_label_ids.back().front());
        if_label_ids.pop_back();
    }
#line 2362 "grammar.tab.c"
    break;

  case 162:
#line 713 "grammar.y"
                         {
        push_num_operation(0);
        cmp_operation();
        jmp_equal_operation(if_label_ids.back().back() + 1);
    }
#line 2372 "grammar.tab.c"
    break;

  case 163:
#line 720 "grammar.y"
            {
        scopes.pop_back();
        printf("Left if scope\n");

        jmp_operation(if_label_ids.back().front());
    }
#line 2383 "grammar.tab.c"
    break;

  case 164:
#line 728 "grammar.y"
                 {
        scopes.pop_back();
        printf("Left if scope\n");

        jmp_operation(if_label_ids.back().front());
    }
#line 2394 "grammar.tab.c"
    break;

  case 165:
#line 737 "grammar.y"
          {
        scopes.push_back({});
        printf("Entered scope\n");

        for_label_ids.push_back(last_label + 1);
        last_label += 2;

        (yyval.val) = last_label + 1;
    }
#line 2408 "grammar.tab.c"
    break;

  case 166:
#line 748 "grammar.y"
                           {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation((yyvsp[-1].val));
        label_operation((yyvsp[-1].val) + 1);

        for_label_ids.pop_back();
    }
#line 2422 "grammar.tab.c"
    break;

  case 167:
#line 757 "grammar.y"
                                              {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation((yyvsp[-2].val));
        label_operation((yyvsp[-2].val) + 1);

        for_label_ids.pop_back();
    }
#line 2436 "grammar.tab.c"
    break;

  case 168:
#line 766 "grammar.y"
                                                                                    {
        scopes.pop_back();
        printf("Left scope\n");

        jmp_operation((yyvsp[-6].val));
        label_operation((yyvsp[-6].val) + 1);

        for_label_ids.pop_back();
    }
#line 2450 "grammar.tab.c"
    break;

  case 169:
#line 777 "grammar.y"
             {
        label_operation(for_label_ids.back());
    }
#line 2458 "grammar.tab.c"
    break;

  case 170:
#line 780 "grammar.y"
                     {
        label_operation(for_label_ids.back());
    }
#line 2466 "grammar.tab.c"
    break;

  case 172:
#line 786 "grammar.y"
                         {
        push_num_operation(0);
        cmp_operation();
        jmp_equal_operation(for_label_ids.back() + 1);
    }
#line 2476 "grammar.tab.c"
    break;

  case 176:
#line 799 "grammar.y"
                         {
        int variable_addr = variable_lookup((yyvsp[-1].str));

        load_operation(variable_addr);
        print_operation();
    }
#line 2487 "grammar.tab.c"
    break;


#line 2491 "grammar.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 807 "grammar.y"


int variable_lookup(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->variables.find(name);
        if (found != it->variables.end()) {
            return found->second;
        }
    }
    
    parsing_failure();

    return -1;
}

int find_last_taken_id() {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->last_id != -1) return it->last_id;
    }

    return 0;
}

int create_variable(const std::string& name) {
    int new_id = find_last_taken_id() + 1;
    scopes.back().variables[name] = new_id;
    scopes.back().last_id = new_id;

    printf("New variable (%s) with id (%d) created\n", name.c_str(), new_id);

    return new_id;
}

void yyerror(const char* s) {
    fprintf(stderr, "Ошибка: %s\n", s);
}

void parsing_failure() {
    printf("Parsing failed in runtime\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: can't open file '%s'\n", argv[1]);
        return 1;
    }
    yyin = input_file;

    FILE* output_file = fopen(argv[2], "w");
    if (!input_file) {
        fprintf(stderr, "Error: cant't open file '%s'\n", argv[2]);
        return 1;
    }
    yyout = output_file;

    if (yyparse() == 0) {
        printf("Parsing completed successfully!\n");
    } else {
        printf("Parsing failed.\n");
    }

    fclose(input_file);
    return 0;
}
