/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "sintatica.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <stdio.h>
#include "escopo.h"
#include "loopStack.h"

#define YYSTYPE atributos

using namespace std;


string gambiarra_print = "";
string gambiarra_read = "";

//Variaveis Globais
bool appendLogFile = true; //falso apaga a porra toda do arquivo, DEIXE TRUE
int curVar = 0;
int curLabel = 0;
int i = 0;
struct atributos
{
	string label;
	string traducao;
	int tipo;
	int tamanho;
};

typedef struct atributos atributos;

//std::map<string, variavel> varTable;
map_stack* pilha = createMapStack();
LoopStack* pilhaLoops = createLoopStack();



//VarTable escopoGlobal;
// pushEscopo(pilha, escopoGlobal);

Declaracoes declaracoes;



// Functions
variavel getVarOnStack(string label);
string getVarType(int);
int checkType(int, int);
atributos castFunction(int, string, int, string, int, string);
void createLog (string name, string toWrite, bool);
int getTokenType(string);
int checkTypeArith(int, int);
atributos castArith(atributos, atributos, string);
atributos castFunctionArith(int, string, int, string, int, string);
string declararVariaveis();
string getLabel(int);
atributos concatString (atributos,atributos);
int getNumber(string str);

void createVarTableLog(VarTable);

int yylex(void);
void yyerror(string);


string getVarName(){
	return "temp" + to_string(++curVar);
}




#line 141 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TK_NUM = 258,
    TK_REAL = 259,
    TK_CHAR = 260,
    TK_BOOL = 261,
    TK_STRING = 262,
    TK_GLOBAL = 263,
    TK_MAIN = 264,
    TK_ID = 265,
    TK_TIPO_INT = 266,
    TK_TIPO_FLOAT = 267,
    TK_TIPO_CHAR = 268,
    TK_TIPO_BOOL = 269,
    TK_TIPO_STRING = 270,
    TK_FIM = 271,
    TK_ERROR = 272,
    TK_EQUAL = 273,
    TK_GTE = 274,
    TK_LTE = 275,
    TK_NEQUAL = 276,
    TK_MAIOR = 277,
    TK_MENOR = 278,
    TK_AND = 279,
    TK_OR = 280,
    TK_NOT = 281,
    TK_IF = 282,
    TK_WHILE = 283,
    TK_DO = 284,
    TK_FOR = 285,
    TK_ELSE = 286,
    TK_BREAK = 287,
    TK_BREAK_ALL = 288,
    TK_BREAK_FUNC = 289,
    TK_CONTINUE = 290,
    TK_PRINT = 291,
    TK_READ = 292,
    TK_PP = 293,
    TK_MM = 294
  };
#endif
/* Tokens.  */
#define TK_NUM 258
#define TK_REAL 259
#define TK_CHAR 260
#define TK_BOOL 261
#define TK_STRING 262
#define TK_GLOBAL 263
#define TK_MAIN 264
#define TK_ID 265
#define TK_TIPO_INT 266
#define TK_TIPO_FLOAT 267
#define TK_TIPO_CHAR 268
#define TK_TIPO_BOOL 269
#define TK_TIPO_STRING 270
#define TK_FIM 271
#define TK_ERROR 272
#define TK_EQUAL 273
#define TK_GTE 274
#define TK_LTE 275
#define TK_NEQUAL 276
#define TK_MAIOR 277
#define TK_MENOR 278
#define TK_AND 279
#define TK_OR 280
#define TK_NOT 281
#define TK_IF 282
#define TK_WHILE 283
#define TK_DO 284
#define TK_FOR 285
#define TK_ELSE 286
#define TK_BREAK 287
#define TK_BREAK_ALL 288
#define TK_BREAK_FUNC 289
#define TK_CONTINUE 290
#define TK_PRINT 291
#define TK_READ 292
#define TK_PP 293
#define TK_MM 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 270 "y.tab.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   312

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  173

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      45,    40,    43,    41,    53,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
      47,    49,    48,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,   104,   115,   123,   131,   140,   148,   153,
     154,   177,   209,   215,   220,   225,   230,   234,   245,   256,
     273,   283,   287,   291,   299,   342,   383,   425,   470,   496,
     520,   546,   572,   591,   636,   642,   646,   652,   688,   716,
     749,   782,   817,   838,   848,   859,   865,   870,   880,   886,
     892,   897,   905,   913,   918,   923,   928,   934,   941,   950,
     957,  1023,  1039,  1154,  1158,  1168,  1179,  1183,  1187,  1199,
    1207,  1214,  1221,  1228,  1235,  1242,  1250,  1258,  1265,  1276,
    1286,  1297,  1308,  1327,  1349
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM", "TK_REAL", "TK_CHAR",
  "TK_BOOL", "TK_STRING", "TK_GLOBAL", "TK_MAIN", "TK_ID", "TK_TIPO_INT",
  "TK_TIPO_FLOAT", "TK_TIPO_CHAR", "TK_TIPO_BOOL", "TK_TIPO_STRING",
  "TK_FIM", "TK_ERROR", "TK_EQUAL", "TK_GTE", "TK_LTE", "TK_NEQUAL",
  "TK_MAIOR", "TK_MENOR", "TK_AND", "TK_OR", "TK_NOT", "TK_IF", "TK_WHILE",
  "TK_DO", "TK_FOR", "TK_ELSE", "TK_BREAK", "TK_BREAK_ALL",
  "TK_BREAK_FUNC", "TK_CONTINUE", "TK_PRINT", "TK_READ", "TK_PP", "TK_MM",
  "')'", "'+'", "'-'", "'*'", "'/'", "'('", "'^'", "'<'", "'>'", "'='",
  "'{'", "'}'", "';'", "','", "$accept", "S", "T", "BLOCO", "PUSH_SCOPE",
  "POP_SCOPE", "COMANDOS", "COMANDO", "OPERADOR_COMPOSTO",
  "OPERADOR_UNARIO", "GLOBAL", "LOOP", "WHILE", "DO", "FOR", "PUSH_LOOP",
  "POP_LOOP", "PRINT", "TK_PRINT_ARGS", "TK_PRINT_ARG", "READ",
  "TK_READ_ARGS", "TK_READ_ARG", "DECLARATION", "TYPE", "VARLIST", "ATRIB",
  "E", YY_NULLPTR
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
      41,    43,    45,    42,    47,    40,    94,    60,    62,    61,
     123,   125,    59,    44
};
# endif

#define YYPACT_NINF -121

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-121)))

