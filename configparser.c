/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.6.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 10 "configparser.y"

#include "config.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "options.h"
#include "util.h"
#include "dname.h"
#include "tsig.h"
#include "rrl.h"
#include "configyyrename.h"
int c_lex(void);
void c_error(const char *message);

#ifdef __cplusplus
extern "C"
#endif /* __cplusplus */

/* these need to be global, otherwise they cannot be used inside yacc */
extern config_parser_state_t* cfg_parser;

#if 0
#define OUTYY(s) printf s /* used ONLY when debugging */
#else
#define OUTYY(s)
#endif


/* Line 336 of yacc.c  */
#line 101 "configparser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "configparser.h".  */
#ifndef YY_CONFIGPARSER_H
# define YY_CONFIGPARSER_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SPACE = 258,
     LETTER = 259,
     NEWLINE = 260,
     COMMENT = 261,
     COLON = 262,
     ANY = 263,
     ZONESTR = 264,
     STRING = 265,
     VAR_SERVER = 266,
     VAR_NAME = 267,
     VAR_IP_ADDRESS = 268,
     VAR_IP_TRANSPARENT = 269,
     VAR_DEBUG_MODE = 270,
     VAR_IP4_ONLY = 271,
     VAR_IP6_ONLY = 272,
     VAR_DATABASE = 273,
     VAR_IDENTITY = 274,
     VAR_NSID = 275,
     VAR_LOGFILE = 276,
     VAR_SERVER_COUNT = 277,
     VAR_TCP_COUNT = 278,
     VAR_PIDFILE = 279,
     VAR_PORT = 280,
     VAR_STATISTICS = 281,
     VAR_CHROOT = 282,
     VAR_USERNAME = 283,
     VAR_ZONESDIR = 284,
     VAR_XFRDFILE = 285,
     VAR_DIFFFILE = 286,
     VAR_XFRD_RELOAD_TIMEOUT = 287,
     VAR_TCP_QUERY_COUNT = 288,
     VAR_TCP_TIMEOUT = 289,
     VAR_IPV4_EDNS_SIZE = 290,
     VAR_IPV6_EDNS_SIZE = 291,
     VAR_DO_IP4 = 292,
     VAR_DO_IP6 = 293,
     VAR_ZONEFILE = 294,
     VAR_ZONE = 295,
     VAR_ALLOW_NOTIFY = 296,
     VAR_REQUEST_XFR = 297,
     VAR_NOTIFY = 298,
     VAR_PROVIDE_XFR = 299,
     VAR_NOTIFY_RETRY = 300,
     VAR_OUTGOING_INTERFACE = 301,
     VAR_ALLOW_AXFR_FALLBACK = 302,
     VAR_KEY = 303,
     VAR_ALGORITHM = 304,
     VAR_SECRET = 305,
     VAR_AXFR = 306,
     VAR_UDP = 307,
     VAR_VERBOSITY = 308,
     VAR_HIDE_VERSION = 309,
     VAR_PATTERN = 310,
     VAR_INCLUDEPATTERN = 311,
     VAR_ZONELISTFILE = 312,
     VAR_REMOTE_CONTROL = 313,
     VAR_CONTROL_ENABLE = 314,
     VAR_CONTROL_INTERFACE = 315,
     VAR_CONTROL_PORT = 316,
     VAR_SERVER_KEY_FILE = 317,
     VAR_SERVER_CERT_FILE = 318,
     VAR_CONTROL_KEY_FILE = 319,
     VAR_CONTROL_CERT_FILE = 320,
     VAR_XFRDIR = 321,
     VAR_RRL_SIZE = 322,
     VAR_RRL_RATELIMIT = 323,
     VAR_RRL_SLIP = 324,
     VAR_RRL_IPV4_PREFIX_LENGTH = 325,
     VAR_RRL_IPV6_PREFIX_LENGTH = 326,
     VAR_RRL_WHITELIST_RATELIMIT = 327,
     VAR_RRL_WHITELIST = 328,
     VAR_ZONEFILES_CHECK = 329,
     VAR_ZONEFILES_WRITE = 330,
     VAR_LOG_TIME_ASCII = 331,
     VAR_ROUND_ROBIN = 332
   };
