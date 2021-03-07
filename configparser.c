#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 11 "./configparser.y"
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

#if 1
#define OUTYY(s) printf s /* used ONLY when debugging */
#else
#define OUTYY(s)
#endif

#line 42 "./configparser.y"
typedef union {
	char*	str;
} YYSTYPE;
#line 58 "configparser.c"
#define SPACE 257
#define LETTER 258
#define NEWLINE 259
#define COMMENT 260
#define COLON 261
#define ANY 262
#define ZONESTR 263
#define STRING 264
#define VAR_SERVER 265
#define VAR_NAME 266
#define VAR_IP_ADDRESS 267
#define VAR_IP_TRANSPARENT 268
#define VAR_DEBUG_MODE 269
#define VAR_IP4_ONLY 270
#define VAR_IP6_ONLY 271
#define VAR_DATABASE 272
#define VAR_IDENTITY 273
#define VAR_NSID 274
#define VAR_LOGFILE 275
#define VAR_SERVER_COUNT 276
#define VAR_TCP_COUNT 277
#define VAR_PIDFILE 278
#define VAR_PORT 279
#define VAR_STATISTICS 280
#define VAR_CHROOT 281
#define VAR_USERNAME 282
#define VAR_ZONESDIR 283
#define VAR_XFRDFILE 284
#define VAR_DIFFFILE 285
#define VAR_XFRD_RELOAD_TIMEOUT 286
#define VAR_TCP_QUERY_COUNT 287
#define VAR_TCP_TIMEOUT 288
#define VAR_IPV4_EDNS_SIZE 289
#define VAR_IPV6_EDNS_SIZE 290
#define VAR_DO_IP4 291
#define VAR_DO_IP6 292
#define VAR_ZONEFILE 293
#define VAR_ZONE 294
#define VAR_ALLOW_NOTIFY 295
#define VAR_REQUEST_XFR 296
#define VAR_NOTIFY 297
#define VAR_PROVIDE_XFR 298
#define VAR_NOTIFY_RETRY 299
#define VAR_OUTGOING_INTERFACE 300
#define VAR_ALLOW_AXFR_FALLBACK 301
#define VAR_KEY 302
#define VAR_ALGORITHM 303
#define VAR_SECRET 304
#define VAR_AXFR 305
#define VAR_UDP 306
#define VAR_VERBOSITY 307
#define VAR_HIDE_VERSION 308
#define VAR_PATTERN 309
#define VAR_INCLUDEPATTERN 310
#define VAR_ZONELISTFILE 311
#define VAR_REMOTE_CONTROL 312
#define VAR_CONTROL_ENABLE 313
#define VAR_CONTROL_INTERFACE 314
#define VAR_CONTROL_PORT 315
#define VAR_SERVER_KEY_FILE 316
#define VAR_SERVER_CERT_FILE 317
#define VAR_CONTROL_KEY_FILE 318
#define VAR_CONTROL_CERT_FILE 319
#define VAR_XFRDIR 320
#define VAR_RRL_SIZE 321
#define VAR_RRL_RATELIMIT 322
#define VAR_RRL_SLIP 323
#define VAR_RRL_IPV4_PREFIX_LENGTH 324
#define VAR_RRL_IPV6_PREFIX_LENGTH 325
#define VAR_RRL_WHITELIST_RATELIMIT 326
#define VAR_RRL_WHITELIST 327
#define VAR_ZONEFILES_CHECK 328
#define VAR_ZONEFILES_WRITE 329
#define VAR_LOG_TIME_ASCII 330
#define VAR_DO_HEALTH_CHECK 331
#define VAR_GEO_DB_FILEPATH 332
#define VAR_ROUND_ROBIN 333
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    1,    1,    1,    1,    1,    2,    3,    3,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   13,   14,   15,   37,   38,   16,   17,   48,
   49,   18,   19,   20,   21,   51,   52,   53,   54,   22,
   23,   24,   25,   26,   27,   28,   29,   39,   40,   30,
   31,   32,   33,   34,   35,   36,   41,   42,   43,   44,
   45,   46,   47,   50,   10,   11,   11,   55,   55,   55,
   55,   55,   55,   55,   56,   58,   57,   59,   60,   61,
   62,    8,    9,    9,   63,   63,   65,   65,   65,   65,
   65,   65,   65,   65,   65,   65,   64,   74,    4,    5,
    5,   76,   76,   77,   66,   67,   68,   78,   78,   78,
   69,   70,   71,   72,   73,   75,    6,    7,    7,   79,
   79,   79,   80,   81,   82,
};
short yylen[] = {                                         2,
    0,    2,    2,    2,    2,    2,    2,    1,    2,    0,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    1,    2,    0,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    2,    2,    2,
    2,    1,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    1,    2,
    1,    1,    1,    2,    2,    3,    2,    2,    3,    3,
    3,    2,    3,    2,    2,    2,    1,    2,    1,    1,
    1,    1,    2,    2,    2,
};
short yydefred[] = {                                      1,
    0,    8,  129,  147,  112,   95,    2,   10,    0,    0,
    0,   97,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  133,  117,  118,  119,  120,
  121,  122,  123,  124,  125,  126,  131,  132,    0,    0,
    0,    0,  149,  150,  151,  152,    0,    0,  114,  115,
  116,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    9,   11,   12,   13,   14,   15,
   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,
   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
   36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
   46,   47,   48,   49,   50,   51,   52,  134,  135,    0,
    0,    0,    0,  137,    0,    0,  142,  144,  145,  128,
  146,  130,  153,  154,  155,  148,  127,  113,    0,    0,
    0,    0,    0,    0,    0,   96,   98,   99,  100,  101,
  102,  103,  104,   53,   54,   55,   58,   59,   62,   63,
   64,   65,   70,   71,   72,   73,   74,   75,   76,   77,
   81,   80,   82,   83,   84,   85,   86,   60,   61,   56,
   57,   78,   79,   87,   88,   89,   90,   91,   92,   93,
   94,   66,   68,   69,   67,  136,  138,    0,    0,  141,
  143,  105,  107,  106,  108,  109,  110,  111,  139,  140,
};
short yydgoto[] = {                                       1,
    7,    8,   13,    9,   25,   10,   42,   11,   48,   12,
   52,   95,   96,   97,   98,   99,  100,  101,  102,  103,
  104,  105,  106,  107,  108,  109,  110,  111,  112,  113,
  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,
  124,  125,  126,  127,  128,  129,  130,  131,  132,  133,
  134,  135,  136,  137,  166,  167,  168,  169,  170,  171,
  172,  173,   49,   50,   26,   27,   28,   29,   30,   31,
   32,   33,   34,   35,   36,   37,   38,  144,   43,   44,
   45,   46,
};
short yysindex[] = {                                      0,
 -173,    0,    0,    0,    0,    0,    0,    0, -200, -251,
 -182,    0, -243, -264, -260, -259, -255, -256, -254, -253,
 -252, -250, -248, -246, -200,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -245, -244,
 -242, -251,    0,    0,    0,    0, -202, -182,    0,    0,
    0, -258, -201, -197, -195, -194, -193, -192, -191, -190,
 -189, -188, -170, -162, -161, -160, -159, -158, -157, -156,
 -155, -152, -144, -142, -141, -140, -139, -138, -134, -133,
 -132, -131, -130, -129, -127, -126, -124, -123, -122, -121,
 -120, -118, -117, -116,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -115,
 -114, -113, -112,    0, -111, -110,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -109, -108,
 -107, -106, -105, -104, -103,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -102, -101,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    2,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    0,    0,    0,    0,    0,    7,    0,    0,
    0,   23,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -42,    0,    6,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -12,    0,    0,  -21,    0,
    0,    0,
};
#define YYTABLESIZE 335
short yytable[] = {                                     138,
    3,    4,    5,  139,  140,  158,    6,  145,  141,  146,
  147,  148,  152,  149,   39,  150,   51,  151,  153,  154,
  156,  155,    7,   53,   54,   55,   56,   57,   58,   59,
   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
   70,   71,   72,   73,   74,   75,   76,   77,   78,  142,
  143,   40,   41,   51,  159,  160,  161,  162,  163,  164,
  165,  157,  174,   79,   80,   14,  175,   81,  176,  177,
  178,  179,  180,  181,  182,  183,   82,   83,   84,   85,
   86,   87,   88,   47,   89,   90,   91,   92,   93,   94,
    0,    2,   15,  184,   16,   17,   18,   19,   20,   21,
   22,  185,  186,  187,  188,  189,  190,  191,  192,   23,
   15,  193,   16,   17,   18,   19,   20,   21,   22,  194,
    3,  195,  196,  197,  198,  199,   24,   23,    4,  200,
  201,  202,  203,  204,  205,    5,  206,  207,    6,  208,
  209,  210,  211,  212,   24,  213,  214,  215,  216,  217,
  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,
  228,  229,  230,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,    4,    5,    0,    0,
    0,    6,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    7,    0,    0,
    0,    0,    0,    0,    3,    4,    5,    0,    0,    0,
    6,    0,    3,    4,    5,    0,    0,    0,    6,    3,
    4,    5,    3,    4,    5,    6,    7,    0,    6,    0,
    0,    0,    0,    0,    7,    0,    0,    0,    0,    0,
    0,    7,    0,    0,    7,
};
short yycheck[] = {                                     264,
    0,    0,    0,  264,  264,   48,    0,  264,  264,  264,
  264,  264,   25,  264,  266,  264,   11,  264,  264,  264,
   42,  264,    0,  267,  268,  269,  270,  271,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  286,  287,  288,  289,  290,  291,  292,  305,
  306,  303,  304,   48,  313,  314,  315,  316,  317,  318,
  319,  264,  264,  307,  308,  266,  264,  311,  264,  264,
  264,  264,  264,  264,  264,  264,  320,  321,  322,  323,
  324,  325,  326,  266,  328,  329,  330,  331,  332,  333,
   -1,  265,  293,  264,  295,  296,  297,  298,  299,  300,
  301,  264,  264,  264,  264,  264,  264,  264,  264,  310,
  293,  264,  295,  296,  297,  298,  299,  300,  301,  264,
  294,  264,  264,  264,  264,  264,  327,  310,  302,  264,
  264,  264,  264,  264,  264,  309,  264,  264,  312,  264,
  264,  264,  264,  264,  327,  264,  264,  264,  264,  264,
  264,  264,  264,  264,  264,  264,  264,  264,  264,  264,
  264,  264,  264,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  265,  265,  265,   -1,   -1,
   -1,  265,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  265,   -1,   -1,
   -1,   -1,   -1,   -1,  294,  294,  294,   -1,   -1,   -1,
  294,   -1,  302,  302,  302,   -1,   -1,   -1,  302,  309,
  309,  309,  312,  312,  312,  309,  294,   -1,  312,   -1,
   -1,   -1,   -1,   -1,  302,   -1,   -1,   -1,   -1,   -1,
   -1,  309,   -1,   -1,  312,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 333
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"SPACE","LETTER","NEWLINE",
"COMMENT","COLON","ANY","ZONESTR","STRING","VAR_SERVER","VAR_NAME",
"VAR_IP_ADDRESS","VAR_IP_TRANSPARENT","VAR_DEBUG_MODE","VAR_IP4_ONLY",
"VAR_IP6_ONLY","VAR_DATABASE","VAR_IDENTITY","VAR_NSID","VAR_LOGFILE",
"VAR_SERVER_COUNT","VAR_TCP_COUNT","VAR_PIDFILE","VAR_PORT","VAR_STATISTICS",
"VAR_CHROOT","VAR_USERNAME","VAR_ZONESDIR","VAR_XFRDFILE","VAR_DIFFFILE",
"VAR_XFRD_RELOAD_TIMEOUT","VAR_TCP_QUERY_COUNT","VAR_TCP_TIMEOUT",
"VAR_IPV4_EDNS_SIZE","VAR_IPV6_EDNS_SIZE","VAR_DO_IP4","VAR_DO_IP6",
"VAR_ZONEFILE","VAR_ZONE","VAR_ALLOW_NOTIFY","VAR_REQUEST_XFR","VAR_NOTIFY",
"VAR_PROVIDE_XFR","VAR_NOTIFY_RETRY","VAR_OUTGOING_INTERFACE",
"VAR_ALLOW_AXFR_FALLBACK","VAR_KEY","VAR_ALGORITHM","VAR_SECRET","VAR_AXFR",
"VAR_UDP","VAR_VERBOSITY","VAR_HIDE_VERSION","VAR_PATTERN","VAR_INCLUDEPATTERN",
"VAR_ZONELISTFILE","VAR_REMOTE_CONTROL","VAR_CONTROL_ENABLE",
"VAR_CONTROL_INTERFACE","VAR_CONTROL_PORT","VAR_SERVER_KEY_FILE",
"VAR_SERVER_CERT_FILE","VAR_CONTROL_KEY_FILE","VAR_CONTROL_CERT_FILE",
"VAR_XFRDIR","VAR_RRL_SIZE","VAR_RRL_RATELIMIT","VAR_RRL_SLIP",
"VAR_RRL_IPV4_PREFIX_LENGTH","VAR_RRL_IPV6_PREFIX_LENGTH",
"VAR_RRL_WHITELIST_RATELIMIT","VAR_RRL_WHITELIST","VAR_ZONEFILES_CHECK",
"VAR_ZONEFILES_WRITE","VAR_LOG_TIME_ASCII","VAR_DO_HEALTH_CHECK",
"VAR_GEO_DB_FILEPATH","VAR_ROUND_ROBIN",
};
char *yyrule[] = {
"$accept : toplevelvars",
"toplevelvars :",
"toplevelvars : toplevelvars toplevelvar",
"toplevelvar : serverstart contents_server",
"toplevelvar : zonestart contents_zone",
"toplevelvar : keystart contents_key",
"toplevelvar : patternstart contents_pattern",
"toplevelvar : rcstart contents_rc",
"serverstart : VAR_SERVER",
"contents_server : contents_server content_server",
"contents_server :",
"content_server : server_ip_address",
"content_server : server_ip_transparent",
"content_server : server_debug_mode",
"content_server : server_ip4_only",
"content_server : server_ip6_only",
"content_server : server_database",
"content_server : server_identity",
"content_server : server_nsid",
"content_server : server_logfile",
"content_server : server_server_count",
"content_server : server_tcp_count",
"content_server : server_pidfile",
"content_server : server_port",
"content_server : server_statistics",
"content_server : server_chroot",
"content_server : server_username",
"content_server : server_zonesdir",
"content_server : server_difffile",
"content_server : server_xfrdfile",
"content_server : server_xfrd_reload_timeout",
"content_server : server_tcp_query_count",
"content_server : server_tcp_timeout",
"content_server : server_ipv4_edns_size",
"content_server : server_ipv6_edns_size",
"content_server : server_verbosity",
"content_server : server_hide_version",
"content_server : server_zonelistfile",
"content_server : server_xfrdir",
"content_server : server_rrl_size",
"content_server : server_rrl_ratelimit",
"content_server : server_rrl_slip",
"content_server : server_rrl_ipv4_prefix_length",
"content_server : server_rrl_ipv6_prefix_length",
"content_server : server_rrl_whitelist_ratelimit",
"content_server : server_zonefiles_check",
"content_server : server_do_ip4",
"content_server : server_do_ip6",
"content_server : server_zonefiles_write",
"content_server : server_log_time_ascii",
"content_server : server_round_robin",
"content_server : server_do_health_check",
"content_server : server_geo_db_file",
"server_ip_address : VAR_IP_ADDRESS STRING",
"server_ip_transparent : VAR_IP_TRANSPARENT STRING",
"server_debug_mode : VAR_DEBUG_MODE STRING",
"server_verbosity : VAR_VERBOSITY STRING",
"server_hide_version : VAR_HIDE_VERSION STRING",
"server_ip4_only : VAR_IP4_ONLY STRING",
"server_ip6_only : VAR_IP6_ONLY STRING",
"server_do_ip4 : VAR_DO_IP4 STRING",
"server_do_ip6 : VAR_DO_IP6 STRING",
"server_database : VAR_DATABASE STRING",
"server_identity : VAR_IDENTITY STRING",
"server_nsid : VAR_NSID STRING",
"server_logfile : VAR_LOGFILE STRING",
"server_log_time_ascii : VAR_LOG_TIME_ASCII STRING",
"server_round_robin : VAR_ROUND_ROBIN STRING",
"server_do_health_check : VAR_DO_HEALTH_CHECK STRING",
"server_geo_db_file : VAR_GEO_DB_FILEPATH STRING",
"server_server_count : VAR_SERVER_COUNT STRING",
"server_tcp_count : VAR_TCP_COUNT STRING",
"server_pidfile : VAR_PIDFILE STRING",
"server_port : VAR_PORT STRING",
"server_statistics : VAR_STATISTICS STRING",
"server_chroot : VAR_CHROOT STRING",
"server_username : VAR_USERNAME STRING",
"server_zonesdir : VAR_ZONESDIR STRING",
"server_zonelistfile : VAR_ZONELISTFILE STRING",
"server_xfrdir : VAR_XFRDIR STRING",
"server_difffile : VAR_DIFFFILE STRING",
"server_xfrdfile : VAR_XFRDFILE STRING",
"server_xfrd_reload_timeout : VAR_XFRD_RELOAD_TIMEOUT STRING",
"server_tcp_query_count : VAR_TCP_QUERY_COUNT STRING",
"server_tcp_timeout : VAR_TCP_TIMEOUT STRING",
"server_ipv4_edns_size : VAR_IPV4_EDNS_SIZE STRING",
"server_ipv6_edns_size : VAR_IPV6_EDNS_SIZE STRING",
"server_rrl_size : VAR_RRL_SIZE STRING",
"server_rrl_ratelimit : VAR_RRL_RATELIMIT STRING",
"server_rrl_slip : VAR_RRL_SLIP STRING",
"server_rrl_ipv4_prefix_length : VAR_RRL_IPV4_PREFIX_LENGTH STRING",
"server_rrl_ipv6_prefix_length : VAR_RRL_IPV6_PREFIX_LENGTH STRING",
"server_rrl_whitelist_ratelimit : VAR_RRL_WHITELIST_RATELIMIT STRING",
"server_zonefiles_check : VAR_ZONEFILES_CHECK STRING",
"server_zonefiles_write : VAR_ZONEFILES_WRITE STRING",
"rcstart : VAR_REMOTE_CONTROL",
"contents_rc : contents_rc content_rc",
"contents_rc :",
"content_rc : rc_control_enable",
"content_rc : rc_control_interface",
"content_rc : rc_control_port",
"content_rc : rc_server_key_file",
"content_rc : rc_server_cert_file",
"content_rc : rc_control_key_file",
"content_rc : rc_control_cert_file",
"rc_control_enable : VAR_CONTROL_ENABLE STRING",
"rc_control_port : VAR_CONTROL_PORT STRING",
"rc_control_interface : VAR_CONTROL_INTERFACE STRING",
"rc_server_key_file : VAR_SERVER_KEY_FILE STRING",
"rc_server_cert_file : VAR_SERVER_CERT_FILE STRING",
"rc_control_key_file : VAR_CONTROL_KEY_FILE STRING",
"rc_control_cert_file : VAR_CONTROL_CERT_FILE STRING",
"patternstart : VAR_PATTERN",
"contents_pattern : contents_pattern content_pattern",
"contents_pattern : content_pattern",
"content_pattern : pattern_name",
"content_pattern : zone_config_item",
"zone_config_item : zone_zonefile",
"zone_config_item : zone_allow_notify",
"zone_config_item : zone_request_xfr",
"zone_config_item : zone_notify",
"zone_config_item : zone_notify_retry",
"zone_config_item : zone_provide_xfr",
"zone_config_item : zone_outgoing_interface",
"zone_config_item : zone_allow_axfr_fallback",
"zone_config_item : include_pattern",
"zone_config_item : zone_rrl_whitelist",
"pattern_name : VAR_NAME STRING",
"include_pattern : VAR_INCLUDEPATTERN STRING",
"zonestart : VAR_ZONE",
"contents_zone : contents_zone content_zone",
"contents_zone : content_zone",
"content_zone : zone_name",
"content_zone : zone_config_item",
"zone_name : VAR_NAME STRING",
"zone_zonefile : VAR_ZONEFILE STRING",
"zone_allow_notify : VAR_ALLOW_NOTIFY STRING STRING",
"zone_request_xfr : VAR_REQUEST_XFR zone_request_xfr_data",
"zone_request_xfr_data : STRING STRING",
"zone_request_xfr_data : VAR_AXFR STRING STRING",
"zone_request_xfr_data : VAR_UDP STRING STRING",
"zone_notify : VAR_NOTIFY STRING STRING",
"zone_notify_retry : VAR_NOTIFY_RETRY STRING",
"zone_provide_xfr : VAR_PROVIDE_XFR STRING STRING",
"zone_outgoing_interface : VAR_OUTGOING_INTERFACE STRING",
"zone_allow_axfr_fallback : VAR_ALLOW_AXFR_FALLBACK STRING",
"zone_rrl_whitelist : VAR_RRL_WHITELIST STRING",
"keystart : VAR_KEY",
"contents_key : contents_key content_key",
"contents_key : content_key",
"content_key : key_name",
"content_key : key_algorithm",
"content_key : key_secret",
"key_name : VAR_NAME STRING",
"key_algorithm : VAR_ALGORITHM STRING",
"key_secret : VAR_SECRET STRING",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 851 "./configparser.y"

/* parse helper routines could be here */
#line 572 "configparser.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 8:
#line 81 "./configparser.y"
{ OUTYY(("\nP(server:)\n")); 
		if(cfg_parser->server_settings_seen) {
			yyerror("duplicate server: element.");
		}
		cfg_parser->server_settings_seen = 1;
	}
break;
case 53:
#line 103 "./configparser.y"
{ 
		OUTYY(("P(server_ip_address:%s)\n", yyvsp[0].str)); 
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
			region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 54:
#line 125 "./configparser.y"
{ 
		OUTYY(("P(server_ip_transparent:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->ip_transparent = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 55:
#line 133 "./configparser.y"
{ 
		OUTYY(("P(server_debug_mode:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->debug_mode = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 56:
#line 141 "./configparser.y"
{ 
		OUTYY(("P(server_verbosity:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->verbosity = atoi(yyvsp[0].str);
	}
break;
case 57:
#line 149 "./configparser.y"
{ 
		OUTYY(("P(server_hide_version:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->hide_version = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 58:
#line 157 "./configparser.y"
{ 
		/* for backwards compatibility in config file with NSD3 */
		OUTYY(("P(server_ip4_only:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else if(strcmp(yyvsp[0].str, "yes")==0) {
			cfg_parser->opt->do_ip4 = 1;
			cfg_parser->opt->do_ip6 = 0;
		}
	}
break;
case 59:
#line 169 "./configparser.y"
{ 
		/* for backwards compatibility in config file with NSD3 */
		OUTYY(("P(server_ip6_only:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else if(strcmp(yyvsp[0].str, "yes")==0) {
			cfg_parser->opt->do_ip6 = 1;
			cfg_parser->opt->do_ip4 = 0;
		}
	}
break;
case 60:
#line 181 "./configparser.y"
{ 
		OUTYY(("P(server_do_ip4:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->do_ip4 = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 61:
#line 189 "./configparser.y"
{ 
		OUTYY(("P(server_do_ip6:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->do_ip6 = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 62:
#line 197 "./configparser.y"
{ 
		OUTYY(("P(server_database:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->database = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
		if(cfg_parser->opt->database[0] == 0 &&
			cfg_parser->opt->zonefiles_write == 0)
			cfg_parser->opt->zonefiles_write = ZONEFILES_WRITE_INTERVAL;
	}
break;
case 63:
#line 206 "./configparser.y"
{ 
		OUTYY(("P(server_identity:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->identity = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 64:
#line 212 "./configparser.y"
{ 
		unsigned char* nsid = 0;
		uint16_t nsid_len = 0;

		OUTYY(("P(server_nsid:%s)\n", yyvsp[0].str));

		if (strncasecmp(yyvsp[0].str, "ascii_", 6) == 0) {
			nsid_len = strlen(yyvsp[0].str+6);
			cfg_parser->opt->nsid = region_alloc(cfg_parser->opt->region, nsid_len*2+1);
			hex_ntop((uint8_t*)yyvsp[0].str+6, nsid_len, (char*)cfg_parser->opt->nsid, nsid_len*2+1);
		} else if (strlen(yyvsp[0].str) % 2 != 0) {
			yyerror("the NSID must be a hex string of an even length.");
		} else {
			nsid_len = strlen(yyvsp[0].str) / 2;
			nsid = xalloc(nsid_len);
			if (hex_pton(yyvsp[0].str, nsid, nsid_len) == -1)
				yyerror("hex string cannot be parsed in NSID.");
			else
				cfg_parser->opt->nsid = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
			free(nsid);
		}
	}
break;
case 65:
#line 236 "./configparser.y"
{ 
		OUTYY(("P(server_logfile:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->logfile = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 66:
#line 242 "./configparser.y"
{ 
		OUTYY(("P(server_log_time_ascii:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->opt->log_time_ascii = (strcmp(yyvsp[0].str, "yes")==0);
			log_time_asc = cfg_parser->opt->log_time_ascii;
		}
	}
break;
case 67:
#line 253 "./configparser.y"
{ 
		OUTYY(("P(server_round_robin:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->opt->round_robin = (strcmp(yyvsp[0].str, "yes")==0);
			round_robin = cfg_parser->opt->round_robin;
		}
	}
break;
case 68:
#line 264 "./configparser.y"
{ 
		OUTYY(("P(server_do_health_check:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->opt->do_health_check = (strcmp(yyvsp[0].str, "yes")==0);
		}
	}
break;
case 69:
#line 274 "./configparser.y"
{ 
		OUTYY(("P(server_geo_db_file:%s)\n", yyvsp[0].str)); 
		if(check_file_existing(yyvsp[0].str) == 0)
			yyerror("geo_db file does not exist.");
		else {
			cfg_parser->opt->geo_db_filepath = region_strdup(cfg_parser->opt->region, yyvsp[0].str);;
		}
	}
break;
case 70:
#line 285 "./configparser.y"
{ 
		OUTYY(("P(server_server_count:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) <= 0)
			yyerror("number greater than zero expected");
		else cfg_parser->opt->server_count = atoi(yyvsp[0].str);
	}
break;
case 71:
#line 293 "./configparser.y"
{ 
		OUTYY(("P(server_tcp_count:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) <= 0)
			yyerror("number greater than zero expected");
		else cfg_parser->opt->tcp_count = atoi(yyvsp[0].str);
	}
break;
case 72:
#line 301 "./configparser.y"
{ 
		OUTYY(("P(server_pidfile:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->pidfile = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 73:
#line 307 "./configparser.y"
{ 
		OUTYY(("P(server_port:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->port = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 74:
#line 313 "./configparser.y"
{ 
		OUTYY(("P(server_statistics:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->statistics = atoi(yyvsp[0].str);
	}
break;
case 75:
#line 321 "./configparser.y"
{ 
		OUTYY(("P(server_chroot:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->chroot = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 76:
#line 327 "./configparser.y"
{ 
		OUTYY(("P(server_username:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->username = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 77:
#line 333 "./configparser.y"
{ 
		OUTYY(("P(server_zonesdir:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->zonesdir = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 78:
#line 339 "./configparser.y"
{ 
		OUTYY(("P(server_zonelistfile:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->zonelistfile = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 79:
#line 345 "./configparser.y"
{ 
		OUTYY(("P(server_xfrdir:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->xfrdir = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 80:
#line 351 "./configparser.y"
{ 
		OUTYY(("P(server_difffile:%s)\n", yyvsp[0].str)); 
		/* ignore the value for backwards compatibility in config file*/
	}
break;
case 81:
#line 357 "./configparser.y"
{ 
		OUTYY(("P(server_xfrdfile:%s)\n", yyvsp[0].str)); 
		cfg_parser->opt->xfrdfile = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 82:
#line 363 "./configparser.y"
{ 
		OUTYY(("P(server_xfrd_reload_timeout:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->xfrd_reload_timeout = atoi(yyvsp[0].str);
	}
break;
case 83:
#line 371 "./configparser.y"
{ 
		OUTYY(("P(server_tcp_query_count:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->tcp_query_count = atoi(yyvsp[0].str);
	}
break;
case 84:
#line 379 "./configparser.y"
{ 
		OUTYY(("P(server_tcp_timeout:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->tcp_timeout = atoi(yyvsp[0].str);
	}
break;
case 85:
#line 387 "./configparser.y"
{ 
		OUTYY(("P(server_ipv4_edns_size:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->ipv4_edns_size = atoi(yyvsp[0].str);
	}
break;
case 86:
#line 395 "./configparser.y"
{ 
		OUTYY(("P(server_ipv6_edns_size:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		cfg_parser->opt->ipv6_edns_size = atoi(yyvsp[0].str);
	}
break;
case 87:
#line 403 "./configparser.y"
{ 
		OUTYY(("P(server_rrl_size:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		if(atoi(yyvsp[0].str) <= 0)
			yyerror("number greater than zero expected");
		cfg_parser->opt->rrl_size = atoi(yyvsp[0].str);
#endif
	}
break;
case 88:
#line 413 "./configparser.y"
{ 
		OUTYY(("P(server_rrl_ratelimit:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		cfg_parser->opt->rrl_ratelimit = atoi(yyvsp[0].str);
#endif
	}
break;
case 89:
#line 421 "./configparser.y"
{ 
		OUTYY(("P(server_rrl_slip:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		if(atoi(yyvsp[0].str) < 0)
			yyerror("number equal or greater than zero expected");
		cfg_parser->opt->rrl_slip = atoi(yyvsp[0].str);
#endif
	}
break;
case 90:
#line 431 "./configparser.y"
{
		OUTYY(("P(server_rrl_ipv4_prefix_length:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		if(atoi(yyvsp[0].str) < 0 || atoi(yyvsp[0].str) > 32)
			yyerror("invalid IPv4 prefix length");
		cfg_parser->opt->rrl_ipv4_prefix_length = atoi(yyvsp[0].str);
#endif
	}
break;
case 91:
#line 441 "./configparser.y"
{
		OUTYY(("P(server_rrl_ipv6_prefix_length:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		if(atoi(yyvsp[0].str) < 0 || atoi(yyvsp[0].str) > 64)
			yyerror("invalid IPv6 prefix length");
		cfg_parser->opt->rrl_ipv6_prefix_length = atoi(yyvsp[0].str);
#endif
	}
break;
case 92:
#line 451 "./configparser.y"
{ 
		OUTYY(("P(server_rrl_whitelist_ratelimit:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		cfg_parser->opt->rrl_whitelist_ratelimit = atoi(yyvsp[0].str);
#endif
	}
break;
case 93:
#line 459 "./configparser.y"
{ 
		OUTYY(("P(server_zonefiles_check:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->zonefiles_check = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 94:
#line 467 "./configparser.y"
{ 
		OUTYY(("P(server_zonefiles_write:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		else cfg_parser->opt->zonefiles_write = atoi(yyvsp[0].str);
	}
break;
case 95:
#line 476 "./configparser.y"
{
		OUTYY(("\nP(remote-control:)\n"));
	}
break;
case 105:
#line 487 "./configparser.y"
{
		OUTYY(("P(control_enable:%s)\n", yyvsp[0].str));
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else cfg_parser->opt->control_enable = (strcmp(yyvsp[0].str, "yes")==0);
	}
break;
case 106:
#line 495 "./configparser.y"
{
		OUTYY(("P(control_port:%s)\n", yyvsp[0].str));
		if(atoi(yyvsp[0].str) == 0)
			yyerror("control port number expected");
		else cfg_parser->opt->control_port = atoi(yyvsp[0].str);
	}
break;
case 107:
#line 503 "./configparser.y"
{
		ip_address_option_t* o = (ip_address_option_t*)region_alloc(
			cfg_parser->opt->region, sizeof(ip_address_option_t));
		OUTYY(("P(control_interface:%s)\n", yyvsp[0].str));
		o->next = cfg_parser->opt->control_interface;
		cfg_parser->opt->control_interface = o;
		o->address = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 108:
#line 513 "./configparser.y"
{
	OUTYY(("P(rc_server_key_file:%s)\n", yyvsp[0].str));
	cfg_parser->opt->server_key_file = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 109:
#line 519 "./configparser.y"
{
	OUTYY(("P(rc_server_cert_file:%s)\n", yyvsp[0].str));
	cfg_parser->opt->server_cert_file = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 110:
#line 525 "./configparser.y"
{
	OUTYY(("P(rc_control_key_file:%s)\n", yyvsp[0].str));
	cfg_parser->opt->control_key_file = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 111:
#line 531 "./configparser.y"
{
	OUTYY(("P(rc_control_cert_file:%s)\n", yyvsp[0].str));
	cfg_parser->opt->control_cert_file = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 112:
#line 539 "./configparser.y"
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
case 127:
#line 579 "./configparser.y"
{ 
		OUTYY(("P(pattern_name:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		if(strchr(yyvsp[0].str, ' '))
			c_error_msg("space is not allowed in pattern name: "
				"'%s'", yyvsp[0].str);
		cfg_parser->current_pattern->pname = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 128:
#line 591 "./configparser.y"
{
		OUTYY(("P(include-pattern:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		config_apply_pattern(yyvsp[0].str);
	}
break;
case 129:
#line 602 "./configparser.y"
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
case 134:
#line 641 "./configparser.y"
{ 
		char* s;
		OUTYY(("P(zone_name:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_zone);
		assert(cfg_parser->current_pattern);
#endif
		cfg_parser->current_zone->name = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
		s = (char*)region_alloc(cfg_parser->opt->region,
			strlen(yyvsp[0].str)+strlen(PATTERN_IMPLICIT_MARKER)+1);
		memmove(s, PATTERN_IMPLICIT_MARKER,
			strlen(PATTERN_IMPLICIT_MARKER));
		memmove(s+strlen(PATTERN_IMPLICIT_MARKER), yyvsp[0].str, strlen(yyvsp[0].str)+1);
		if(pattern_options_find(cfg_parser->opt, s))
			c_error_msg("zone %s cannot be created because "
				"implicit pattern %s already exists", yyvsp[0].str, s);
		cfg_parser->current_pattern->pname = s;
	}
break;
case 135:
#line 661 "./configparser.y"
{ 
		OUTYY(("P(zonefile:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_pattern);
#endif
		cfg_parser->current_pattern->zonefile = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
	}
break;
case 136:
#line 670 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		OUTYY(("P(allow_notify:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(cfg_parser->current_allow_notify)
			cfg_parser->current_allow_notify->next = acl;
		else
			cfg_parser->current_pattern->allow_notify = acl;
		cfg_parser->current_allow_notify = acl;
	}
break;
case 137:
#line 681 "./configparser.y"
{
	}
break;
case 138:
#line 685 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		OUTYY(("P(request_xfr:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
break;
case 139:
#line 697 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		acl->use_axfr_only = 1;
		OUTYY(("P(request_xfr:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
break;
case 140:
#line 710 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		acl->allow_udp = 1;
		OUTYY(("P(request_xfr:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(acl->blocked) c_error("blocked address used for request-xfr");
		if(acl->rangetype!=acl_range_single) c_error("address range used for request-xfr");
		if(cfg_parser->current_request_xfr)
			cfg_parser->current_request_xfr->next = acl;
		else
			cfg_parser->current_pattern->request_xfr = acl;
		cfg_parser->current_request_xfr = acl;
	}
break;
case 141:
#line 724 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		OUTYY(("P(notify:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(acl->blocked) c_error("blocked address used for notify");
		if(acl->rangetype!=acl_range_single) c_error("address range used for notify");
		if(cfg_parser->current_notify)
			cfg_parser->current_notify->next = acl;
		else
			cfg_parser->current_pattern->notify = acl;
		cfg_parser->current_notify = acl;
	}
break;
case 142:
#line 737 "./configparser.y"
{ 
		OUTYY(("P(notify_retry:%s)\n", yyvsp[0].str)); 
		if(atoi(yyvsp[0].str) == 0 && strcmp(yyvsp[0].str, "0") != 0)
			yyerror("number expected");
		else {
			cfg_parser->current_pattern->notify_retry = atoi(yyvsp[0].str);
			cfg_parser->current_pattern->notify_retry_is_default=0;
		}
	}
break;
case 143:
#line 748 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[-1].str, yyvsp[0].str);
		OUTYY(("P(provide_xfr:%s %s)\n", yyvsp[-1].str, yyvsp[0].str)); 
		if(cfg_parser->current_provide_xfr)
			cfg_parser->current_provide_xfr->next = acl;
		else
			cfg_parser->current_pattern->provide_xfr = acl;
		cfg_parser->current_provide_xfr = acl;
	}
break;
case 144:
#line 759 "./configparser.y"
{ 
		acl_options_t* acl = parse_acl_info(cfg_parser->opt->region, yyvsp[0].str, "NOKEY");
		OUTYY(("P(outgoing_interface:%s)\n", yyvsp[0].str)); 
		if(acl->rangetype!=acl_range_single) c_error("address range used for outgoing interface");
		if(cfg_parser->current_outgoing_interface)
			cfg_parser->current_outgoing_interface->next = acl;
		else
			cfg_parser->current_pattern->outgoing_interface = acl;
		cfg_parser->current_outgoing_interface = acl;
	}
break;
case 145:
#line 771 "./configparser.y"
{ 
		OUTYY(("P(allow_axfr_fallback:%s)\n", yyvsp[0].str)); 
		if(strcmp(yyvsp[0].str, "yes") != 0 && strcmp(yyvsp[0].str, "no") != 0)
			yyerror("expected yes or no.");
		else {
			cfg_parser->current_pattern->allow_axfr_fallback = (strcmp(yyvsp[0].str, "yes")==0);
			cfg_parser->current_pattern->allow_axfr_fallback_is_default = 0;
		}
	}
break;
case 146:
#line 782 "./configparser.y"
{ 
		OUTYY(("P(zone_rrl_whitelist:%s)\n", yyvsp[0].str)); 
#ifdef RATELIMIT
		cfg_parser->current_pattern->rrl_whitelist |= rrlstr2type(yyvsp[0].str);
#endif
	}
break;
case 147:
#line 792 "./configparser.y"
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
case 153:
#line 806 "./configparser.y"
{ 
		const dname_type* d;
		OUTYY(("P(key_name:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->name = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
		d = dname_parse(cfg_parser->opt->region, yyvsp[0].str);
		if(!d)	c_error_msg("Failed to parse tsig key name %s", yyvsp[0].str);
		else	region_recycle(cfg_parser->opt->region, (void*)d,
				dname_total_size(d));
	}
break;
case 154:
#line 820 "./configparser.y"
{ 
		OUTYY(("P(key_algorithm:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->algorithm = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
		if(tsig_get_algorithm_by_name(yyvsp[0].str) == NULL)
			c_error_msg("Bad tsig algorithm %s", yyvsp[0].str);
	}
break;
case 155:
#line 831 "./configparser.y"
{ 
		uint8_t data[16384];
		int size;
		OUTYY(("key_secret:%s)\n", yyvsp[0].str)); 
#ifndef NDEBUG
		assert(cfg_parser->current_key);
#endif
		cfg_parser->current_key->secret = region_strdup(cfg_parser->opt->region, yyvsp[0].str);
		size = b64_pton(yyvsp[0].str, data, sizeof(data));
		if(size == -1) {
			c_error_msg("Cannot base64 decode tsig secret %s",
				cfg_parser->current_key->name?
				cfg_parser->current_key->name:"");
		} else if(size != 0) {
			memset(data, 0xdd, size); /* wipe secret */
		}
	}
break;
#line 1558 "configparser.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