#define YYTABLE_NINF -9

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -121,     2,    -7,  -121,    -4,  -121,   -37,  -121,   -31,  -121,
    -121,   -35,    13,  -121,  -121,  -121,  -121,  -121,   249,    18,
    -121,  -121,  -121,  -121,  -121,    95,   -14,   -19,   -18,   -17,
     -15,    95,    95,    28,    32,    95,    95,    -8,    13,     1,
      11,    14,   -16,    16,    30,    35,    34,    36,   106,  -121,
      44,  -121,  -121,    42,    45,    47,    55,    95,    96,  -121,
     264,    95,  -121,  -121,  -121,  -121,    12,  -121,   233,    57,
    -121,   233,  -121,  -121,    98,   154,  -121,  -121,  -121,  -121,
    -121,    67,  -121,    68,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,    65,    62,  -121,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,  -121,    71,    95,    95,
      95,    95,   233,   185,    95,    95,  -121,  -121,    95,   110,
     121,  -121,    95,   129,   264,   264,   264,   264,   233,   233,
      98,    98,   264,   264,   264,   264,    95,   233,   233,   233,
     233,  -121,  -121,  -121,   194,    99,    91,   233,   102,  -121,
     233,   124,  -121,    95,    95,  -121,  -121,   225,   141,  -121,
     100,    -9,  -121,    18,   116,   117,   123,  -121,  -121,  -121,
    -121,  -121,  -121
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     1,     0,     6,     0,     2,     0,     5,
       3,     0,    42,    79,    78,    81,    80,    82,     0,    83,
      53,    54,    55,    56,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    84,
       0,    28,    30,     0,     0,     0,     0,     0,     0,    83,
      77,     0,    17,    18,    19,    20,    44,    46,    47,    48,
      50,    51,    29,    31,    64,     0,     6,     7,    23,    22,
      21,     0,     5,     0,    43,    34,    35,    36,    15,    16,
      13,    61,    52,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    32,     0,     0,
       0,     0,    62,     0,     0,     0,    63,     4,     0,     0,
       0,    12,     0,     0,    73,    71,    72,    74,    75,    76,
      65,    66,    67,    68,    70,    69,     0,    24,    25,    26,
      27,     5,    45,    49,     0,     0,     0,    60,    58,    59,
      33,    10,     5,     0,     0,     5,    37,     0,     0,    11,
       0,     0,    38,     0,     0,     0,     0,     5,     5,     5,
      41,    40,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,  -121,   -60,   164,    92,   131,  -121,     6,     9,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,    63,
    -121,  -121,    56,    60,   158,  -121,  -120,   -25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     5,    10,    11,     7,    37,    38,    39,    40,
      41,    84,    85,    86,    87,    42,   121,    43,    66,    67,
      44,    69,    70,    45,    46,    92,    47,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,   163,     3,   149,     4,     6,    68,    71,     8,     9,
      74,    75,    81,    82,    83,    12,    13,    14,    15,    16,
      17,    18,   119,    19,    20,    21,    22,    23,    24,    33,
      34,    61,   112,    62,    63,    64,   113,    65,    72,    25,
      26,   166,    73,    76,    91,    27,    28,    29,    30,    31,
      32,    33,    34,    78,   107,    35,    51,    52,    36,    53,
      54,    55,    56,    79,    -8,   114,    80,    57,    88,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   151,    89,   137,   138,   139,   140,    90,    93,    68,
      71,   108,   156,   144,   109,   159,   110,   147,    13,    14,
      15,    16,    17,    58,   111,    59,    49,   170,   171,   172,
     115,   150,   118,   120,   122,   123,    94,    95,    96,    97,
     136,    25,    98,    99,    94,    95,    96,    97,   157,   158,
      98,    99,    20,    21,    22,    23,    24,    35,   145,   148,
      36,   102,   103,   154,   153,   104,   105,   100,   101,   102,
     103,    57,   162,   104,   105,   155,   167,   168,   106,    94,
      95,    96,    97,   169,     2,    98,    99,   164,   117,    77,
     165,   143,    94,    95,    96,    97,    50,   142,    98,    99,
     146,     0,   100,   101,   102,   103,     0,     0,   104,   105,
       0,     0,     0,   161,   116,   100,   101,   102,   103,     0,
       0,   104,   105,    94,    95,    96,    97,     0,     0,    98,
      99,     0,    94,    95,    96,    97,     0,     0,    98,    99,
       0,     0,     0,     0,     0,   141,   100,   101,   102,   103,
       0,     0,   104,   105,   152,   100,   101,   102,   103,     0,
       0,   104,   105,    94,    95,    96,    97,     0,     0,    98,
      99,    94,    95,    96,    97,     0,     0,    98,    99,    49,
      20,    21,    22,    23,    24,   160,   100,   101,   102,   103,
       0,     0,   104,   105,   100,   101,   102,   103,     0,     0,
     104,   105,    94,    95,    96,    97,     0,     0,    98,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105
};