#endif
/* Tokens.  */
#define SPACE 258
#define LETTER 259
#define NEWLINE 260
#define COMMENT 261
#define COLON 262
#define ANY 263
#define ZONESTR 264
#define STRING 265
#define VAR_SERVER 266
#define VAR_NAME 267
#define VAR_IP_ADDRESS 268
#define VAR_IP_TRANSPARENT 269
#define VAR_DEBUG_MODE 270
#define VAR_IP4_ONLY 271
#define VAR_IP6_ONLY 272
#define VAR_DATABASE 273
#define VAR_IDENTITY 274
#define VAR_NSID 275
#define VAR_LOGFILE 276
#define VAR_SERVER_COUNT 277
#define VAR_TCP_COUNT 278
#define VAR_PIDFILE 279
#define VAR_PORT 280
#define VAR_STATISTICS 281
#define VAR_CHROOT 282
#define VAR_USERNAME 283
#define VAR_ZONESDIR 284
#define VAR_XFRDFILE 285
#define VAR_DIFFFILE 286
#define VAR_XFRD_RELOAD_TIMEOUT 287
#define VAR_TCP_QUERY_COUNT 288
#define VAR_TCP_TIMEOUT 289
#define VAR_IPV4_EDNS_SIZE 290
#define VAR_IPV6_EDNS_SIZE 291
#define VAR_DO_IP4 292
#define VAR_DO_IP6 293
#define VAR_ZONEFILE 294
#define VAR_ZONE 295
#define VAR_ALLOW_NOTIFY 296
#define VAR_REQUEST_XFR 297
#define VAR_NOTIFY 298
#define VAR_PROVIDE_XFR 299
#define VAR_NOTIFY_RETRY 300
#define VAR_OUTGOING_INTERFACE 301
#define VAR_ALLOW_AXFR_FALLBACK 302
#define VAR_KEY 303
#define VAR_ALGORITHM 304
#define VAR_SECRET 305
#define VAR_AXFR 306
#define VAR_UDP 307
#define VAR_VERBOSITY 308
#define VAR_HIDE_VERSION 309
#define VAR_PATTERN 310
#define VAR_INCLUDEPATTERN 311
#define VAR_ZONELISTFILE 312
#define VAR_REMOTE_CONTROL 313
#define VAR_CONTROL_ENABLE 314
#define VAR_CONTROL_INTERFACE 315
#define VAR_CONTROL_PORT 316
#define VAR_SERVER_KEY_FILE 317
#define VAR_SERVER_CERT_FILE 318
#define VAR_CONTROL_KEY_FILE 319
#define VAR_CONTROL_CERT_FILE 320
#define VAR_XFRDIR 321
#define VAR_RRL_SIZE 322
#define VAR_RRL_RATELIMIT 323
#define VAR_RRL_SLIP 324
#define VAR_RRL_IPV4_PREFIX_LENGTH 325
#define VAR_RRL_IPV6_PREFIX_LENGTH 326
#define VAR_RRL_WHITELIST_RATELIMIT 327
#define VAR_RRL_WHITELIST 328
#define VAR_ZONEFILES_CHECK 329
#define VAR_ZONEFILES_WRITE 330
#define VAR_LOG_TIME_ASCII 331
#define VAR_ROUND_ROBIN 332



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 42 "configparser.y"

	char*	str;