static const yytype_int16 yycheck[] =
{
      25,    10,     0,   123,    11,     9,    31,    32,    45,    40,
      35,    36,    28,    29,    30,    50,     3,     4,     5,     6,
       7,     8,    82,    10,    11,    12,    13,    14,    15,    38,
      39,    45,    57,    52,    52,    52,    61,    52,    10,    26,
      27,   161,    10,    51,    10,    32,    33,    34,    35,    36,
      37,    38,    39,    52,    10,    42,    38,    39,    45,    41,
      42,    43,    44,    52,    51,    53,    52,    49,    52,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   141,    52,   108,   109,   110,   111,    52,    52,   114,
     115,    49,   152,   118,    49,   155,    49,   122,     3,     4,
       5,     6,     7,     8,    49,    10,    10,   167,   168,   169,
      53,   136,    45,    45,    49,    53,    18,    19,    20,    21,
      49,    26,    24,    25,    18,    19,    20,    21,   153,   154,
      24,    25,    11,    12,    13,    14,    15,    42,    28,    10,
      45,    43,    44,    52,    45,    47,    48,    41,    42,    43,
      44,    49,    52,    47,    48,    31,    40,    40,    52,    18,
      19,    20,    21,    40,     0,    24,    25,   161,    76,    38,
     161,   115,    18,    19,    20,    21,    18,   114,    24,    25,
     120,    -1,    41,    42,    43,    44,    -1,    -1,    47,    48,
      -1,    -1,    -1,    52,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    18,    19,    20,    21,    -1,    -1,    24,
      25,    -1,    18,    19,    20,    21,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    18,    19,    20,    21,    -1,    -1,    24,
      25,    18,    19,    20,    21,    -1,    -1,    24,    25,    10,
      11,    12,    13,    14,    15,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    41,    42,    43,    44,    -1,    -1,
      47,    48,    18,    19,    20,    21,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    58,     0,    11,    56,     9,    59,    45,    40,
      57,    58,    50,     3,     4,     5,     6,     7,     8,    10,
      11,    12,    13,    14,    15,    26,    27,    32,    33,    34,
      35,    36,    37,    38,    39,    42,    45,    60,    61,    62,
      63,    64,    69,    71,    74,    77,    78,    80,    81,    10,
      78,    38,    39,    41,    42,    43,    44,    49,     8,    10,
      81,    45,    52,    52,    52,    52,    72,    73,    81,    75,
      76,    81,    10,    10,    81,    81,    51,    60,    52,    52,
      52,    28,    29,    30,    65,    66,    67,    68,    52,    52,
      52,    10,    79,    52,    18,    19,    20,    21,    24,    25,
      41,    42,    43,    44,    47,    48,    52,    10,    49,    49,
      49,    49,    81,    81,    53,    53,    40,    59,    45,    57,
      45,    70,    49,    53,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    49,    81,    81,    81,
      81,    40,    73,    76,    81,    28,    77,    81,    10,    80,
      81,    57,    40,    45,    52,    31,    57,    81,    81,    57,
      40,    52,    52,    10,    62,    63,    80,    40,    40,    40,
      57,    57,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    58,    59,    60,    60,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    62,    62,    63,    63,
      63,    63,    64,    64,    65,    65,    65,    66,    67,    68,
      68,    68,    69,    70,    71,    72,    72,    73,    74,    75,
      75,    76,    77,    78,    78,    78,    78,    78,    79,    79,
      79,    79,    80,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     5,     5,     0,     0,     2,     0,     2,
       5,     7,     3,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     4,     4,     4,     2,     2,
       2,     2,     3,     5,     1,     1,     1,     5,     7,     9,
       9,     9,     0,     0,     2,     3,     1,     1,     2,     3,
       1,     1,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     1,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     2
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 98 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
			}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 105 "sintatica.y" /* yacc.c:1646  */
    { 
				cout <<"\n\n/*Compilador Bolado*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n"  << declararVariaveis() << "\nint main(void)\n{\n" << (yyvsp[0]).traducao << "\treturn 0;\n}" << endl;
				
				ofstream outputFile;
				outputFile.open("src.c");
				outputFile <<"\n\n/*Compilador Bolado*/\n" << "#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n"  << declararVariaveis() << "\nint main(void)\n{\n" << (yyvsp[0]).traducao << "\treturn 0;\n}" << endl;
				outputFile.close();
			}
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 116 "sintatica.y" /* yacc.c:1646  */
    {
				
				(yyval).traducao = (yyvsp[-2]).traducao;
				
			}
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 123 "sintatica.y" /* yacc.c:1646  */
    {
				VarTable escopo;
				pushEscopo(pilha,escopo);
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 131 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "escopoAtual " << pilha->escopoAtual << endl;
				createVarTableLog(pilha->escopos[pilha->escopoAtual]);
				pop(pilha);
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				
				//cout << "Traducao Comandos" << endl << $2.traducao << endl;
			}
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 148 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 155 "sintatica.y" /* yacc.c:1646  */
    {
				// VarTable varTableEscopo;
				// pushEscopo(escopos, varTableEscopo);

			    int teste = checkType((yyvsp[-2]).tipo, (yyvsp[-2]).tipo);

			    if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
			        puts("Invalid Type for the IF Statment");
			        exit(0);
			    }
				string varName = getVarName();
				string gotoLabel = getLabel(TK_IF);
				string linha = "\t" + varName + " = !" + (yyvsp[-2]).label + ";\n";
				string showLabel = "\t"+gotoLabel + ":\n\n";

				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);//[varName] = v;
				declaracoes.push_back(v);

				string stmt = "\n\tif(" + varName + ") " + "goto " + gotoLabel +";\n" + (yyvsp[0]).traducao + "\n" + showLabel;
			    (yyval).traducao = (yyvsp[-2]).traducao + linha + stmt;
			}
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 178 "sintatica.y" /* yacc.c:1646  */
    {
				// VarTable varTableEscopo;
				// pushEscopo(escopos, varTableEscopo);

			    int teste = checkType((yyvsp[-4]).tipo, (yyvsp[-4]).tipo);

			    if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
			        puts("Invalid Type for the IF Statment");
			        exit(0);
			    }
				string varName = getVarName();
				//END_IF
				string gotoLabel = getLabel(TK_IF);
				
				//INICIO_ELSE
				
				string inicio_else = "inicio_else_" + to_string(curLabel);
				
				
				string linha = "\t" + varName + " = !" + (yyvsp[-4]).label + ";\n";
				//string showLabel = gotoLabel + ":\n\n";

				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);//[varName] = v;
				declaracoes.push_back(v);

				string stmt = "\n\tif(" + varName + ") " + "goto " + inicio_else +";\n" + (yyvsp[-2]).traducao + "\n\tgoto " + gotoLabel + ";\n\t" + inicio_else + ":\n" + (yyvsp[0]).traducao + "\n\t" + gotoLabel + ":\n";
				
				
			    (yyval).traducao = (yyvsp[-4]).traducao + linha + stmt;
			}
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 210 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao;
				
				//cout << "Traducao do Push_Loop_Pop " << "\n" << $2.traducao << endl;
			}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 216 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
				i++;
			}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 221 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
				i++;
			}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 226 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
				gambiarra_print = "";
			}
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 231 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);	
			}
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 234 "sintatica.y" /* yacc.c:1646  */
    {
			 	
			 	if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopAtual = getLoop(pilhaLoops);
			 		(yyval).traducao = "\tgoto " + loopAtual.endLabel+";//break comum\n";
			 	}
			 	
			 }
#line 1690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 245 "sintatica.y" /* yacc.c:1646  */
    {
			 	
			 	if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopMaisExterno = pilhaLoops->loops[0];
			 		(yyval).traducao = "\tgoto " + loopMaisExterno.endLabel+";//break all\n";
			 	}
			 	
			 }
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 256 "sintatica.y" /* yacc.c:1646  */
    {
			 	
			 	cout << "Break func " << (yyvsp[-1]).label << " parametro " << getNumber((yyvsp[-1]).label) << endl;
			 	(yyval).traducao = (yyvsp[-1]).traducao;
			 
			 	int parametro_break = getNumber((yyvsp[-1]).label);
			 	if(pilhaLoops->loops.size() < parametro_break ){
			 		cout << "Erro de compilação. 'break' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loop = pilhaLoops->loops[ pilhaLoops->loops.size() - parametro_break ];
			 		(yyval).traducao = "\tgoto " + loop.endLabel+";//break_func\n";
			 		
			 		//std::cout << "DANDO GO TO PARA " << loop.beginLabel << std::endl;
			 	}
			 	
			}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 273 "sintatica.y" /* yacc.c:1646  */
    {
				
				 if(pilhaLoops->loops.empty()){
			 		cout << "Erro de compilação. 'continue' deveria estar dentro de um laço de repetição ";
			 		exit(0);
			 	}else{
			 		Loop loopAtual = getLoop(pilhaLoops);
			 		(yyval).traducao = "\tgoto " + loopAtual.continueLabel + ";//continue comum\n";
			 	}			
			}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 284 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);	
			}
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 288 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
			}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 292 "sintatica.y" /* yacc.c:1646  */
    {
				
				(yyval) = (yyvsp[-1]);
			}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 300 "sintatica.y" /* yacc.c:1646  */
    {
						variavel var = getVarOnStack((yyvsp[-3]).label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador += não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType((yyvsp[0]).tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + (yyvsp[0]).label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack((yyvsp[-3]).label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType((yyvsp[0]).tipo) == "char*"){
								cout << "Este Operador += não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " + " + (yyvsp[0]).label +";\n";
								(yyval).traducao = (yyvsp[0]).traducao+ "\n" + linha;
							}
								
							
						}
			
					
					}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 343 "sintatica.y" /* yacc.c:1646  */
    {
						variavel var = getVarOnStack((yyvsp[-3]).label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador -= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType((yyvsp[0]).tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + (yyvsp[0]).label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack((yyvsp[-3]).label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType((yyvsp[0]).tipo) == "char*"){
								cout << "Este Operador -= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + (yyvsp[0]).label +";\n";
								(yyval).traducao = (yyvsp[0]).traducao+ "\n" + linha;
							}
								
							
						}
					}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 384 "sintatica.y" /* yacc.c:1646  */
    {
						variavel var = getVarOnStack((yyvsp[-3]).label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador *= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType((yyvsp[0]).tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + (yyvsp[0]).label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack((yyvsp[-3]).label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType((yyvsp[0]).tipo) == "char*"){
								cout << "Este Operador *= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " * " + (yyvsp[0]).label +";\n";
								(yyval).traducao = (yyvsp[0]).traducao+ "\n" + linha;
							}
								
						
						}
				
					}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 426 "sintatica.y" /* yacc.c:1646  */
    {
						variavel var = getVarOnStack((yyvsp[-3]).label);
						if(var.tipo != getVarType(TK_TIPO_INT) && var.tipo != getVarType(TK_TIPO_FLOAT)){
							cout << "operador /= não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//caminho feliz
						//string linha = $1.label + " = " + $1.label + " + " + $3.label; 

						
						// Cast na atribuição com Temp "Store"
						if( var.tipo != getVarType((yyvsp[0]).tipo) ) {
							// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
							
							//string varName;
							string store = getVarName();
							string linha =  store + " = (" +var.tipo+") " + (yyvsp[0]).label + ";\n";
							string linha2 = "\t"  + var.nome_temp + " = " + store + ";\n";
							
							(yyval).traducao = (yyvsp[-3]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;
		
							variavel v = createVar(store, getVarOnStack((yyvsp[-3]).label).tipo,store);
		
							addVar2Escopo(pilha, v);
							declaracoes.push_back(v);
					
						}	// Tipo Inferido ou cast não necessário
						else{
							if (getVarType((yyvsp[0]).tipo) == "char*"){
								cout << "Este Operador /= não é destinado a Strings" << endl;
							}
							else{
								string linha = "\t" + var.nome_temp + " = " + var.nome_temp + " / " + (yyvsp[0]).label +";\n";
								(yyval).traducao = (yyvsp[0]).traducao+ "\n" + linha;
							}
								
						
						}
				
					}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 471 "sintatica.y" /* yacc.c:1646  */
    {
						
						variavel var = getVarOnStack((yyvsp[-1]).label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						string varName = getVarName();
						variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
						
						string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = "+ varName +" + " + var.nome_temp + ";\n";
						
						(yyval).traducao = linha + linha2;

	
					}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 497 "sintatica.y" /* yacc.c:1646  */
    {
						
						variavel var = getVarOnStack((yyvsp[-1]).label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//string varName = getVarName();
					//	variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, var);
						declaracoes.push_back(var);
						
						//string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " + "+ "1" + ";\n";
						
						(yyval).traducao = linha2;
					}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 521 "sintatica.y" /* yacc.c:1646  */
    {
						
						variavel var = getVarOnStack((yyvsp[-1]).label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador -- não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						string varName = getVarName();
						variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
						
						string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + varName + ";\n";
						
						(yyval).traducao = linha + linha2;

	
					}
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 547 "sintatica.y" /* yacc.c:1646  */
    {
						
						variavel var = getVarOnStack((yyvsp[-1]).label);
						if(var.tipo != getVarType(TK_TIPO_INT)){
							cout << "operador ++ não é permitido para o tipo " << var.tipo << endl;
							exit(0);
						}
						
						//string varName = getVarName();
					//	variavel v = createVar(varName, var.tipo, varName);
						
						//a = 4;
						// print(a++); printa 4
						// print(++a) printa 5
						
						addVar2Escopo(pilha, var);
						declaracoes.push_back(var);
						
						//string linha = "\t" + varName + " =  1;\n";
						string linha2 = "\t" + var.nome_temp + " = " + var.nome_temp + " - " + "1" + ";\n";
						
						(yyval).traducao = linha2;
					}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 572 "sintatica.y" /* yacc.c:1646  */
    {
			

				//se variavel NAO existe no escopo global
				if ( pilha->escopos[0][(yyvsp[0]).label].nome_var == ""  ){
					
					string varName = getVarName();
					variavel v = createVar((yyvsp[0]).label, getVarType((yyvsp[-1]).tipo), varName);
					
					addVar2Global(pilha, v);
					declaracoes.push_back(v);

				}else{
					cout << "Variavel " << (yyvsp[0]).label << " ja foi declarada no escopo global" <<endl;
					exit(0);
				}
	
			}
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 591 "sintatica.y" /* yacc.c:1646  */
    {
			
				//std::map<string,variavel>::iterator it;
			
				//busca no escopo global se variavel ja existe
				//it = pilha->escopos[0].find($3.label);
				
				//se variavel nao existe no escopo global
				if ( pilha->escopos[0][(yyvsp[-2]).label].nome_var == ""  ){
					
					string varName = getVarName();
					variavel v = createVar((yyvsp[-2]).label, getVarType((yyvsp[-3]).tipo), varName);
					
					addVar2Global(pilha, v);
					declaracoes.push_back(v);
					
									// Cast na atribuição com Temp "Store"
					if( v.tipo != getVarType((yyvsp[0]).tipo) ) {
						// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
						string store = getVarName();
						string linha =  store + " = (" +v.tipo+") " + (yyvsp[0]).label + ";\n";
						string linha2 = "\t"  + varName + " = " + store + ";\n";
						
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;
	
						variavel v = createVar(store, getVarOnStack((yyvsp[-2]).label).tipo,store);
	
						addVar2Escopo(pilha, v);
						declaracoes.push_back(v);
				
					}	// Tipo Inferido ou cast não necessário
					else{
						if (getVarType((yyvsp[0]).tipo) == "char*"){
							(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\tstrcpy(" + varName  + ", " + (yyvsp[0]).label +");\n";
						}
						else
							(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + varName  + " = " + (yyvsp[0]).label +";\n";
						
					}
				
				}	
				//daqui
			}
#line 2139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 637 "sintatica.y" /* yacc.c:1646  */
    { 
				(yyval) = (yyvsp[0]);
			//	cout<< "traducao de while" << $1.traducao << endl;
				
			}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 643 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[0]);
			}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 647 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[0]);
			}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 653 "sintatica.y" /* yacc.c:1646  */
    {
				int teste = checkType((yyvsp[-2]).tipo, (yyvsp[-2]).tipo);
	
				if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
					puts("Invalid Type for the WHILE Statment");
					exit(0);
				}
				string varName = getVarName();
				
				Loop loop = getLoop(pilhaLoops);
				
				//string beginLabel = "inicio" + getLabel(TK_WHILE);
				string beginLabel = loop.beginLabel;
				//curLabel--; //Gambiarra para ficar inicio_while_1 e fim_while_1
	
				// string endLabel = "fim" + getLabel(TK_WHILE);
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
	
				string linha = "\t" + varName + " = !" + (yyvsp[-2]).label + ";\n";
				string showLabel = "\tgoto "+ beginLabel + ";\n\n";
	
				variavel v = createVar(varName, getVarType(teste), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
				
				// parte que atualiza o indice do loop == $3.traducao + linha
				// o continueLabel esta para ser usado por um comando continue, caso nao haja um
				// ele é apenas um label vazio
				string stmt =  "\t" + beginLabel +":"+ "\tif(" + varName + ") " + "goto " + endLabel +";\n" + (yyvsp[0]).traducao + "\n" + "\t" + 
				continueLabel + "://continueLabel\n" + (yyvsp[-2]).traducao + linha + showLabel + "\t"  + endLabel + ":\n\n";
			    (yyval).traducao = (yyvsp[-2]).traducao + linha + stmt;
				
			}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 689 "sintatica.y" /* yacc.c:1646  */
    {
				int teste = checkType((yyvsp[-2]).tipo, (yyvsp[-2]).tipo);
	
				if (teste != TK_TIPO_BOOL && teste != TK_TIPO_INT){
					puts("Invalid Type for the DO...WHILE Statment");
					exit(0);
				}
				
				//string varName = getVarName();
				
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
	
				string linha = "\tif(" + (yyvsp[-2]).label + ")";
				string showLabel = "\tgoto "+ beginLabel;
				
				//label do_while bloco
				string stmt  = "\t" + beginLabel + ":\n" + (yyvsp[-5]).traducao + "\n\t" + continueLabel + ":\n";
				stmt		+= (yyvsp[-2]).traducao + linha + showLabel + ";\n\t" + endLabel + ":\n"; 
				
				(yyval).traducao = stmt;
			}
#line 2234 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 717 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "ENCONTREI UM FOR " << getVarType((yyvsp[-4]).tipo) <<" : " << (yyvsp[-4]).tipo <<endl;
				
				if( (yyvsp[-4]).tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType((yyvsp[-4]).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + (yyvsp[-4]).label + ";\n";
				
				string atrib_inicial = (yyvsp[-6]).traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + (yyvsp[-4]).traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = (yyvsp[0]).traducao + "\n\t" + continueLabel + ": \n" + (yyvsp[-2]).traducao + (yyvsp[-4]).traducao + linha + "\n";
				
				(yyval).traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
#line 2270 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 750 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "ENCONTREI UM FOR " << getVarType((yyvsp[-4]).tipo) <<" : " << (yyvsp[-4]).tipo <<endl;
				
				if( (yyvsp[-4]).tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType((yyvsp[-4]).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + (yyvsp[-4]).label + ";\n";
				
				string atrib_inicial = (yyvsp[-6]).traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + (yyvsp[-4]).traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = (yyvsp[0]).traducao + "\n\t" + continueLabel + ": \n" + (yyvsp[-2]).traducao + (yyvsp[-4]).traducao + linha + "\n";
				
				(yyval).traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 783 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "ENCONTREI UM FOR " << getVarType((yyvsp[-4]).tipo) <<" : " << (yyvsp[-4]).tipo <<endl;
				
				if( (yyvsp[-4]).tipo != TK_TIPO_BOOL ){
					cout <<  "ERRO DE COMPILACAO: for espera uma expressao boleana no segundo parametro" <<endl;
					exit(0);
				}
				
				string varName = getVarName();
				
				variavel v = createVar(varName, getVarType((yyvsp[-4]).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
					
					
				Loop loop = getLoop(pilhaLoops);
				
				string beginLabel = loop.beginLabel;
				string endLabel = loop.endLabel;
				string continueLabel = loop.continueLabel;
				
				string linha = "\t" + varName + " = !" + (yyvsp[-4]).label + ";\n";
				
				string atrib_inicial = (yyvsp[-6]).traducao;
				string showLabel = "\n\t" + beginLabel + ": \n" + (yyvsp[-4]).traducao + linha + "\n";
				string verifica = "\tif(" + varName + ") " + "\tgoto "+ endLabel + ";\n";
				
				string dentroFor = (yyvsp[0]).traducao + "\n\t" + continueLabel + ": \n" + (yyvsp[-2]).traducao + (yyvsp[-4]).traducao + linha + "\n";
				
				(yyval).traducao = atrib_inicial + showLabel + verifica + dentroFor + "\tgoto " + beginLabel + ";\n\t" + endLabel + ":\n";
			}
#line 2342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 817 "sintatica.y" /* yacc.c:1646  */
    {
				string label = getLabel(TK_WHILE);
				
				//cout << "Pushando o Loop While" << endl;
				//string label = "loop_1";
				string beginLabel = "inicio" + label;
				string endLabel = "fim" + label;
				string continueLabel = "continue" + label;
				
				Loop loop;
				loop.endLabel = endLabel;
				loop.beginLabel = beginLabel;
				loop.continueLabel = continueLabel;
				
				
				pushLoop(loop, pilhaLoops);
				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 2367 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 838 "sintatica.y" /* yacc.c:1646  */
    {
				popLoop(pilhaLoops);
				
				cout << "Popando o Loop While" << endl;

				
				(yyval).traducao = "";
				(yyval).label = "";
			}
#line 2381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 849 "sintatica.y" /* yacc.c:1646  */
    {
				    //variavel v = getVarOnStack($2.label);
				    
					(yyval).traducao = gambiarra_print + "\tstd::cout "  + (yyvsp[0]).traducao + " << std::endl;\n";
					
				//	cout << "traducao de print args = " <<  $2.traducao<<endl;
				//	cout  << "traducao de print = " <<  $$.traducao<<endl;
				}
#line 2394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 860 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
					
					//cout << "derivacao print args" << $$.traducao << endl;
				}
#line 2404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 866 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[0]).traducao; 
				}
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 871 "sintatica.y" /* yacc.c:1646  */
    {
					gambiarra_print = (yyvsp[0]).traducao;
					(yyval).traducao = " << " + (yyvsp[0]).label;
				//	cout << "traducao de print arg = " <<  $$.traducao <<endl;
				//	cout << "gambiarra_print  = " <<  $1.traducao <<endl;
					
				}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 881 "sintatica.y" /* yacc.c:1646  */
    {

					(yyval).traducao = gambiarra_print + "\tstd::cin"  + (yyvsp[0]).traducao + ";\n";

				}
#line 2434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 887 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
					
					//cout << "derivacao print args" << $$.traducao << endl;
				}
#line 2444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 893 "sintatica.y" /* yacc.c:1646  */
    {
					(yyval).traducao = (yyvsp[0]).traducao; 
				}
#line 2452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 898 "sintatica.y" /* yacc.c:1646  */
    {
					gambiarra_read = (yyvsp[0]).traducao;
					(yyval).traducao = " >> " + (yyvsp[0]).label;
				//	cout << "traducao de print arg = " <<  $$.traducao <<endl;
				//	cout << "gambiarra_print  = " <<  $1.traducao <<endl;
					
				}
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 906 "sintatica.y" /* yacc.c:1646  */
    {
				(yyvsp[0]).tipo = (yyvsp[-1]).tipo;
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
				// $$.tipo = ;
			}
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 914 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_INT;
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 919 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_FLOAT;
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 924 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_CHAR;
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 929 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 935 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_STRING;
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 942 "sintatica.y" /* yacc.c:1646  */
    {
				string varName = getVarName();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;// +"\t" + getVarType($0.tipo) + " "+ varName + "; \n";
				createLog("Name", getVarType((yyvsp[-3]).tipo) + " " + (yyvsp[0]).label + " - " + varName, appendLogFile);
				variavel v = createVar((yyvsp[0]).label, getVarType((yyvsp[-3]).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 951 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				(yyvsp[-2]).tipo = (yyvsp[-3]).tipo;
				(yyvsp[0]).tipo = (yyvsp[-3]).tipo;
				// cout << "Em " <<$1.label <<" Tipo do VARLIST em Var, Atrib: " << getVarType($0.tipo) << "\nEm "<< $3.label<< " Tipo da Atrib em Var, Atrib: " << getVarType($3.tipo) << endl;
			}
#line 2543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 958 "sintatica.y" /* yacc.c:1646  */
    {
				variavel var = getVarOnStack((yyvsp[-2]).label); //Buscar só no escopo atual
				string varName = "";
				(yyvsp[-2]).tamanho = (yyvsp[0]).tamanho;

				string infere_tipo = "", store = "";
				//variavel v;

				//std::cout << "TK_ID = E" << endl;

				//variavel n existe na tabela
				if(varName == ""){
					varName = getVarName();
					// cout << "ENTREI NO IF " <<getVarType($0.tipo) << endl;

					if(getVarType((yyvsp[-3]).tipo) != ""){
					//	cout << "$0 tipo nao vazio" << endl;
						infere_tipo = getVarType((yyvsp[-3]).tipo);
						
					}
					else{
					//	cout << "$0 tipo vazio" << endl;
						infere_tipo = getVarType((yyvsp[0]).tipo);
						
					}

					var = createVar((yyvsp[-2]).label, infere_tipo, varName);

					// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
					// std::cout << "(VAR3) Tipo " << getVarType($3.tipo) << " com i = "<< i<< std::endl;

					addVar2Escopo(pilha, var);
					declaracoes.push_back(var);

					
				}
				
				// Cast na atribuição com Temp "Store"
				if( (getVarOnStack((yyvsp[-2]).label).tipo != getVarType((yyvsp[0]).tipo) ) ){
					// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
					store = getVarName();
					string linha =  store + " = (" +getVarOnStack((yyvsp[-2]).label).tipo+") " + (yyvsp[0]).label + ";\n";
					string linha2 = "\t"  + varName + " = " + store + ";\n";
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;

					variavel v = createVar(store, getVarOnStack((yyvsp[-2]).label).tipo,store);

					addVar2Escopo(pilha, v);
					declaracoes.push_back(v);
				}
				// Tipo Inferido ou cast não necessário
				else{
					if (getVarType((yyvsp[0]).tipo) == "char*"){
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\tstrcpy(" + varName  + ", " + (yyvsp[0]).label +");\n";
					}
					else
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + varName  + " = " + (yyvsp[0]).label +";\n";
					
					
				}
				
				i++;
				createLog("Name", getVarType((yyvsp[0]).tipo) + " "+ (yyval).label + " - " + varName, appendLogFile);
			
			}
#line 2613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1024 "sintatica.y" /* yacc.c:1646  */
    {
				// COLOCAR no HASH
				string varName = getVarName();
				(yyval).label = (yyvsp[0]).label;
				//$$.tamanho = 20;
				(yyval).traducao = (yyvsp[0]).traducao;// + "\t" + getVarType($0.tipo)+ " "+ varName + "; \n";
				createLog("Name", getVarType((yyvsp[-1]).tipo) + " "+ (yyval).label + " - " + varName, appendLogFile);
				variavel v = createVar((yyval).label, getVarType((yyvsp[-1]).tipo), varName);
				v.tamanho = 20;
				// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
				addVar2Escopo(pilha, v);;
				declaracoes.push_back(v);
			}
#line 2631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1040 "sintatica.y" /* yacc.c:1646  */
    {
				variavel var = getVarOnStack((yyvsp[-2]).label); //Buscar só no escopo atual
				string varName = var.nome_temp;
				
				cout << (yyvsp[0]).label <<" tam da E em atrib "<< (yyvsp[0]).tamanho << endl;

				string infere_tipo = "", store = "";
				
				//usado para quando precisa dar free e outro malloc para alteracao de string
				string trad = "";
				//variavel v;

				//std::cout << "TK_ID = E" << endl;

				//variavel n existe na tabela
				if(varName == ""){
					varName = getVarName();
					// cout << "ENTREI NO IF " <<getVarType($0.tipo) << endl;

					if(getVarType((yyvsp[-3]).tipo) != ""){
					//	cout << "$0 tipo nao vazio" << endl;
						infere_tipo = getVarType((yyvsp[-3]).tipo);
						
					}
					else{
					//	cout << "$0 tipo vazio" << endl;
						infere_tipo = getVarType((yyvsp[0]).tipo);
						
					}

					var = createVar((yyval).label, infere_tipo, varName);
					
					
					//se for string verificar o tamanho dela para realizar a copia 
					// que acontece no if de baixo
					if((yyvsp[0]).tipo == TK_TIPO_STRING){
						variavel str = getVarOnStack((yyvsp[0]).label);
						var.tamanho = str.tamanho;
						
						
						//verifica se $3 foi resultado de concatenaçao da variavel
						if((yyvsp[0]).tamanho > var.tamanho)
							var.tamanho = (yyvsp[0]).tamanho;
					}
				
					// std::cout << "Tipo " << getVarType($0.tipo) << " com i = "<< i<< std::endl;
					// std::cout << "(VAR3) Tipo " << getVarType($3.tipo) << " com i = "<< i<< std::endl;

					addVar2Escopo(pilha, var);
					declaracoes.push_back(var);

					
				}else{
					//se a variavel ja foi declarada
					cout << " VARIAVEL FOI DECLARADA "<< var.tipo << endl;
					if(var.tipo == getVarType(TK_TIPO_STRING)){
						string willy = getVarName();					
						variavel willy_var = createVar(willy, var.tipo, willy);
						
						//variavel temporaria armazena variavel antiga
						trad = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+ willy_var.nome_temp + " = " + varName + ";\n";

						int tam = var.tamanho + (yyvsp[0]).tamanho;
						trad += "\t"+varName + " = (char*) malloc(sizeof(char) * "+ to_string(tam) + ");\n";
						//$$.traducao = $1.traducao + $3.traducao + "\tstrcpy(" + varName  + ", " + $3.label +");\n";
						trad +=  "\tstrcpy(" + varName  + ", " + (yyvsp[0]).label +");\n";
						trad += "\tfree("+ willy + ");\n";
						
						cout << " TRAD EM ATRIB " <<trad << endl;
						
						//atualiza o tamanho da variavel existente e salva na pilha
						var.tamanho = tam;
						addVar2Escopo(pilha ,var );
						declaracoes.push_back(willy_var);
					}
				}
				
				// Cast na atribuição com Temp "Store"
				if( (getVarOnStack((yyvsp[-2]).label).tipo != getVarType((yyvsp[0]).tipo) ) ){
					// std::cout << "Convert Tipo da " << $1.label << "    Tipo: " << varTable[$1.label].tipo  << std::endl;
					store = getVarName();
					string linha =  store + " = (" +getVarOnStack((yyvsp[-2]).label).tipo+") " + (yyvsp[0]).label + ";\n";
					string linha2 = "\t"  + varName + " = " + store + ";\n";
					(yyval).traducao = trad + (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"  + linha + linha2;

					variavel v = createVar(store, getVarOnStack((yyvsp[-2]).label).tipo,store);

					addVar2Escopo(pilha, v);
					declaracoes.push_back(v);
				}
				// Tipo Inferido ou cast não necessário
				else{
					
					if (getVarType((yyvsp[0]).tipo) == "char*"){
						(yyval).tamanho = (yyvsp[0]).tamanho - 2;
						
						if(trad == "")
							(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\tstrcpy(" + varName  + ", " + (yyvsp[0]).label +");\n";
						else
							(yyval).traducao = trad;
						
					}
					else
						(yyval).traducao = trad +  (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t" + varName  + " = " + (yyvsp[0]).label +";\n";
	
					
				}
				
				i++;
				createLog("Name", getVarType((yyvsp[0]).tipo) + " "+ (yyval).label + " - " + varName, appendLogFile);
			
			}
#line 2748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1154 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval) = (yyvsp[-1]);
			}
#line 2757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1158 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = (yyvsp[0]).tipo;
				string varName = getVarName();
				(yyval).label = '-' + (yyvsp[0]).label;
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + varName +" = " + "-" + (yyvsp[0]).label +";\n";
				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);

			}
#line 2772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1169 "sintatica.y" /* yacc.c:1646  */
    {
				if ((yyvsp[-2]).tipo == TK_TIPO_STRING || (yyvsp[0]).tipo == TK_TIPO_STRING){
					//cout << "No E+E, concat " << $1.traducao << endl;
				//	cout << $1.tamanho << $3.tamanho << endl;
					(yyval) = concatString((yyvsp[-2]), (yyvsp[0]));
				}
				else{
					(yyval) = castArith((yyvsp[-2]), (yyvsp[0]), "+");
				}
			}
#line 2787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1180 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = castArith((yyvsp[-2]), (yyvsp[0]), "-");
			}
#line 2795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1184 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = castArith((yyvsp[-2]), (yyvsp[0]), "*");
			}
#line 2803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1188 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = castArith((yyvsp[-2]), (yyvsp[0]), "/");
			}
#line 2811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1200 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, ">");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;

			}
#line 2823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1208 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, "<");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;
			}
#line 2834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1215 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, ">=");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;
			}
#line 2845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1222 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, "<=");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;
			}
#line 2856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1229 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, "==");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;
			}
#line 2867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1236 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				atributos atr = castFunction((yyvsp[-2]).tipo, (yyvsp[-2]).label, (yyvsp[0]).tipo, (yyvsp[0]).label, (yyval).tipo, "!=");
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + atr.traducao;
				(yyval).label = atr.label;
			}
#line 2878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1243 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				(yyval).tipo = checkType((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string varName = getVarName();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+getVarType((yyval).tipo)+ " " +  varName +" = "+ (yyvsp[-2]).label +" && "+ (yyvsp[0]).label +";\n";
				(yyval).label = varName;
			}
#line 2890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1251 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				(yyval).tipo = checkType((yyvsp[-2]).tipo, (yyvsp[0]).tipo);
				string varName = getVarName();
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + "\t"+getVarType((yyval).tipo)+ " " +  varName +" = "+ (yyvsp[-2]).label +" || "+ (yyvsp[0]).label +";\n";
				(yyval).label = varName;
			}