/* Line 350 of yacc.c  */
#line 303 "configparser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_CONFIGPARSER_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 331 "configparser.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNRULES -- Number of states.  */
#define YYNSTATES  226

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   332

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      24,    27,    28,    30,    32,    34,    36,    38,    40,    42,
      44,    46,    48,    50,    52,    54,    56,    58,    60,    62,
      64,    66,    68,    70,    72,    74,    76,    78,    80,    82,
      84,    86,    88,    90,    92,    94,    96,    98,   100,   102,
     104,   106,   108,   111,   114,   117,   120,   123,   126,   129,
     132,   135,   138,   141,   144,   147,   150,   153,   156,   159,
     162,   165,   168,   171,   174,   177,   180,   183,   186,   189,
     192,   195,   198,   201,   204,   207,   210,   213,   216,   219,
     222,   225,   228,   230,   233,   234,   236,   238,   240,   242,
     244,   246,   248,   251,   254,   257,   260,   263,   266,   269,
     271,   274,   276,   278,   280,   282,   284,   286,   288,   290,
     292,   294,   296,   298,   300,   303,   306,   308,   311,   313,
     315,   317,   320,   323,   327,   330,   333,   337,   341,   345,
     348,   352,   355,   358,   361,   363,   366,   368,   370,   372,
     374,   377,   380
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      79,     0,    -1,    -1,    79,    80,    -1,    81,    82,    -1,
     140,   141,    -1,   154,   155,    -1,   134,   135,    -1,   124,
     125,    -1,    11,    -1,    82,    83,    -1,    -1,    84,    -1,
      85,    -1,    86,    -1,    89,    -1,    90,    -1,    93,    -1,
      94,    -1,    95,    -1,    96,    -1,    99,    -1,   100,    -1,
     101,    -1,   102,    -1,   103,    -1,   104,    -1,   105,    -1,
     106,    -1,   109,    -1,   110,    -1,   111,    -1,   112,    -1,
     113,    -1,   114,    -1,   115,    -1,    87,    -1,    88,    -1,
     107,    -1,   108,    -1,   116,    -1,   117,    -1,   118,    -1,
     119,    -1,   120,    -1,   121,    -1,   122,    -1,    91,    -1,
      92,    -1,   123,    -1,    97,    -1,    98,    -1,    13,    10,
      -1,    14,    10,    -1,    15,    10,    -1,    53,    10,    -1,
      54,    10,    -1,    16,    10,    -1,    17,    10,    -1,    37,
      10,    -1,    38,    10,    -1,    18,    10,    -1,    19,    10,
      -1,    20,    10,    -1,    21,    10,    -1,    76,    10,    -1,
      77,    10,    -1,    22,    10,    -1,    23,    10,    -1,    24,
      10,    -1,    25,    10,    -1,    26,    10,    -1,    27,    10,
      -1,    28,    10,    -1,    29,    10,    -1,    57,    10,    -1,
      66,    10,    -1,    31,    10,    -1,    30,    10,    -1,    32,
      10,    -1,    33,    10,    -1,    34,    10,    -1,    35,    10,
      -1,    36,    10,    -1,    67,    10,    -1,    68,    10,    -1,
      69,    10,    -1,    70,    10,    -1,    71,    10,    -1,    72,
      10,    -1,    74,    10,    -1,    75,    10,    -1,    58,    -1,
     125,   126,    -1,    -1,   127,    -1,   129,    -1,   128,    -1,
     130,    -1,   131,    -1,   132,    -1,   133,    -1,    59,    10,
      -1,    61,    10,    -1,    60,    10,    -1,    62,    10,    -1,
      63,    10,    -1,    64,    10,    -1,    65,    10,    -1,    55,
      -1,   135,   136,    -1,   136,    -1,   138,    -1,   137,    -1,
     144,    -1,   145,    -1,   146,    -1,   148,    -1,   149,    -1,
     150,    -1,   151,    -1,   152,    -1,   139,    -1,   153,    -1,
      12,    10,    -1,    56,    10,    -1,    40,    -1,   141,   142,
      -1,   142,    -1,   143,    -1,   137,    -1,    12,    10,    -1,
      39,    10,    -1,    41,    10,    10,    -1,    42,   147,    -1,
      10,    10,    -1,    51,    10,    10,    -1,    52,    10,    10,
      -1,    43,    10,    10,    -1,    45,    10,    -1,    44,    10,
      10,    -1,    46,    10,    -1,    47,    10,    -1,    73,    10,
      -1,    48,    -1,   155,   156,    -1,   156,    -1,   157,    -1,
     158,    -1,   159,    -1,    12,    10,    -1,    49,    10,    -1,
      50,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    73,    74,    74,    75,    75,    76,    79,
      87,    87,    88,    88,    88,    88,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    91,    91,    91,    91,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    95,    95,
      96,    96,    96,    97,    97,    97,    98,    98,    98,    99,
      99,    99,   100,   122,   130,   138,   146,   154,   166,   178,
     186,   194,   203,   209,   233,   239,   250,   261,   269,   277,
     283,   289,   297,   303,   309,   315,   321,   327,   333,   339,
     347,   355,   363,   371,   379,   389,   397,   407,   417,   427,
     435,   443,   452,   457,   458,   459,   459,   459,   460,   460,
     460,   461,   463,   471,   479,   489,   495,   501,   507,   515,
     549,   549,   550,   550,   551,   551,   551,   552,   552,   552,
     553,   553,   553,   554,   555,   567,   578,   615,   615,   616,
     616,   617,   637,   646,   657,   661,   673,   686,   700,   713,
     724,   735,   747,   758,   768,   780,   780,   781,   781,   781,
     782,   796,   807
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SPACE", "LETTER", "NEWLINE", "COMMENT",
  "COLON", "ANY", "ZONESTR", "STRING", "VAR_SERVER", "VAR_NAME",
  "VAR_IP_ADDRESS", "VAR_IP_TRANSPARENT", "VAR_DEBUG_MODE", "VAR_IP4_ONLY",
  "VAR_IP6_ONLY", "VAR_DATABASE", "VAR_IDENTITY", "VAR_NSID",
  "VAR_LOGFILE", "VAR_SERVER_COUNT", "VAR_TCP_COUNT", "VAR_PIDFILE",
  "VAR_PORT", "VAR_STATISTICS", "VAR_CHROOT", "VAR_USERNAME",
  "VAR_ZONESDIR", "VAR_XFRDFILE", "VAR_DIFFFILE",
  "VAR_XFRD_RELOAD_TIMEOUT", "VAR_TCP_QUERY_COUNT", "VAR_TCP_TIMEOUT",
  "VAR_IPV4_EDNS_SIZE", "VAR_IPV6_EDNS_SIZE", "VAR_DO_IP4", "VAR_DO_IP6",
  "VAR_ZONEFILE", "VAR_ZONE", "VAR_ALLOW_NOTIFY", "VAR_REQUEST_XFR",
  "VAR_NOTIFY", "VAR_PROVIDE_XFR", "VAR_NOTIFY_RETRY",
  "VAR_OUTGOING_INTERFACE", "VAR_ALLOW_AXFR_FALLBACK", "VAR_KEY",
  "VAR_ALGORITHM", "VAR_SECRET", "VAR_AXFR", "VAR_UDP", "VAR_VERBOSITY",
  "VAR_HIDE_VERSION", "VAR_PATTERN", "VAR_INCLUDEPATTERN",
  "VAR_ZONELISTFILE", "VAR_REMOTE_CONTROL", "VAR_CONTROL_ENABLE",
  "VAR_CONTROL_INTERFACE", "VAR_CONTROL_PORT", "VAR_SERVER_KEY_FILE",
  "VAR_SERVER_CERT_FILE", "VAR_CONTROL_KEY_FILE", "VAR_CONTROL_CERT_FILE",
  "VAR_XFRDIR", "VAR_RRL_SIZE", "VAR_RRL_RATELIMIT", "VAR_RRL_SLIP",
  "VAR_RRL_IPV4_PREFIX_LENGTH", "VAR_RRL_IPV6_PREFIX_LENGTH",
  "VAR_RRL_WHITELIST_RATELIMIT", "VAR_RRL_WHITELIST",
  "VAR_ZONEFILES_CHECK", "VAR_ZONEFILES_WRITE", "VAR_LOG_TIME_ASCII",
  "VAR_ROUND_ROBIN", "$accept", "toplevelvars", "toplevelvar",
  "serverstart", "contents_server", "content_server", "server_ip_address",
  "server_ip_transparent", "server_debug_mode", "server_verbosity",
  "server_hide_version", "server_ip4_only", "server_ip6_only",
  "server_do_ip4", "server_do_ip6", "server_database", "server_identity",
  "server_nsid", "server_logfile", "server_log_time_ascii",
  "server_round_robin", "server_server_count", "server_tcp_count",
  "server_pidfile", "server_port", "server_statistics", "server_chroot",
  "server_username", "server_zonesdir", "server_zonelistfile",
  "server_xfrdir", "server_difffile", "server_xfrdfile",
  "server_xfrd_reload_timeout", "server_tcp_query_count",
  "server_tcp_timeout", "server_ipv4_edns_size", "server_ipv6_edns_size",
  "server_rrl_size", "server_rrl_ratelimit", "server_rrl_slip",
  "server_rrl_ipv4_prefix_length", "server_rrl_ipv6_prefix_length",
  "server_rrl_whitelist_ratelimit", "server_zonefiles_check",
  "server_zonefiles_write", "rcstart", "contents_rc", "content_rc",
  "rc_control_enable", "rc_control_port", "rc_control_interface",
  "rc_server_key_file", "rc_server_cert_file", "rc_control_key_file",
  "rc_control_cert_file", "patternstart", "contents_pattern",
  "content_pattern", "zone_config_item", "pattern_name", "include_pattern",
  "zonestart", "contents_zone", "content_zone", "zone_name",
  "zone_zonefile", "zone_allow_notify", "zone_request_xfr",
  "zone_request_xfr_data", "zone_notify", "zone_notify_retry",
  "zone_provide_xfr", "zone_outgoing_interface",
  "zone_allow_axfr_fallback", "zone_rrl_whitelist", "keystart",
  "contents_key", "content_key", "key_name", "key_algorithm", "key_secret", YY_NULL
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    80,    80,    80,    80,    80,    81,
      82,    82,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   135,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   138,   139,   140,   141,   141,   142,
     142,   143,   144,   145,   146,   147,   147,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   155,   156,   156,   156,
     157,   158,   159
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     1,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     1,     1,
       1,     2,     2,     3,     2,     2,     3,     3,     3,     2,
       3,     2,     2,     2,     1,     2,     1,     1,     1,     1,
       2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     9,   126,   144,   109,    92,     3,    11,
      94,     0,     0,     0,     4,     8,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,   111,   113,
     112,   122,   114,   115,   116,   117,   118,   119,   120,   121,
     123,     0,   130,     5,   128,   129,     0,     0,     0,     6,
     146,   147,   148,   149,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,    12,    13,    14,    36,    37,
      15,    16,    47,    48,    17,    18,    19,    20,    50,    51,
      21,    22,    23,    24,    25,    26,    27,    28,    38,    39,
      29,    30,    31,    32,    33,    34,    35,    40,    41,    42,
      43,    44,    45,    46,    49,     0,     0,     0,     0,     0,
       0,     0,    93,    95,    97,    96,    98,    99,   100,   101,
     124,   132,     0,     0,     0,     0,   134,     0,     0,   139,
     141,   142,   125,   143,   110,   131,   127,   150,   151,   152,
     145,    52,    53,    54,    57,    58,    61,    62,    63,    64,
      67,    68,    69,    70,    71,    72,    73,    74,    78,    77,
      79,    80,    81,    82,    83,    59,    60,    55,    56,    75,
      76,    84,    85,    86,    87,    88,    89,    90,    91,    65,
      66,   102,   104,   103,   105,   106,   107,   108,   133,   135,
       0,     0,   138,   140,   136,   137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    14,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    10,    15,   142,   143,
     144,   145,   146,   147,   148,   149,    11,    27,    28,    29,
      30,    31,    12,    43,    44,    45,    32,    33,    34,   156,
      35,    36,    37,    38,    39,    40,    13,    49,    50,    51,
      52,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -34