#line 2902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1259 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = checkType((yyvsp[0]).tipo, (yyvsp[0]).tipo);
				string varName = getVarName();
				(yyval).traducao = (yyvsp[0]).traducao + "\t"+getVarType((yyval).tipo)+ " " +  varName +" = " "! "+ (yyvsp[0]).label +";\n";
				(yyval).label = varName;
			}
#line 2913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1266 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_FLOAT;
				string varName = getVarName();
				(yyval).traducao = "\t" +varName + " = " + (yyvsp[0]).label + ";\n";
				(yyval).label = varName;

				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1277 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_INT;
				string varName = getVarName();
				(yyval).traducao = "\t" +varName + " = " + (yyvsp[0]).label + ";\n";
				(yyval).label = varName;
				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1287 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).tipo = TK_TIPO_BOOL;
				string varName = getVarName();
				// puts("Estou aqui");
				(yyval).traducao = "\t" + varName+ " = " + (yyvsp[0]).label + ";\n";
				(yyval).label = varName;
				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1298 "sintatica.y" /* yacc.c:1646  */
    {
				// puts("Estou aqui");
				(yyval).tipo = TK_TIPO_CHAR;
				string varName = getVarName();
				(yyval).traducao = "\t" + varName + " = " + (yyvsp[0]).label + ";\n";
				(yyval).label = varName;
				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1309 "sintatica.y" /* yacc.c:1646  */
    {
				// puts("ACHEI UMA STRING");
				(yyval).tipo = TK_TIPO_STRING;
				string varName = getVarName();
				// $$.traducao = "\t" + varName + " = " + $1.label + ";\n";
				(yyval).traducao = "\tstrcpy(" + varName + "," + (yyvsp[0]).label + ");\n";
				(yyval).label = varName;
				
				variavel v = createVar(varName, getVarType((yyval).tipo), varName);
				// nao conta o abre e fecha aspas
				v.tamanho = (yyvsp[0]).label.size() - 2;
				
				cout << "Imprimindo Label: " << (yyvsp[0]).label <<endl;
				cout<< " tamanho da string " << v.tamanho << endl;
				
				addVar2Escopo(pilha, v);
				declaracoes.push_back(v);
			}
#line 2995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1328 "sintatica.y" /* yacc.c:1646  */
    {
				variavel v = getVarOnStack((yyvsp[0]).label);
				string id = v.nome_temp;

				if (id == ""){
					cout << "Erro de Compilação Variavel '" << (yyvsp[0]).label << "' inexistente" <<endl;
					exit(0);
				}
				else{

					(yyval).traducao = (yyvsp[0]).traducao;
					(yyval).label = id;
					(yyval).tipo = getTokenType(v.tipo);
					(yyval).tamanho = v.tamanho;
					
					cout << " achei uma variavel "<< v.nome_var << " " << v.nome_temp << " " << v.tamanho << endl;
				//	cout << "REGRA TK_ID: " <<$$.label << $$.tipo <<": "+v.tipo << endl;
				}
			}
#line 3019 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1350 "sintatica.y" /* yacc.c:1646  */
    {
				variavel v = pilha->escopos[0][(yyvsp[0]).label];
				string id = v.nome_temp;

				if (id == ""){
					cout << "Erro de Compilação Variavel '" << (yyvsp[-1]).label << "' inexistente no escopo global" <<endl;
					exit(0);
				}
				else{

					(yyval).traducao = (yyvsp[-1]).traducao;
					(yyval).label = id;
					(yyval).tipo = getTokenType(v.tipo);
					(yyval).tamanho = v.tamanho;
					
					cout << " achei uma variavel "<< v.nome_var << " " << v.nome_temp << " " << v.tamanho << endl;
				//	cout << "REGRA TK_ID: " <<$$.label << $$.tipo <<": "+v.tipo << endl;
				}
			}
#line 3043 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3047 "y.tab.c" /* yacc.c:1646  */
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 1371 "sintatica.y" /* yacc.c:1906  */


#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] ){

	// pushEscopo(pilha, escopoGlobal);

	//criar datamap em arquivo
	yyparse();
	

	return 0;
}

string declararVariaveis(){
	return getDeclaracoes(declaracoes);
}

void yyerror( string MSG ){
	cout << MSG << endl;
	exit (0);
}

int getTokenType(string type){
	if(type == "int")
		return TK_TIPO_INT;
	if(type ==  "float")
		return TK_TIPO_FLOAT;
	if(type == "char")
		return TK_TIPO_CHAR;
	if(type == "bool")
		return TK_TIPO_INT;
	if(type == "char*")
		return TK_TIPO_STRING;

}

string getVarType(int type){
	if(type == TK_TIPO_INT)
		return "int";
	if(type == TK_TIPO_FLOAT )
		return "float";
	if(type == TK_TIPO_CHAR)
		return "char";
	if(type == TK_TIPO_BOOL)
		return "int";
	if(type == TK_TIPO_STRING)
		return "char*";
	
	return "";	
}

int checkType (int t1, int t3){

	//cout << "Tipo1 " << getVarType(t1) << "Tipo3 " << getVarType(t3) << endl;
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {

		if (t1 == TK_TIPO_BOOL && t3 == TK_TIPO_BOOL)
			return TK_TIPO_BOOL;

		else if (t1 == TK_TIPO_CHAR && t3 == TK_TIPO_CHAR)
			return TK_TIPO_CHAR;

		puts("Invalid Type for the Operation");
		exit(0);
	}
	else if (t1 == TK_TIPO_FLOAT || t3 == TK_TIPO_FLOAT){

		return TK_TIPO_FLOAT;

	}
	else{

		return TK_TIPO_INT;
	}
}