static const yytype_int16 yypact[] =
{
     -34,    74,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,    26,    48,    30,   -13,   -33,    27,    29,    33,    24,
      35,    36,    37,    38,    39,    40,    41,    26,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,    42,   -34,    48,   -34,   -34,    67,    68,    71,    30,
     -34,   -34,   -34,   -34,    73,    76,    78,    86,    87,    88,
      90,    91,    92,    93,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   105,   106,   107,   108,   109,   110,   113,
     114,   115,   116,   117,   118,   120,   121,   123,   124,   125,
     126,   127,   128,   129,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   130,   131,   132,   133,   134,
     135,   136,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   137,   138,   139,   140,   -34,   141,   142,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     143,   144,   -34,   -34,   -34,   -34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,     6,    23,
     -34,   -34,   -34,   -34,    -7,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   111,   -34,
     -34,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   135,   136,   137,   138,
     139,   140,   141,   164,   153,    42,   166,   150,    16,   151,
      80,    81,    46,   152,    82,   157,   158,   159,   160,   161,
     162,   163,   165,    83,    84,    85,    86,    87,    88,    89,
      41,    90,    91,    92,    93,    17,    42,    18,    19,    20,
      21,    22,    23,    24,     2,   154,   155,   167,   168,    47,
      48,   169,    25,   171,     0,     3,   172,    17,   173,    18,
      19,    20,    21,    22,    23,    24,   174,   175,   176,    26,
     177,   178,   179,   180,    25,   181,   182,   183,   184,   185,
     186,   187,   188,   189,     4,   190,   191,   192,   193,   194,
     195,    26,     5,   196,   197,   198,   199,   200,   201,     6,
     202,   203,     7,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,     0,     0,     0,     0,     0,
     170
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-34))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    59,    60,    61,    62,
      63,    64,    65,    27,    10,    12,    43,    10,    12,    10,
      53,    54,    12,    10,    57,    10,    10,    10,    10,    10,
      10,    10,    10,    66,    67,    68,    69,    70,    71,    72,
      12,    74,    75,    76,    77,    39,    43,    41,    42,    43,
      44,    45,    46,    47,     0,    51,    52,    10,    10,    49,
      50,    10,    56,    10,    -1,    11,    10,    39,    10,    41,
      42,    43,    44,    45,    46,    47,    10,    10,    10,    73,
      10,    10,    10,    10,    56,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    40,    10,    10,    10,    10,    10,
      10,    73,    48,    10,    10,    10,    10,    10,    10,    55,
      10,    10,    58,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    -1,    -1,    -1,    -1,    -1,
      49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    79,     0,    11,    40,    48,    55,    58,    80,    81,
     124,   134,   140,   154,    82,   125,    12,    39,    41,    42,
      43,    44,    45,    46,    47,    56,    73,   135,   136,   137,
     138,   139,   144,   145,   146,   148,   149,   150,   151,   152,
     153,    12,   137,   141,   142,   143,    12,    49,    50,   155,
     156,   157,   158,   159,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      53,    54,    57,    66,    67,    68,    69,    70,    71,    72,
      74,    75,    76,    77,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,    59,    60,    61,    62,    63,
      64,    65,   126,   127,   128,   129,   130,   131,   132,   133,
      10,    10,    10,    10,    51,    52,   147,    10,    10,    10,
      10,    10,    10,    10,   136,    10,   142,    10,    10,    10,
     156,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
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
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
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
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
/* Line 1787 of yacc.c  */
#line 80 "configparser.y"
    { OUTYY(("\nP(server:)\n")); 
		if(cfg_parser->server_settings_seen) {
			yyerror("duplicate server: element.");
		}
		cfg_parser->server_settings_seen = 1;
	}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 101 "configparser.y"
    { 
		OUTYY(("P(server_ip_address:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(cfg_parser->current_ip_address_option) {
			cfg_parser->current_ip_address_option->next = 
				(ip_address_option_t*)region_alloc(
				cfg_parser->opt->region, sizeof(ip_address_option_t));
			cfg_parser->current_ip_address_option = 
				cfg_parser->current_ip_address_option->next;
			cfg_parser->current_ip_address_option->next=0;
		} else {
			cfg_parser->current_ip_address_option = 
				(ip_address_option_t*)region_alloc(
				cfg_parser->opt->region, sizeof(ip_address_option_t));
			cfg_parser->current_ip_address_option->next=0;
			cfg_parser->opt->ip_addresses = cfg_parser->current_ip_address_option;
		}

		cfg_parser->current_ip_address_option->address = 
			region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 123 "configparser.y"
    { 
		OUTYY(("P(server_ip_transparent:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->ip_transparent = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 131 "configparser.y"
    { 
		OUTYY(("P(server_debug_mode:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->debug_mode = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 139 "configparser.y"
    { 
		OUTYY(("P(server_verbosity:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->verbosity = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 147 "configparser.y"
    { 
		OUTYY(("P(server_hide_version:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->hide_version = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 155 "configparser.y"
    { 
		/* for backwards compatibility in config file with NSD3 */
		OUTYY(("P(server_ip4_only:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else if(strcmp((yyvsp[(2) - (2)].str), "yes")==0) {
			cfg_parser->opt->do_ip4 = 1;
			cfg_parser->opt->do_ip6 = 0;
		}
	}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 167 "configparser.y"
    { 
		/* for backwards compatibility in config file with NSD3 */
		OUTYY(("P(server_ip6_only:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else if(strcmp((yyvsp[(2) - (2)].str), "yes")==0) {
			cfg_parser->opt->do_ip6 = 1;
			cfg_parser->opt->do_ip4 = 0;
		}
	}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 179 "configparser.y"
    { 
		OUTYY(("P(server_do_ip4:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->do_ip4 = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 187 "configparser.y"
    { 
		OUTYY(("P(server_do_ip6:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->do_ip6 = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 195 "configparser.y"
    { 
		OUTYY(("P(server_database:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->database = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		if(cfg_parser->opt->database[0] == 0 &&
			cfg_parser->opt->zonefiles_write == 0)
			cfg_parser->opt->zonefiles_write = ZONEFILES_WRITE_INTERVAL;
	}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 204 "configparser.y"
    { 
		OUTYY(("P(server_identity:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->identity = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 210 "configparser.y"
    { 
		unsigned char* nsid = 0;
		uint16_t nsid_len = 0;

		OUTYY(("P(server_nsid:%s)\n", (yyvsp[(2) - (2)].str)));

		if (strncasecmp((yyvsp[(2) - (2)].str), "ascii_", 6) == 0) {
			nsid_len = strlen((yyvsp[(2) - (2)].str)+6);
			cfg_parser->opt->nsid = region_alloc(cfg_parser->opt->region, nsid_len*2+1);
			hex_ntop((uint8_t*)(yyvsp[(2) - (2)].str)+6, nsid_len, (char*)cfg_parser->opt->nsid, nsid_len*2+1);
		} else if (strlen((yyvsp[(2) - (2)].str)) % 2 != 0) {
			yyerror("the NSID must be a hex string of an even length.");
		} else {
			nsid_len = strlen((yyvsp[(2) - (2)].str)) / 2;
			nsid = xalloc(nsid_len);
			if (hex_pton((yyvsp[(2) - (2)].str), nsid, nsid_len) == -1)
				yyerror("hex string cannot be parsed in NSID.");
			else
				cfg_parser->opt->nsid = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
			free(nsid);
		}
	}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 234 "configparser.y"
    { 
		OUTYY(("P(server_logfile:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->logfile = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 240 "configparser.y"
    { 
		OUTYY(("P(server_log_time_ascii:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->opt->log_time_ascii = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
			log_time_asc = cfg_parser->opt->log_time_ascii;
		}
	}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 251 "configparser.y"
    { 
		OUTYY(("P(server_round_robin:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->opt->round_robin = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
			round_robin = cfg_parser->opt->round_robin;
		}
	}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 262 "configparser.y"
    { 
		OUTYY(("P(server_server_count:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) <= 0)
			yyerror("number greater than zero expected");
		else cfg_parser->opt->server_count = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 270 "configparser.y"
    { 
		OUTYY(("P(server_tcp_count:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) <= 0)
			yyerror("number greater than zero expected");
		else cfg_parser->opt->tcp_count = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 278 "configparser.y"
    { 
		OUTYY(("P(server_pidfile:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->pidfile = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 284 "configparser.y"
    { 
		OUTYY(("P(server_port:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->port = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 290 "configparser.y"
    { 
		OUTYY(("P(server_statistics:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->statistics = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 298 "configparser.y"
    { 
		OUTYY(("P(server_chroot:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->chroot = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 304 "configparser.y"
    { 
		OUTYY(("P(server_username:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->username = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 310 "configparser.y"
    { 
		OUTYY(("P(server_zonesdir:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->zonesdir = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 316 "configparser.y"
    { 
		OUTYY(("P(server_zonelistfile:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->zonelistfile = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 322 "configparser.y"
    { 
		OUTYY(("P(server_xfrdir:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->xfrdir = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 328 "configparser.y"
    { 
		OUTYY(("P(server_difffile:%s)\n", (yyvsp[(2) - (2)].str))); 
		/* ignore the value for backwards compatibility in config file*/
	}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 334 "configparser.y"
    { 
		OUTYY(("P(server_xfrdfile:%s)\n", (yyvsp[(2) - (2)].str))); 
		cfg_parser->opt->xfrdfile = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 340 "configparser.y"
    { 
		OUTYY(("P(server_xfrd_reload_timeout:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->xfrd_reload_timeout = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 348 "configparser.y"
    { 
		OUTYY(("P(server_tcp_query_count:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->tcp_query_count = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 356 "configparser.y"
    { 
		OUTYY(("P(server_tcp_timeout:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->tcp_timeout = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 364 "configparser.y"
    { 
		OUTYY(("P(server_ipv4_edns_size:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->ipv4_edns_size = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 372 "configparser.y"
    { 
		OUTYY(("P(server_ipv6_edns_size:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->ipv6_edns_size = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 380 "configparser.y"
    { 
		OUTYY(("P(server_rrl_size:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		if(atoi((yyvsp[(2) - (2)].str)) <= 0)
			yyerror("number greater than zero expected");
		cfg_parser->opt->rrl_size = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 390 "configparser.y"
    { 
		OUTYY(("P(server_rrl_ratelimit:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		cfg_parser->opt->rrl_ratelimit = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 398 "configparser.y"
    { 
		OUTYY(("P(server_rrl_slip:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		if(atoi((yyvsp[(2) - (2)].str)) < 0)
			yyerror("number equal or greater than zero expected");
		cfg_parser->opt->rrl_slip = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 408 "configparser.y"
    {
		OUTYY(("P(server_rrl_ipv4_prefix_length:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		if(atoi((yyvsp[(2) - (2)].str)) < 0 || atoi((yyvsp[(2) - (2)].str)) > 32)
			yyerror("invalid IPv4 prefix length");
		cfg_parser->opt->rrl_ipv4_prefix_length = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 418 "configparser.y"
    {
		OUTYY(("P(server_rrl_ipv6_prefix_length:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		if(atoi((yyvsp[(2) - (2)].str)) < 0 || atoi((yyvsp[(2) - (2)].str)) > 64)
			yyerror("invalid IPv6 prefix length");
		cfg_parser->opt->rrl_ipv6_prefix_length = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 428 "configparser.y"
    { 
		OUTYY(("P(server_rrl_whitelist_ratelimit:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		cfg_parser->opt->rrl_whitelist_ratelimit = atoi((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 436 "configparser.y"
    { 
		OUTYY(("P(server_zonefiles_check:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->zonefiles_check = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 444 "configparser.y"
    { 
		OUTYY(("P(server_zonefiles_write:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->zonefiles_write = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 453 "configparser.y"
    {
		OUTYY(("\nP(remote-control:)\n"));
	}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 464 "configparser.y"
    {
		OUTYY(("P(control_enable:%s)\n", (yyvsp[(2) - (2)].str)));
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->control_enable = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
	}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 472 "configparser.y"
    {
		OUTYY(("P(control_port:%s)\n", (yyvsp[(2) - (2)].str)));
		if(atoi((yyvsp[(2) - (2)].str)) == 0)
			yyerror("control port number expected");
		else cfg_parser->opt->control_port = atoi((yyvsp[(2) - (2)].str));
	}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 480 "configparser.y"
    {
		ip_address_option_t* o = (ip_address_option_t*)region_alloc(
			cfg_parser->opt->region, sizeof(ip_address_option_t));
		OUTYY(("P(control_interface:%s)\n", (yyvsp[(2) - (2)].str)));
		o->next = cfg_parser->opt->control_interface;
		cfg_parser->opt->control_interface = o;
		o->address = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 490 "configparser.y"
    {
	OUTYY(("P(rc_server_key_file:%s)\n", (yyvsp[(2) - (2)].str)));
	cfg_parser->opt->server_key_file = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 496 "configparser.y"
    {
	OUTYY(("P(rc_server_cert_file:%s)\n", (yyvsp[(2) - (2)].str)));
	cfg_parser->opt->server_cert_file = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 502 "configparser.y"
    {
	OUTYY(("P(rc_control_key_file:%s)\n", (yyvsp[(2) - (2)].str)));
	cfg_parser->opt->control_key_file = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 508 "configparser.y"
    {
	OUTYY(("P(rc_control_cert_file:%s)\n", (yyvsp[(2) - (2)].str)));
	cfg_parser->opt->control_cert_file = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 516 "configparser.y"
    { 
		OUTYY(("\nP(pattern:)\n")); 
		if(cfg_parser->current_zone) {
			if(!cfg_parser->current_zone->name) 
				c_error("previous zone has no name");
			else {
				if(!nsd_options_insert_zone(cfg_parser->opt, 
					cfg_parser->current_zone))
					c_error("duplicate zone");
			}
			if(!cfg_parser->current_zone->pattern) 
				c_error("previous zone has no pattern");
			cfg_parser->current_zone = NULL;
		}
		if(cfg_parser->current_pattern) {
			if(!cfg_parser->current_pattern->pname) 
				c_error("previous pattern has no name");
			else {
				if(!nsd_options_insert_pattern(cfg_parser->opt, 
					cfg_parser->current_pattern))
					c_error_msg("duplicate pattern %s",
						cfg_parser->current_pattern->pname);
			}
		}
		cfg_parser->current_pattern = pattern_options_create(
			cfg_parser->opt->region);
		cfg_parser->current_allow_notify = 0;
		cfg_parser->current_request_xfr = 0;
		cfg_parser->current_notify = 0;
		cfg_parser->current_provide_xfr = 0;
		cfg_parser->current_outgoing_interface = 0;
	}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 556 "configparser.y"
    { 
		OUTYY(("P(pattern_name:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		if(strchr((yyvsp[(2) - (2)].str), ' '))
			c_error_msg("space is not allowed in pattern name: "
				"'%s'", (yyvsp[(2) - (2)].str));
		cfg_parser->current_pattern->pname = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 568 "configparser.y"
    {
		OUTYY(("P(include-pattern:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		config_apply_pattern((yyvsp[(2) - (2)].str));
	}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 579 "configparser.y"
    { 
		OUTYY(("\nP(zone:)\n")); 
		if(cfg_parser->current_zone) {
			if(!cfg_parser->current_zone->name) 
				c_error("previous zone has no name");
			else {
				if(!nsd_options_insert_zone(cfg_parser->opt, 
					cfg_parser->current_zone))
					c_error("duplicate zone");
			}
			if(!cfg_parser->current_zone->pattern) 
				c_error("previous zone has no pattern");
		}
		if(cfg_parser->current_pattern) {
			if(!cfg_parser->current_pattern->pname) 
				c_error("previous pattern has no name");
			else {
				if(!nsd_options_insert_pattern(cfg_parser->opt, 
					cfg_parser->current_pattern))
					c_error_msg("duplicate pattern %s",
						cfg_parser->current_pattern->pname);
			}
		}
		cfg_parser->current_zone = zone_options_create(cfg_parser->opt->region);
		cfg_parser->current_zone->part_of_config = 1;
		cfg_parser->current_pattern = pattern_options_create(
			cfg_parser->opt->region);
		cfg_parser->current_pattern->implicit = 1;
		cfg_parser->current_zone->pattern = cfg_parser->current_pattern;
		cfg_parser->current_allow_notify = 0;
		cfg_parser->current_request_xfr = 0;
		cfg_parser->current_notify = 0;
		cfg_parser->current_provide_xfr = 0;
		cfg_parser->current_outgoing_interface = 0;
	}
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 618 "configparser.y"
    { 
		char* s;
		OUTYY(("P(zone_name:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_zone);
		assert(cfg_parser->current_pattern);
#endif
		cfg_parser->current_zone->name = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		s = (char*)region_alloc(cfg_parser->opt->region,
			strlen((yyvsp[(2) - (2)].str))+strlen(PATTERN_IMPLICIT_MARKER)+1);
		memmove(s, PATTERN_IMPLICIT_MARKER,
			strlen(PATTERN_IMPLICIT_MARKER));
		memmove(s+strlen(PATTERN_IMPLICIT_MARKER), (yyvsp[(2) - (2)].str), strlen((yyvsp[(2) - (2)].str))+1);
		if(pattern_options_find(cfg_parser->opt, s))
			c_error_msg("zone %s cannot be created because "
				"implicit pattern %s already exists", (yyvsp[(2) - (2)].str), s);
		cfg_parser->current_pattern->pname = s;
	}
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 638 "configparser.y"
    { 
		OUTYY(("P(zonefile:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		cfg_parser->current_pattern->zonefile = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
	}
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 647 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str));
		OUTYY(("P(allow_notify:%s %s)\n", (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str))); 
		if(cfg_parser->current_allow_notify)
			cfg_parser->current_allow_notify->next = acl;
		else
			cfg_parser->current_pattern->allow_notify = acl;
		cfg_parser->current_allow_notify = acl;
	}
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 658 "configparser.y"
    {
	}
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 662 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str));
		OUTYY(("P(request_xfr:%s %s)\n", (yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str))); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 674 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str));
		acl->use_axfr_only = 1;
		OUTYY(("P(request_xfr:%s %s)\n", (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str))); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 687 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str));
		acl->allow_udp = 1;
		OUTYY(("P(request_xfr:%s %s)\n", (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str))); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 701 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str));
		OUTYY(("P(notify:%s %s)\n", (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str))); 
		if(acl->blocked) c_error("blocked address used for notify");
		if(acl->rangetype!=acl_range_single) c_error("address range used for notify");
		if(cfg_parser->current_notify)
			cfg_parser->current_notify->next = acl;
		else
			cfg_parser->current_pattern->notify = acl;
		cfg_parser->current_notify = acl;
	}
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 714 "configparser.y"
    { 
		OUTYY(("P(notify_retry:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(atoi((yyvsp[(2) - (2)].str)) == 0 && strcmp((yyvsp[(2) - (2)].str), "0") != 0)
			yyerror("number expected");
		else {
			cfg_parser->current_pattern->notify_retry = atoi((yyvsp[(2) - (2)].str));
			cfg_parser->current_pattern->notify_retry_is_default=0;
		}
	}
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 725 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str));
		OUTYY(("P(provide_xfr:%s %s)\n", (yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].str))); 
		if(cfg_parser->current_provide_xfr)
			cfg_parser->current_provide_xfr->next = acl;
		else
			cfg_parser->current_pattern->provide_xfr = acl;
		cfg_parser->current_provide_xfr = acl;
	}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 736 "configparser.y"
    { 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, (yyvsp[(2) - (2)].str), "NOKEY");
		OUTYY(("P(outgoing_interface:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(acl->rangetype!=acl_range_single) c_error("address range used for outgoing interface");
		if(cfg_parser->current_outgoing_interface)
			cfg_parser->current_outgoing_interface->next = acl;
		else
			cfg_parser->current_pattern->outgoing_interface = acl;
		cfg_parser->current_outgoing_interface = acl;
	}
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 748 "configparser.y"
    { 
		OUTYY(("P(allow_axfr_fallback:%s)\n", (yyvsp[(2) - (2)].str))); 
		if(strcmp((yyvsp[(2) - (2)].str), "yes") != 0 && strcmp((yyvsp[(2) - (2)].str), "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->current_pattern->allow_axfr_fallback = (strcmp((yyvsp[(2) - (2)].str), "yes")==0);
			cfg_parser->current_pattern->allow_axfr_fallback_is_default = 0;
		}
	}
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 759 "configparser.y"
    { 
		OUTYY(("P(zone_rrl_whitelist:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifdef RATELIMIT
		cfg_parser->current_pattern->rrl_whitelist |= rrlstr2type((yyvsp[(2) - (2)].str));
#endif
	}
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 769 "configparser.y"
    { 
		OUTYY(("\nP(key:)\n")); 
		if(cfg_parser->current_key) {
			if(!cfg_parser->current_key->name) c_error("previous key has no name");
			if(!cfg_parser->current_key->algorithm) c_error("previous key has no algorithm");
			if(!cfg_parser->current_key->secret) c_error("previous key has no secret blob");
			key_options_insert(cfg_parser->opt, cfg_parser->current_key);
		}
		cfg_parser->current_key = key_options_create(cfg_parser->opt->region);
	}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 783 "configparser.y"
    { 
		const dname_type* d;
		OUTYY(("P(key_name:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->name = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		d = dname_parse(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		if(!d)	c_error_msg("Failed to parse tsig key name %s", (yyvsp[(2) - (2)].str));
		else	region_recycle(cfg_parser->opt->region, (void*)d,
				dname_total_size(d));
	}
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 797 "configparser.y"
    { 
		OUTYY(("P(key_algorithm:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->algorithm = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		if(tsig_get_algorithm_by_name((yyvsp[(2) - (2)].str)) == NULL)
			c_error_msg("Bad tsig algorithm %s", (yyvsp[(2) - (2)].str));
	}
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 808 "configparser.y"
    { 
		uint8_t data[16384];
		int size;
		OUTYY(("key_secret:%s)\n", (yyvsp[(2) - (2)].str))); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->secret = region_strdup(cfg_parser->opt->region, (yyvsp[(2) - (2)].str));
		size = b64_pton((yyvsp[(2) - (2)].str), data, sizeof(data));
		if(size == -1) {
			c_error_msg("Cannot base64 decode tsig secret %s",
				cfg_parser->current_key->name?
				cfg_parser->current_key->name:"");
		} else if(size != 0) {
			memset(data, 0xdd, size); /* wipe secret */
		}
	}
    break;


/* Line 1787 of yacc.c  */
#line 2724 "configparser.c"
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

  *++yyvsp = yylval;


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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2048 of yacc.c  */
#line 827 "configparser.y"


/* parse helper routines could be here */