atributos castFunction(int t1, string t1_label, int t3, string t3_label, int t0, string sinal){
	int teste = checkType(t1, t3);
	string linha = "", linha2 = "";

	string varName = getVarName();
	atributos retorno;

	if (teste == TK_TIPO_FLOAT){

		string store = getVarName();
		retorno.label = store;

		variavel v = createVar(varName, getVarType(teste), varName);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
		v = createVar(store, getVarType(teste), store);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);

		if(t1 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t1_label +";\n";
			linha2 = "\t" + store +" = "+ varName + " " + sinal + " " +t3_label +";\n";
		}
		else if (t3 == TK_TIPO_INT){
			linha = "\tfloat " + varName + " = (float) " + t3_label +";\n";
			linha2 = "\t" + store +" = "+ t1_label + " " + sinal + " " + varName +";\n";
		}
	}
	else if (teste == TK_TIPO_INT){
		retorno.label = varName;
		linha2 = "\t" + varName +" = "+ t1_label + " " + sinal + " " + t3_label +";\n";
		variavel v = createVar(varName, getVarType(teste), varName);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
	}

	retorno.traducao = linha + linha2;
	retorno.tipo = t0;
	return retorno;

}

atributos castFunctionArith(int t1, string t1_label, int t3, string t3_label, int t0, string sinal){
	int teste = checkType(t1, t3);
	string linha = "", linha2 = "";

	string varName = getVarName();
	string store = getVarName();
	if (teste == TK_TIPO_FLOAT){

		variavel v = createVar(varName, getVarType(teste), varName);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
		v = createVar(store, getVarType(teste), store);
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);

		if(t1 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t1_label +";\n";
			linha2 = "\t" + store +" = "+ varName + " " + sinal + " " +t3_label +";\n";
		}
		else if (t3 == TK_TIPO_INT){
			linha = "\t" + varName + " = (float) " + t3_label +";\n";
			linha2 = "\t" + store +" = "+ t1_label + " " + sinal + " " + varName +";\n";
		}
	}
	atributos retorno;
	retorno.traducao = linha + linha2;
	retorno.label = store;
	retorno.tipo = t0;
	return retorno;

}

int checkTypeArith(int t1, int t3){
	if ( (t1 != TK_TIPO_INT && t1 != TK_TIPO_FLOAT) || (t3 != TK_TIPO_INT && t3 != TK_TIPO_FLOAT) ) {
		puts("Invalid Types for Arithmetics Operators!");

		cout << "TIPOS DE T1 E T3 " << t1 << " " << t3 << endl;
		exit(0);

	}
	if(t1 == TK_TIPO_FLOAT || t3 == TK_TIPO_FLOAT)
		return TK_TIPO_FLOAT;

	else
		return TK_TIPO_INT;
}

void createLog (string name, string toWrite, bool append){

	FILE *p_arquivo;
	//char *nome = "arquivo.txt";
	string parameter = "w";

	if(append)
		parameter = "a";

	if((p_arquivo = fopen(name.c_str(), parameter.c_str()) ) == NULL)
	{
		printf("\n\nNao foi possivel abrir o arquivo.\n");
		return;
	}


	fprintf(p_arquivo,"%s\n", toWrite.c_str());

	fclose(p_arquivo);

}

void createVarTableLog (VarTable escopo){

	string linhas;
	// for (int i = 0; i < pilha->escopos.size(); i++){
	// 	VarTable varTable = pilha->escopos[i];
	linhas += "Escopo " + to_string(pilha->escopoAtual) + "\n";

	// 	// linhas += "\n";
	for (std::map<string,variavel>::iterator it=escopo.begin(); it!=escopo.end(); ++it){
		variavel var = it->second;
		linhas += var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\t" + to_string(var.tamanho) + "\n";
	}
	linhas += "\n";
	// }

	createLog("varTable", linhas, true);
}

variavel getVarOnStack(string label){

	
	//out <<  " GET TEMP ON TABLE: buscando: " << label<< " ESCOPO ATUAL  " << pilha->escopoAtual << endl;

	for (int i = pilha->escopoAtual; i >= 0 ; i--)
	{	
		VarTable varTable = pilha->escopos[i];
	//	cout<< "buscando no Escopo: " << i <<endl;
		for (std::map<string,variavel>::iterator it=varTable.begin(); it!=varTable.end(); ++it){
			variavel var = it->second;
		//	cout << var.tipo + "\t" + var.nome_var + "\t" + var.nome_temp + "\n" << endl;
		}
	}


	VarTable varTable = pilha->escopos[pilha->escopoAtual];
	if ( varTable.count(label) ){
		//variavel ja foi declarada
	//	cout<< "achei " << label << " no escopo atual" << endl;
		return varTable[label];
	}else{
		int escopo = pilha->escopoAtual-1;
		for(int i = escopo; i > -1; i--){
			VarTable varTable = pilha->escopos[i];
			if ( varTable.count(label) ){
				//variavel ja foi declarada
			//	cout<< "achei " << label << " no escopo " << i << endl;
			//	cout << varTable[label].nome_temp << " " << varTable[label].tipo << endl;
				return varTable[label];
			}
		}
	//	cout << "nao achei " << label << endl;

		return createVar("", "","");
	}


	// cout << "Nein Nein Nein variavel "<< label << endl;
	// exit(0);	

}

atributos castArith(atributos s1, atributos s3, string sinal){

	atributos ss;
	ss.tipo = checkTypeArith(s1.tipo, s3.tipo);
	//Sem Cast
	if (s1.tipo == s3.tipo){
		string varName = getVarName();
		ss.traducao = s1.traducao + s3.traducao + "\t" + varName + " = "+ s1.label +" " + sinal + " "+ s3.label +";\n";
		ss.label = varName;

		variavel v = createVar(varName, getVarType(ss.tipo), varName);
		//varTable[varName] = v;
		addVar2Escopo(pilha, v);
		declaracoes.push_back(v);
	}
	//Com cast
	else{
		atributos atr = castFunctionArith(s1.tipo, s1.label, s3.tipo, s3.label, ss.tipo, sinal);
		ss.traducao = s1.traducao + s3.traducao + atr.traducao;
		ss.label = atr.label;
	}
	return ss;

}

string getLabel(int token){

	if (token == TK_IF)
		return "fim_if_" + to_string(++curLabel);
		
//	else if (token == TK_ELSE)
	//	return "else";

	else if (token == TK_WHILE)
		return "_loop_" + to_string(++curLabel);
		
}

atributos concatString (atributos a1 ,atributos a2){
	
	string varName = getVarName();
	variavel var = createVar(varName, getVarType(TK_TIPO_STRING), varName);
	
	variavel v1 = getVarOnStack(a1.label);
	variavel v2 = getVarOnStack(a2.label);
	
	var.tamanho = a1.tamanho + a2.tamanho;
	
	cout << "VarTamanho " << v1.tamanho << " " << v2.tamanho << endl;
	cout << "dados variaveis encontradas" <<endl;
	cout << v1.nome_temp << " " << v1.nome_var << endl;
	cout << v2.nome_temp << " " << v2.nome_var << endl;
	
	declaracoes.push_back(var);
	
	string linha = "\tstrcat("+ varName +", " + a1.label+");\n";
	string linha2 = "\tstrcat("+ varName +", " + a2.label+");\n";
	
	//String concatenada ta no VarName
	atributos atr;
	
	atr.label = varName;
	atr.traducao = linha + linha2;
	atr.tipo = TK_TIPO_STRING;
	atr.tamanho = var.tamanho;
	
	
	//cout << " CONCAT STRING" << endl;
	//cout << a1.label << " " << a1.traducao << a1.tipo << endl;
//	cout << a2.label << " " <<  a2.traducao << a2.tipo << endl;
	
	return atr;
	
}

int getNumber(string str){
	int result = 0;
	
	for (int i = 0; i < str.length(); ++i)	{
		if(str.at(i) >= '0' &&  str.at(i) <= '9'){
			result *= 10;
			result += str.at(i) - '0'; 
		}
	}
	return result;
}

