/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "mon_parse.y"

/* -*- C -*-
 *
 * mon_parse.y - Parser for the VICE built-in monitor.
 *
 * Written by
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Andreas Boose <viceteam@t-online.de>
 *  Thomas Giesel <skoe@directbox.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#ifndef MINIXVMD
#ifdef __GNUC__
#undef alloca
#define        alloca(n)       __builtin_alloca (n)
#else
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else  /* Not HAVE_ALLOCA_H.  */
#if !defined(_AIX) && !defined(WINCE)
#ifndef _MSC_VER
extern char *alloca();
#else
#define alloca(n)   _alloca(n)
#endif  /* MSVC */
#endif /* Not AIX and not WINCE.  */
#endif /* HAVE_ALLOCA_H.  */
#endif /* GCC.  */
#endif /* MINIXVMD */

/* SunOS 4.x specific stuff */
#if defined(sun) || defined(__sun)
#  if !defined(__SVR4) && !defined(__svr4__)
#    ifdef __sparc__
#      define YYFREE
#    endif
#  endif
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asm.h"
#include "console.h"
#include "lib.h"
#include "machine.h"
#include "mon_breakpoint.h"
#include "mon_command.h"
#include "mon_disassemble.h"
#include "mon_drive.h"
#include "mon_file.h"
#include "mon_memory.h"
#include "mon_util.h"
#include "montypes.h"
#include "types.h"
#include "uimon.h"


#define join_ints(x,y) (LO16_TO_HI16(x)|y)
#define separate_int1(x) (HI16_TO_LO16(x))
#define separate_int2(x) (LO16(x))

static int yyerror(char *s);
static int temp;
static int resolve_datatype(unsigned guess_type, const char *num);
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2], 
                         const char *num);
static void mon_quit(void);

#ifdef __IBMC__
static void __yy_memcpy (char *to, char *from, int count);
#endif

/* Defined in the lexer */
extern int new_cmd, opt_asm;
extern void free_buffer(void);
extern void make_buffer(char *str);
extern int yylex(void);
extern int cur_len, last_len;

#define ERR_ILLEGAL_INPUT 1     /* Generic error as returned by yacc.  */
#define ERR_RANGE_BAD_START 2
#define ERR_RANGE_BAD_END 3
#define ERR_BAD_CMD 4
#define ERR_EXPECT_CHECKNUM 5
#define ERR_EXPECT_END_CMD 6
#define ERR_MISSING_CLOSE_PAREN 7
#define ERR_INCOMPLETE_COMPARE_OP 8
#define ERR_EXPECT_FILENAME 9
#define ERR_ADDR_TOO_BIG 10
#define ERR_IMM_TOO_BIG 11
#define ERR_EXPECT_STRING 12
#define ERR_UNDEFINED_LABEL 13
#define ERR_EXPECT_DEVICE_NUM 14
#define ERR_EXPECT_ADDRESS 15

#define BAD_ADDR (new_addr(e_invalid_space, 0))
#define CHECK_ADDR(x) ((x) == addr_mask(x))

#define YYDEBUG 1



/* Line 189 of yacc.c  */
#line 199 "mon_parse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     H_NUMBER = 258,
     D_NUMBER = 259,
     O_NUMBER = 260,
     B_NUMBER = 261,
     CONVERT_OP = 262,
     B_DATA = 263,
     H_RANGE_GUESS = 264,
     D_NUMBER_GUESS = 265,
     O_NUMBER_GUESS = 266,
     B_NUMBER_GUESS = 267,
     BAD_CMD = 268,
     MEM_OP = 269,
     IF = 270,
     MEM_COMP = 271,
     MEM_DISK8 = 272,
     MEM_DISK9 = 273,
     MEM_DISK10 = 274,
     MEM_DISK11 = 275,
     EQUALS = 276,
     TRAIL = 277,
     CMD_SEP = 278,
     LABEL_ASGN_COMMENT = 279,
     CMD_SIDEFX = 280,
     CMD_RETURN = 281,
     CMD_BLOCK_READ = 282,
     CMD_BLOCK_WRITE = 283,
     CMD_UP = 284,
     CMD_DOWN = 285,
     CMD_LOAD = 286,
     CMD_SAVE = 287,
     CMD_VERIFY = 288,
     CMD_IGNORE = 289,
     CMD_HUNT = 290,
     CMD_FILL = 291,
     CMD_MOVE = 292,
     CMD_GOTO = 293,
     CMD_REGISTERS = 294,
     CMD_READSPACE = 295,
     CMD_WRITESPACE = 296,
     CMD_RADIX = 297,
     CMD_MEM_DISPLAY = 298,
     CMD_BREAK = 299,
     CMD_TRACE = 300,
     CMD_IO = 301,
     CMD_BRMON = 302,
     CMD_COMPARE = 303,
     CMD_DUMP = 304,
     CMD_UNDUMP = 305,
     CMD_EXIT = 306,
     CMD_DELETE = 307,
     CMD_CONDITION = 308,
     CMD_COMMAND = 309,
     CMD_ASSEMBLE = 310,
     CMD_DISASSEMBLE = 311,
     CMD_NEXT = 312,
     CMD_STEP = 313,
     CMD_PRINT = 314,
     CMD_DEVICE = 315,
     CMD_HELP = 316,
     CMD_WATCH = 317,
     CMD_DISK = 318,
     CMD_SYSTEM = 319,
     CMD_QUIT = 320,
     CMD_CHDIR = 321,
     CMD_BANK = 322,
     CMD_LOAD_LABELS = 323,
     CMD_SAVE_LABELS = 324,
     CMD_ADD_LABEL = 325,
     CMD_DEL_LABEL = 326,
     CMD_SHOW_LABELS = 327,
     CMD_RECORD = 328,
     CMD_MON_STOP = 329,
     CMD_PLAYBACK = 330,
     CMD_CHAR_DISPLAY = 331,
     CMD_SPRITE_DISPLAY = 332,
     CMD_TEXT_DISPLAY = 333,
     CMD_SCREENCODE_DISPLAY = 334,
     CMD_ENTER_DATA = 335,
     CMD_ENTER_BIN_DATA = 336,
     CMD_KEYBUF = 337,
     CMD_BLOAD = 338,
     CMD_BSAVE = 339,
     CMD_SCREEN = 340,
     CMD_UNTIL = 341,
     CMD_CPU = 342,
     CMD_YYDEBUG = 343,
     CMD_BACKTRACE = 344,
     CMD_SCREENSHOT = 345,
     CMD_PWD = 346,
     CMD_DIR = 347,
     CMD_RESOURCE_GET = 348,
     CMD_RESOURCE_SET = 349,
     CMD_ATTACH = 350,
     CMD_DETACH = 351,
     CMD_MON_RESET = 352,
     CMD_TAPECTRL = 353,
     CMD_CARTFREEZE = 354,
     CMD_CPUHISTORY = 355,
     CMD_MEMMAPZAP = 356,
     CMD_MEMMAPSHOW = 357,
     CMD_MEMMAPSAVE = 358,
     CMD_COMMENT = 359,
     CMD_LIST = 360,
     CMD_EXPORT = 361,
     CMD_AUTOSTART = 362,
     CMD_AUTOLOAD = 363,
     CMD_LABEL_ASGN = 364,
     L_PAREN = 365,
     R_PAREN = 366,
     ARG_IMMEDIATE = 367,
     REG_A = 368,
     REG_S = 369,
     REG_X = 370,
     REG_Y = 371,
     REG_Z = 372,
     COMMA = 373,
     INST_SEP = 374,
     REG_B = 375,
     REG_C = 376,
     REG_D = 377,
     REG_E = 378,
     REG_H = 379,
     REG_L = 380,
     REG_AF = 381,
     REG_BC = 382,
     REG_DE = 383,
     REG_HL = 384,
     REG_IX = 385,
     REG_IY = 386,
     REG_SP = 387,
     REG_IXH = 388,
     REG_IXL = 389,
     REG_IYH = 390,
     REG_IYL = 391,
     STRING = 392,
     FILENAME = 393,
     R_O_L = 394,
     OPCODE = 395,
     LABEL = 396,
     BANKNAME = 397,
     CPUTYPE = 398,
     MON_REGISTER = 399,
     COMPARE_OP = 400,
     RADIX_TYPE = 401,
     INPUT_SPEC = 402,
     CMD_CHECKPT_ON = 403,
     CMD_CHECKPT_OFF = 404,
     TOGGLE = 405,
     MASK = 406
   };
#endif
/* Tokens.  */
#define H_NUMBER 258
#define D_NUMBER 259
#define O_NUMBER 260
#define B_NUMBER 261
#define CONVERT_OP 262
#define B_DATA 263
#define H_RANGE_GUESS 264
#define D_NUMBER_GUESS 265
#define O_NUMBER_GUESS 266
#define B_NUMBER_GUESS 267
#define BAD_CMD 268
#define MEM_OP 269
#define IF 270
#define MEM_COMP 271
#define MEM_DISK8 272
#define MEM_DISK9 273
#define MEM_DISK10 274
#define MEM_DISK11 275
#define EQUALS 276
#define TRAIL 277
#define CMD_SEP 278
#define LABEL_ASGN_COMMENT 279
#define CMD_SIDEFX 280
#define CMD_RETURN 281
#define CMD_BLOCK_READ 282
#define CMD_BLOCK_WRITE 283
#define CMD_UP 284
#define CMD_DOWN 285
#define CMD_LOAD 286
#define CMD_SAVE 287
#define CMD_VERIFY 288
#define CMD_IGNORE 289
#define CMD_HUNT 290
#define CMD_FILL 291
#define CMD_MOVE 292
#define CMD_GOTO 293
#define CMD_REGISTERS 294
#define CMD_READSPACE 295
#define CMD_WRITESPACE 296
#define CMD_RADIX 297
#define CMD_MEM_DISPLAY 298
#define CMD_BREAK 299
#define CMD_TRACE 300
#define CMD_IO 301
#define CMD_BRMON 302
#define CMD_COMPARE 303
#define CMD_DUMP 304
#define CMD_UNDUMP 305
#define CMD_EXIT 306
#define CMD_DELETE 307
#define CMD_CONDITION 308
#define CMD_COMMAND 309
#define CMD_ASSEMBLE 310
#define CMD_DISASSEMBLE 311
#define CMD_NEXT 312
#define CMD_STEP 313
#define CMD_PRINT 314
#define CMD_DEVICE 315
#define CMD_HELP 316
#define CMD_WATCH 317
#define CMD_DISK 318
#define CMD_SYSTEM 319
#define CMD_QUIT 320
#define CMD_CHDIR 321
#define CMD_BANK 322
#define CMD_LOAD_LABELS 323
#define CMD_SAVE_LABELS 324
#define CMD_ADD_LABEL 325
#define CMD_DEL_LABEL 326
#define CMD_SHOW_LABELS 327
#define CMD_RECORD 328
#define CMD_MON_STOP 329
#define CMD_PLAYBACK 330
#define CMD_CHAR_DISPLAY 331
#define CMD_SPRITE_DISPLAY 332
#define CMD_TEXT_DISPLAY 333
#define CMD_SCREENCODE_DISPLAY 334
#define CMD_ENTER_DATA 335
#define CMD_ENTER_BIN_DATA 336
#define CMD_KEYBUF 337
#define CMD_BLOAD 338
#define CMD_BSAVE 339
#define CMD_SCREEN 340
#define CMD_UNTIL 341
#define CMD_CPU 342
#define CMD_YYDEBUG 343
#define CMD_BACKTRACE 344
#define CMD_SCREENSHOT 345
#define CMD_PWD 346
#define CMD_DIR 347
#define CMD_RESOURCE_GET 348
#define CMD_RESOURCE_SET 349
#define CMD_ATTACH 350
#define CMD_DETACH 351
#define CMD_MON_RESET 352
#define CMD_TAPECTRL 353
#define CMD_CARTFREEZE 354
#define CMD_CPUHISTORY 355
#define CMD_MEMMAPZAP 356
#define CMD_MEMMAPSHOW 357
#define CMD_MEMMAPSAVE 358
#define CMD_COMMENT 359
#define CMD_LIST 360
#define CMD_EXPORT 361
#define CMD_AUTOSTART 362
#define CMD_AUTOLOAD 363
#define CMD_LABEL_ASGN 364
#define L_PAREN 365
#define R_PAREN 366
#define ARG_IMMEDIATE 367
#define REG_A 368
#define REG_S 369
#define REG_X 370
#define REG_Y 371
#define REG_Z 372
#define COMMA 373
#define INST_SEP 374
#define REG_B 375
#define REG_C 376
#define REG_D 377
#define REG_E 378
#define REG_H 379
#define REG_L 380
#define REG_AF 381
#define REG_BC 382
#define REG_DE 383
#define REG_HL 384
#define REG_IX 385
#define REG_IY 386
#define REG_SP 387
#define REG_IXH 388
#define REG_IXL 389
#define REG_IYH 390
#define REG_IYL 391
#define STRING 392
#define FILENAME 393
#define R_O_L 394
#define OPCODE 395
#define LABEL 396
#define BANKNAME 397
#define CPUTYPE 398
#define MON_REGISTER 399
#define COMPARE_OP 400
#define RADIX_TYPE 401
#define INPUT_SPEC 402
#define CMD_CHECKPT_ON 403
#define CMD_CHECKPT_OFF 404
#define TOGGLE 405
#define MASK 406




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 127 "mon_parse.y"

    MON_ADDR a;
    MON_ADDR range[2];
    int i;
    REG_ID reg;
    CONDITIONAL cond_op;
    cond_node_t *cond_node;
    RADIXTYPE rt;
    ACTION action;
    char *str;



/* Line 214 of yacc.c  */
#line 551 "mon_parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 563 "mon_parse.c"

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  298
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1734

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  158
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  282
/* YYNRULES -- Number of states.  */
#define YYNSTATES  569

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   406

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     156,   157,   154,   152,     2,   153,     2,   155,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    50,    54,    58,    64,    68,    71,
      75,    78,    82,    85,    90,    93,    97,   101,   104,   109,
     112,   117,   120,   125,   128,   133,   136,   138,   141,   145,
     149,   155,   159,   165,   169,   175,   179,   185,   189,   192,
     197,   203,   204,   210,   214,   218,   221,   227,   233,   239,
     245,   251,   255,   258,   262,   265,   269,   272,   276,   279,
     283,   286,   289,   292,   297,   303,   309,   313,   319,   324,
     331,   334,   338,   344,   349,   356,   359,   363,   369,   374,
     381,   384,   388,   391,   395,   399,   403,   409,   413,   416,
     422,   428,   433,   437,   440,   444,   447,   451,   454,   457,
     460,   464,   468,   471,   475,   479,   483,   487,   491,   494,
     498,   501,   505,   511,   515,   520,   523,   528,   533,   536,
     540,   546,   552,   558,   562,   567,   573,   578,   584,   589,
     595,   601,   604,   608,   613,   617,   621,   627,   631,   637,
     641,   644,   648,   653,   656,   659,   661,   663,   664,   666,
     668,   670,   672,   674,   675,   677,   680,   684,   686,   690,
     692,   694,   696,   698,   702,   704,   708,   711,   712,   714,
     718,   720,   722,   723,   725,   727,   729,   731,   733,   735,
     737,   741,   745,   749,   753,   757,   761,   763,   767,   771,
     775,   779,   781,   783,   785,   789,   791,   793,   795,   798,
     800,   802,   804,   806,   808,   810,   812,   814,   816,   818,
     820,   822,   824,   826,   828,   830,   832,   834,   838,   842,
     845,   848,   850,   852,   855,   857,   861,   865,   872,   877,
     881,   887,   893,   899,   907,   911,   915,   919,   923,   927,
     931,   937,   943,   949,   955,   956,   958,   960,   962,   964,
     966,   968,   970,   972,   974,   976,   978,   980,   982,   984,
     986,   988,   990
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     159,     0,    -1,   160,    -1,   206,    22,    -1,    22,    -1,
     162,    -1,   160,   162,    -1,    23,    -1,    22,    -1,     1,
      -1,   163,    -1,   165,    -1,   168,    -1,   166,    -1,   169,
      -1,   170,    -1,   171,    -1,   172,    -1,   173,    -1,   174,
      -1,   175,    -1,   176,    -1,    13,    -1,    67,   161,    -1,
      67,   191,   161,    -1,    67,   142,   161,    -1,    67,   191,
     190,   142,   161,    -1,    38,   189,   161,    -1,    46,   161,
      -1,    46,   189,   161,    -1,    87,   161,    -1,    87,   143,
     161,    -1,   100,   161,    -1,   100,   190,   194,   161,    -1,
      26,   161,    -1,    49,   179,   161,    -1,    50,   179,   161,
      -1,    58,   161,    -1,    58,   190,   194,   161,    -1,    57,
     161,    -1,    57,   190,   194,   161,    -1,    29,   161,    -1,
      29,   190,   194,   161,    -1,    30,   161,    -1,    30,   190,
     194,   161,    -1,    85,   161,    -1,   164,    -1,    39,   161,
      -1,    39,   191,   161,    -1,    39,   183,   161,    -1,    68,
     191,   190,   179,   161,    -1,    68,   179,   161,    -1,    69,
     191,   190,   179,   161,    -1,    69,   179,   161,    -1,    70,
     189,   190,   141,   161,    -1,    71,   141,   161,    -1,    71,
     191,   190,   141,   161,    -1,    72,   191,   161,    -1,    72,
     161,    -1,   109,    21,   189,   161,    -1,   109,    21,   189,
      24,   161,    -1,    -1,    55,   189,   167,   207,   161,    -1,
      55,   189,   161,    -1,    56,   186,   161,    -1,    56,   161,
      -1,    37,   187,   190,   189,   161,    -1,    48,   187,   190,
     189,   161,    -1,    36,   187,   190,   197,   161,    -1,    35,
     187,   190,   199,   161,    -1,    43,   146,   190,   186,   161,
      -1,    43,   186,   161,    -1,    43,   161,    -1,    76,   186,
     161,    -1,    76,   161,    -1,    77,   186,   161,    -1,    77,
     161,    -1,    78,   186,   161,    -1,    78,   161,    -1,    79,
     186,   161,    -1,    79,   161,    -1,   101,   161,    -1,   102,
     161,    -1,   102,   190,   194,   161,    -1,   102,   190,   194,
     186,   161,    -1,   103,   179,   190,   194,   161,    -1,    44,
     186,   161,    -1,    44,   186,    15,   195,   161,    -1,    44,
     181,   186,   161,    -1,    44,   181,   186,    15,   195,   161,
      -1,    44,   161,    -1,    62,   186,   161,    -1,    62,   186,
      15,   195,   161,    -1,    62,   181,   186,   161,    -1,    62,
     181,   186,    15,   195,   161,    -1,    62,   161,    -1,    45,
     186,   161,    -1,    45,   186,    15,   195,   161,    -1,    45,
     181,   186,   161,    -1,    45,   181,   186,    15,   195,   161,
      -1,    45,   161,    -1,    86,   186,   161,    -1,    86,   161,
      -1,   148,   185,   161,    -1,   149,   185,   161,    -1,    34,
     185,   161,    -1,    34,   185,   190,   194,   161,    -1,    52,
     185,   161,    -1,    52,   161,    -1,    53,   185,    15,   195,
     161,    -1,    54,   185,   190,   137,   161,    -1,    54,   185,
       1,   161,    -1,    25,   150,   161,    -1,    25,   161,    -1,
      42,   146,   161,    -1,    42,   161,    -1,    60,   191,   161,
      -1,   106,   161,    -1,    65,   161,    -1,    51,   161,    -1,
      63,   177,   161,    -1,    59,   194,   161,    -1,    61,   161,
      -1,    61,   177,   161,    -1,    64,   177,   161,    -1,     7,
     194,   161,    -1,    66,   177,   161,    -1,    82,   137,   161,
      -1,    89,   161,    -1,    92,   178,   161,    -1,    91,   161,
      -1,    90,   179,   161,    -1,    90,   179,   190,   194,   161,
      -1,    93,   137,   161,    -1,    94,   137,   137,   161,    -1,
      97,   161,    -1,    97,   190,   194,   161,    -1,    98,   190,
     194,   161,    -1,    99,   161,    -1,   104,   178,   161,    -1,
      31,   179,   180,   188,   161,    -1,    83,   179,   180,   188,
     161,    -1,    32,   179,   180,   187,   161,    -1,    32,   179,
       1,    -1,    32,   179,   180,     1,    -1,    84,   179,   180,
     187,   161,    -1,    84,   179,   180,     1,    -1,    33,   179,
     180,   189,   161,    -1,    33,   179,   180,     1,    -1,    27,
     194,   194,   188,   161,    -1,    28,   194,   194,   189,   161,
      -1,   105,   161,    -1,   105,   180,   161,    -1,    95,   179,
     194,   161,    -1,    96,   194,   161,    -1,   107,   179,   161,
      -1,   107,   179,   190,   204,   161,    -1,   108,   179,   161,
      -1,   108,   179,   190,   204,   161,    -1,    73,   179,   161,
      -1,    74,   161,    -1,    75,   179,   161,    -1,    80,   189,
     197,   161,    -1,    81,   161,    -1,    88,   161,    -1,   139,
      -1,   139,    -1,    -1,   138,    -1,     1,    -1,   194,    -1,
       1,    -1,    14,    -1,    -1,   144,    -1,   191,   144,    -1,
     183,   118,   184,    -1,   184,    -1,   182,    21,   204,    -1,
     202,    -1,     1,    -1,   187,    -1,   189,    -1,   189,   190,
     189,    -1,     9,    -1,   191,   190,     9,    -1,   190,   189,
      -1,    -1,   192,    -1,   191,   190,   192,    -1,   141,    -1,
     118,    -1,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,   193,    -1,   204,    -1,   194,   152,   194,
      -1,   194,   153,   194,    -1,   194,   154,   194,    -1,   194,
     155,   194,    -1,   156,   194,   157,    -1,   156,   194,     1,
      -1,   201,    -1,   195,   145,   195,    -1,   195,   145,     1,
      -1,   110,   195,   111,    -1,   110,   195,     1,    -1,   196,
      -1,   182,    -1,   204,    -1,   197,   190,   198,    -1,   198,
      -1,   204,    -1,   137,    -1,   199,   200,    -1,   200,    -1,
     204,    -1,   151,    -1,   137,    -1,   204,    -1,   182,    -1,
       4,    -1,    12,    -1,    11,    -1,    10,    -1,    12,    -1,
      11,    -1,    10,    -1,     3,    -1,     4,    -1,     5,    -1,
       6,    -1,   203,    -1,   205,   119,   206,    -1,   206,   119,
     206,    -1,   206,   119,    -1,   140,   208,    -1,   206,    -1,
     205,    -1,   112,   204,    -1,   204,    -1,   204,   118,   115,
      -1,   204,   118,   116,    -1,   112,   204,   118,   204,   118,
     204,    -1,   112,   204,   118,   204,    -1,   110,   204,   111,
      -1,   110,   204,   118,   115,   111,    -1,   110,   204,   111,
     118,   116,    -1,   110,   204,   111,   118,   117,    -1,   110,
     204,   118,   114,   111,   118,   116,    -1,   110,   127,   111,
      -1,   110,   128,   111,    -1,   110,   129,   111,    -1,   110,
     130,   111,    -1,   110,   131,   111,    -1,   110,   132,   111,
      -1,   110,   204,   111,   118,   113,    -1,   110,   204,   111,
     118,   129,    -1,   110,   204,   111,   118,   130,    -1,   110,
     204,   111,   118,   131,    -1,    -1,   113,    -1,   120,    -1,
     121,    -1,   122,    -1,   123,    -1,   124,    -1,   133,    -1,
     135,    -1,   125,    -1,   134,    -1,   136,    -1,   126,    -1,
     127,    -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,
     132,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   186,   186,   187,   188,   191,   192,   195,   196,   197,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   215,   217,   219,   221,   223,   225,   227,
     229,   231,   233,   235,   237,   239,   241,   243,   245,   247,
     249,   251,   253,   255,   257,   259,   261,   264,   266,   268,
     271,   276,   281,   283,   285,   287,   289,   291,   293,   295,
     299,   306,   305,   308,   310,   312,   316,   318,   320,   322,
     324,   326,   328,   330,   332,   334,   336,   338,   340,   342,
     344,   346,   348,   350,   352,   354,   358,   362,   367,   371,
     376,   379,   383,   388,   392,   397,   400,   404,   409,   413,
     418,   421,   425,   430,   432,   434,   436,   438,   440,   442,
     444,   446,   450,   452,   457,   459,   477,   479,   481,   483,
     487,   489,   491,   493,   495,   497,   499,   501,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   523,   525,
     529,   531,   533,   535,   537,   539,   541,   543,   545,   547,
     549,   551,   553,   555,   557,   559,   561,   563,   565,   569,
     571,   573,   577,   579,   583,   587,   590,   591,   594,   595,
     598,   599,   602,   603,   606,   607,   610,   611,   614,   618,
     619,   622,   623,   626,   627,   629,   633,   634,   637,   642,
     647,   657,   658,   661,   662,   663,   664,   665,   668,   670,
     672,   673,   674,   675,   676,   677,   678,   681,   686,   688,
     690,   692,   696,   702,   710,   711,   714,   715,   718,   719,
     722,   723,   724,   727,   728,   731,   732,   733,   734,   737,
     738,   739,   742,   743,   744,   745,   746,   749,   750,   751,
     754,   764,   765,   768,   777,   782,   787,   792,   795,   798,
     803,   808,   810,   812,   814,   815,   816,   817,   818,   819,
     820,   822,   824,   826,   828,   829,   830,   831,   832,   833,
     834,   835,   836,   837,   838,   839,   840,   841,   842,   843,
     844,   845,   846
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "H_NUMBER", "D_NUMBER", "O_NUMBER",
  "B_NUMBER", "CONVERT_OP", "B_DATA", "H_RANGE_GUESS", "D_NUMBER_GUESS",
  "O_NUMBER_GUESS", "B_NUMBER_GUESS", "BAD_CMD", "MEM_OP", "IF",
  "MEM_COMP", "MEM_DISK8", "MEM_DISK9", "MEM_DISK10", "MEM_DISK11",
  "EQUALS", "TRAIL", "CMD_SEP", "LABEL_ASGN_COMMENT", "CMD_SIDEFX",
  "CMD_RETURN", "CMD_BLOCK_READ", "CMD_BLOCK_WRITE", "CMD_UP", "CMD_DOWN",
  "CMD_LOAD", "CMD_SAVE", "CMD_VERIFY", "CMD_IGNORE", "CMD_HUNT",
  "CMD_FILL", "CMD_MOVE", "CMD_GOTO", "CMD_REGISTERS", "CMD_READSPACE",
  "CMD_WRITESPACE", "CMD_RADIX", "CMD_MEM_DISPLAY", "CMD_BREAK",
  "CMD_TRACE", "CMD_IO", "CMD_BRMON", "CMD_COMPARE", "CMD_DUMP",
  "CMD_UNDUMP", "CMD_EXIT", "CMD_DELETE", "CMD_CONDITION", "CMD_COMMAND",
  "CMD_ASSEMBLE", "CMD_DISASSEMBLE", "CMD_NEXT", "CMD_STEP", "CMD_PRINT",
  "CMD_DEVICE", "CMD_HELP", "CMD_WATCH", "CMD_DISK", "CMD_SYSTEM",
  "CMD_QUIT", "CMD_CHDIR", "CMD_BANK", "CMD_LOAD_LABELS",
  "CMD_SAVE_LABELS", "CMD_ADD_LABEL", "CMD_DEL_LABEL", "CMD_SHOW_LABELS",
  "CMD_RECORD", "CMD_MON_STOP", "CMD_PLAYBACK", "CMD_CHAR_DISPLAY",
  "CMD_SPRITE_DISPLAY", "CMD_TEXT_DISPLAY", "CMD_SCREENCODE_DISPLAY",
  "CMD_ENTER_DATA", "CMD_ENTER_BIN_DATA", "CMD_KEYBUF", "CMD_BLOAD",
  "CMD_BSAVE", "CMD_SCREEN", "CMD_UNTIL", "CMD_CPU", "CMD_YYDEBUG",
  "CMD_BACKTRACE", "CMD_SCREENSHOT", "CMD_PWD", "CMD_DIR",
  "CMD_RESOURCE_GET", "CMD_RESOURCE_SET", "CMD_ATTACH", "CMD_DETACH",
  "CMD_MON_RESET", "CMD_TAPECTRL", "CMD_CARTFREEZE", "CMD_CPUHISTORY",
  "CMD_MEMMAPZAP", "CMD_MEMMAPSHOW", "CMD_MEMMAPSAVE", "CMD_COMMENT",
  "CMD_LIST", "CMD_EXPORT", "CMD_AUTOSTART", "CMD_AUTOLOAD",
  "CMD_LABEL_ASGN", "L_PAREN", "R_PAREN", "ARG_IMMEDIATE", "REG_A",
  "REG_S", "REG_X", "REG_Y", "REG_Z", "COMMA", "INST_SEP", "REG_B",
  "REG_C", "REG_D", "REG_E", "REG_H", "REG_L", "REG_AF", "REG_BC",
  "REG_DE", "REG_HL", "REG_IX", "REG_IY", "REG_SP", "REG_IXH", "REG_IXL",
  "REG_IYH", "REG_IYL", "STRING", "FILENAME", "R_O_L", "OPCODE", "LABEL",
  "BANKNAME", "CPUTYPE", "MON_REGISTER", "COMPARE_OP", "RADIX_TYPE",
  "INPUT_SPEC", "CMD_CHECKPT_ON", "CMD_CHECKPT_OFF", "TOGGLE", "MASK",
  "'+'", "'-'", "'*'", "'/'", "'('", "')'", "$accept", "top_level",
  "command_list", "end_cmd", "command", "machine_state_rules",
  "register_mod", "symbol_table_rules", "asm_rules", "$@1", "memory_rules",
  "checkpoint_rules", "checkpoint_control_rules", "monitor_state_rules",
  "monitor_misc_rules", "disk_rules", "cmd_file_rules", "data_entry_rules",
  "monitor_debug_rules", "rest_of_line", "opt_rest_of_line", "filename",
  "device_num", "opt_mem_op", "register", "reg_list", "reg_asgn",
  "checkpt_num", "address_opt_range", "address_range", "opt_address",
  "address", "opt_sep", "memspace", "memloc", "memaddr", "expression",
  "cond_expr", "compare_operand", "data_list", "data_element", "hunt_list",
  "hunt_element", "value", "d_number", "guess_default", "number",
  "assembly_instr_list", "assembly_instruction", "post_assemble",
  "asm_operand_mode", 0
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,    43,    45,    42,    47,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   158,   159,   159,   159,   160,   160,   161,   161,   161,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   164,   164,   164,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   167,   166,   166,   166,   166,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   171,   171,   171,   171,   171,   171,   171,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   174,
     174,   174,   175,   175,   176,   177,   178,   178,   179,   179,
     180,   180,   181,   181,   182,   182,   183,   183,   184,   185,
     185,   186,   186,   187,   187,   187,   188,   188,   189,   189,
     189,   190,   190,   191,   191,   191,   191,   191,   192,   193,
     194,   194,   194,   194,   194,   194,   194,   195,   195,   195,
     195,   195,   196,   196,   197,   197,   198,   198,   199,   199,
     200,   200,   200,   201,   201,   202,   202,   202,   202,   203,
     203,   203,   204,   204,   204,   204,   204,   205,   205,   205,
     206,   207,   207,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     3,     5,     3,     2,     3,
       2,     3,     2,     4,     2,     3,     3,     2,     4,     2,
       4,     2,     4,     2,     4,     2,     1,     2,     3,     3,
       5,     3,     5,     3,     5,     3,     5,     3,     2,     4,
       5,     0,     5,     3,     3,     2,     5,     5,     5,     5,
       5,     3,     2,     3,     2,     3,     2,     3,     2,     3,
       2,     2,     2,     4,     5,     5,     3,     5,     4,     6,
       2,     3,     5,     4,     6,     2,     3,     5,     4,     6,
       2,     3,     2,     3,     3,     3,     5,     3,     2,     5,
       5,     4,     3,     2,     3,     2,     3,     2,     2,     2,
       3,     3,     2,     3,     3,     3,     3,     3,     2,     3,
       2,     3,     5,     3,     4,     2,     4,     4,     2,     3,
       5,     5,     5,     3,     4,     5,     4,     5,     4,     5,
       5,     2,     3,     4,     3,     3,     5,     3,     5,     3,
       2,     3,     4,     2,     2,     1,     1,     0,     1,     1,
       1,     1,     1,     0,     1,     2,     3,     1,     3,     1,
       1,     1,     1,     3,     1,     3,     2,     0,     1,     3,
       1,     1,     0,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     1,     1,     2,     1,     3,     3,     6,     4,     3,
       5,     5,     5,     7,     3,     3,     3,     3,     3,     3,
       5,     5,     5,     5,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    22,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   167,     0,
       0,     0,     0,     0,   192,     0,     0,     0,     0,     0,
     167,     0,     0,     0,     0,     0,   264,     0,     0,     0,
       2,     5,    10,    46,    11,    13,    12,    14,    15,    16,
      17,    18,    19,    20,    21,     0,   232,   233,   234,   235,
     231,   230,   229,   193,   194,   195,   196,   197,   174,     0,
     224,     0,     0,   206,   236,   223,     9,     8,     7,     0,
     113,    34,     0,     0,   191,    41,     0,    43,     0,   169,
     168,     0,     0,     0,   180,   225,   228,   227,   226,     0,
     179,   184,   190,   192,   192,   192,   188,   198,   199,   192,
     192,     0,   192,    47,     0,     0,   177,     0,     0,   115,
     192,    72,     0,   181,   192,   172,    90,     0,     0,   100,
       0,     0,    28,     0,   192,     0,     0,   119,     9,   108,
       0,     0,     0,     0,    65,     0,    39,     0,    37,     0,
       0,     0,   165,   122,     0,    95,     0,     0,     0,     0,
     118,     0,     0,    23,     0,     0,   192,     0,   192,   192,
       0,   192,    58,     0,     0,   160,     0,    74,     0,    76,
       0,    78,     0,    80,     0,     0,   163,     0,     0,     0,
      45,   102,     0,     0,    30,   164,   128,     0,   130,   166,
       0,     0,     0,     0,     0,   135,     0,     0,   138,    32,
       0,    81,    82,     0,   192,     0,     9,   151,     0,   170,
     117,     0,     0,     0,     0,     0,   265,   266,   267,   268,
     269,   270,   273,   276,   277,   278,   279,   280,   281,   282,
     271,   274,   272,   275,   244,   240,     0,     0,     1,     6,
       3,     0,   175,     0,     0,     0,     0,   125,   112,   192,
       0,     0,     0,   171,   192,   143,     0,     0,   105,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,    49,
      48,   114,     0,    71,     0,     0,    86,     0,     0,    96,
      29,     0,    35,    36,   107,     0,     0,     0,    63,     0,
      64,     0,     0,   121,   116,   123,     0,     0,    91,   120,
     124,   126,    25,    24,     0,    51,     0,    53,     0,     0,
      55,     0,    57,   159,   161,    73,    75,    77,    79,   217,
       0,   215,   216,   127,   192,     0,   101,    31,   131,     0,
     129,   133,     0,     0,   154,     0,     0,     0,     0,     0,
     139,   152,   155,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,   103,   104,   205,   204,
     200,   201,   202,   203,     0,     0,     0,    42,    44,     0,
     144,     0,   148,     0,     0,   222,   221,     0,   219,   220,
     183,   185,   189,     0,     0,   178,   176,     0,     0,    88,
       0,   212,     0,   211,   213,     0,    98,     0,     0,     0,
     111,     0,   242,   241,     0,    40,    38,     0,    93,     0,
       0,     0,     0,     0,     0,   162,     0,     0,   146,     0,
       0,   134,   153,   136,   137,    33,    83,     0,     0,     0,
       0,     0,    59,   254,   255,   256,   257,   258,   259,   249,
       0,     0,   245,   246,   149,   186,   150,   140,   142,   147,
     106,    69,   218,    68,    66,    70,     0,     0,     0,    87,
       0,    97,    67,   109,   110,     0,   239,    62,     0,    92,
      26,    50,    52,    54,    56,   214,   141,   145,   132,    84,
      85,   156,   158,    60,     0,     0,     0,   248,    89,   210,
     209,   208,   207,    99,   237,   238,    94,   260,   251,   252,
     261,   262,   263,     0,   250,     0,     0,   247,   253
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    89,    90,   130,    91,    92,    93,    94,    95,   349,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   204,
     250,   141,   268,   177,   120,   165,   166,   149,   172,   173,
     424,   174,   425,   121,   156,   157,   269,   452,   453,   380,
     381,   437,   438,   123,   150,   124,   158,   462,   105,   464,
     295
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -347
static const yytype_int16 yypact[] =
{
    1195,   956,  -347,  -347,    26,   204,   956,   956,   761,   761,
       1,     1,     1,   365,  1533,  1533,  1533,  1551,   519,    24,
    1065,  1165,  1165,  1432,  1533,     1,     1,   204,   502,   365,
     365,  1551,  1306,   761,   761,   956,   633,    54,  1165,  -127,
    -127,   204,  -127,   441,   213,   213,  1551,   250,   606,     1,
     204,     1,  1306,  1306,  1306,  1306,  1551,   204,  -107,     1,
       1,   204,  1306,    44,   204,   204,     1,   204,  -100,  -105,
     -93,     1,   956,   761,   -62,   204,   761,   204,   761,     1,
    -100,   476,   204,     1,     1,    43,  1594,   365,   365,    75,
    1320,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,    60,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   956,
    -347,   -60,    64,  -347,  -347,  -347,  -347,  -347,  -347,   204,
    -347,  -347,   882,   882,  -347,  -347,   956,  -347,   956,  -347,
    -347,   105,   719,   105,  -347,  -347,  -347,  -347,  -347,   761,
    -347,  -347,  -347,   -62,   -62,   -62,  -347,  -347,  -347,   -62,
     -62,   204,   -62,  -347,    73,   241,  -347,    91,   204,  -347,
     -62,  -347,   204,  -347,   256,  -347,  -347,  1533,   340,  -347,
    1533,   482,  -347,   204,   -62,   204,   204,  -347,   285,  -347,
     204,    84,    12,   125,  -347,   204,  -347,   956,  -347,   956,
      64,   204,  -347,  -347,   204,  -347,  1533,   531,   204,   204,
    -347,   204,   204,  -347,    97,   204,   -62,   204,   -62,   -62,
     204,   -62,  -347,   204,   204,  -347,   204,  -347,   204,  -347,
     204,  -347,   204,  -347,   204,   678,  -347,   204,   105,   105,
    -347,  -347,   204,   204,  -347,  -347,  -347,   761,  -347,  -347,
     204,   204,   -36,   956,    64,  -347,   956,   956,  -347,  -347,
     956,  -347,  -347,   956,   -62,   204,   308,  -347,   204,     9,
    -347,  1616,  1616,  1551,   740,   932,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,    -6,  -347,   204,   204,  -347,  -347,
    -347,     3,  -347,   956,   956,   956,   956,  -347,  -347,    56,
     279,    64,    64,  -347,   310,  1455,  1475,  1515,  -347,   956,
      85,  1551,  1118,   678,  1551,  -347,   932,   932,   297,  -347,
    -347,  -347,  1533,  -347,   580,  1036,  -347,   596,  1036,  -347,
    -347,  1551,  -347,  -347,  -347,  1036,   204,    -9,  -347,    -7,
    -347,    64,    64,  -347,  -347,  -347,   642,  1036,  -347,  -347,
    -347,  -347,  -347,  -347,    -4,  -347,     1,  -347,     1,    -5,
    -347,    13,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    1571,  -347,  -347,  -347,   310,  1495,  -347,  -347,  -347,   956,
    -347,  -347,   204,    64,  -347,    64,    64,    64,   910,   956,
    -347,  -347,  -347,   932,  -347,   932,   149,    48,    58,    70,
      93,    95,   112,  -110,    57,   -57,  -347,  -347,  -347,  -347,
     -10,   -10,  -347,  -347,   204,  1551,   204,  -347,  -347,   204,
    -347,   204,  -347,   204,    64,  -347,  -347,   989,  -347,  -347,
    -347,  -347,  -347,  1571,   204,  -347,  -347,   204,  1036,  -347,
    1036,  -347,     6,  -347,  -347,  1036,  -347,     6,   204,     6,
    -347,   204,    76,    83,   204,  -347,  -347,  1036,  -347,     6,
     204,   204,   204,   204,   204,  -347,   678,   204,  -347,   204,
      64,  -347,  -347,  -347,  -347,  -347,  -347,   204,    64,   204,
     204,   204,  -347,  -347,  -347,  -347,  -347,  -347,  -347,   110,
     126,   932,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,     6,    32,  1091,  -347,
       6,  -347,  -347,  -347,  -347,    -7,    -7,  -347,     6,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,   581,   133,   135,   136,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,   140,  -347,   932,   137,  -347,  -347
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -347,  -347,  -347,   362,   161,  -347,  -347,  -347,  -347,  -347,
    -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,  -347,    30,
     180,   141,   207,    -3,     0,  -347,   -56,   -14,   -12,     7,
    -303,    37,    29,   624,  -222,  -347,   726,  -321,  -347,   -48,
    -199,  -347,  -157,  -347,  -347,  -347,    -1,  -347,  -346,  -347,
    -347
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -193
static const yytype_int16 yytable[] =
{
     125,   499,   139,   463,   418,   125,   125,   126,   500,   178,
     181,   429,   202,   346,   190,   191,   192,   457,   164,   180,
     195,   153,   159,   160,   459,   126,   207,   126,   127,   128,
     237,   184,   251,   549,   125,   206,   469,   136,   138,   249,
     228,   230,   232,   234,   252,   126,   127,   128,   127,   128,
     242,   154,   154,   154,   161,   126,   134,  -187,   502,   503,
     183,   154,   197,   199,   273,   126,   127,   128,   193,   208,
     209,   125,   211,   296,   297,   298,   127,   128,  -187,  -187,
     125,   477,   300,   219,   302,   294,   127,   128,   106,   107,
     108,   109,   126,   235,   327,   110,   111,   112,   126,   345,
     442,   392,   256,   257,   442,   260,   313,   263,   106,   107,
     108,   109,   415,   127,   128,   110,   111,   112,   125,   127,
     128,   113,   114,   115,   116,   117,   126,   516,   461,   517,
     134,   125,   125,    86,   520,   125,   473,   125,   470,   140,
     125,   125,   125,   550,   305,   306,   528,   127,   128,  -192,
     126,   518,   142,   143,   474,   303,   304,   305,   306,   493,
     419,   303,   304,   305,   306,   334,   185,   186,   337,   494,
     168,   127,   128,   491,   134,   501,   129,   518,   319,   554,
     555,   495,   320,   321,   322,   215,   217,   243,   323,   324,
     224,   326,   226,   202,   356,   525,   125,   552,   125,   332,
     238,   239,   526,   321,   496,   126,   497,   247,   303,   304,
     305,   306,   253,   341,   139,   134,   303,   304,   305,   306,
     264,   347,   435,   498,   271,   272,   127,   128,   544,   113,
     114,   115,   116,   117,   382,   302,   436,   125,   125,  -192,
     545,   546,   126,   364,   563,   366,   564,   368,   369,   118,
     371,   299,   125,   568,   565,   125,   125,  -182,   566,   125,
     265,   119,   125,   127,   128,   -61,   113,   114,   115,   116,
     117,  -182,   446,   413,   414,   443,   389,   535,  -182,  -182,
     512,     0,   106,   107,   108,   109,  -180,     0,     0,   110,
     111,   112,     0,   399,     0,   113,   114,   115,   116,   117,
     403,   405,   125,   125,   125,   125,     0,  -180,  -180,  -171,
     406,  -187,     0,   113,   114,   115,   116,   117,   125,   439,
     447,     0,   382,   431,     0,     0,   445,     0,   164,     0,
    -171,  -171,  -187,  -187,   454,   451,     0,   454,   451,     0,
       0,   126,     0,     0,   454,   451,     0,   426,   314,   316,
     317,   140,     0,   154,   433,   335,   454,   451,   440,   328,
       0,   444,   127,   128,     0,     0,   144,   131,     0,   145,
     135,   137,     0,     0,   134,   146,   147,   148,   458,     0,
     163,   169,   171,   176,   179,   182,   487,     0,   125,   187,
     189,   220,   479,     0,   194,   196,   198,     0,   125,   203,
     205,     0,   489,   210,   490,   213,     0,     0,     0,   476,
     222,     0,   225,     0,   227,   229,   231,   233,     0,   236,
     152,     0,   154,   240,   241,   244,   245,   246,   134,   248,
       0,   303,   304,   305,   306,   255,   439,   258,   259,   261,
     262,   118,   126,   267,   270,   384,   385,   454,   451,   454,
     451,     0,     0,     0,   454,   451,     0,   113,   114,   115,
     116,   117,   505,   127,   128,     0,   454,   451,     0,     0,
       0,     0,   476,     0,     0,   382,     0,   266,     0,   106,
     107,   108,   109,   126,   307,     0,   110,   111,   112,     0,
       0,   308,   113,   114,   115,   116,   117,   338,   127,   128,
     547,     0,     0,   188,   127,   128,   145,   471,     0,   472,
       0,   318,   146,   147,   148,     0,     0,   454,   451,     0,
     126,     0,     0,   325,   127,   128,     0,   329,     0,   330,
     331,     0,   126,     0,   333,   113,   114,   115,   116,   117,
     336,   127,   128,   339,     0,   340,   357,   342,   343,     0,
       0,     0,   344,   127,   128,   348,     0,   350,     0,     0,
       0,     0,   353,   354,   567,     0,   355,     0,     0,   358,
     359,   360,     0,   361,   362,     0,   363,   365,     0,   367,
       0,   126,   370,   212,     0,   372,   373,     0,   374,     0,
     375,     0,   376,     0,   377,   448,   378,   126,     0,   383,
       0,     0,   127,   128,   386,   387,     0,   126,     0,   388,
       0,   455,   390,   391,     0,     0,   394,     0,   127,   128,
     118,     0,   113,   114,   115,   116,   117,   400,   127,   128,
     401,     0,   119,   402,   404,     0,     0,     0,   155,   155,
     155,   162,   167,   126,   155,   155,   155,   162,   155,   113,
     114,   115,   116,   117,     0,   162,   155,   467,   416,   417,
     201,     0,   155,   118,   127,   128,     0,   214,   216,   218,
     162,   221,   223,   427,   428,     0,   155,   155,   155,   155,
     162,   106,   107,   108,   109,     0,   155,     0,   110,   111,
     112,     0,     0,     0,   557,     0,   449,   558,   559,   456,
       0,     0,     0,     0,     0,     0,     0,     0,   460,     0,
     560,   561,   562,   465,   466,     0,     0,     0,   468,     0,
     315,     0,   106,   107,   108,   109,     0,   122,     0,   110,
     111,   112,   132,   133,     0,   113,   114,   115,   116,   117,
       0,     0,   475,   106,   107,   108,   109,     0,     0,     0,
     110,   111,   112,     0,   481,   482,     0,   483,   484,   485,
     486,   200,   126,     0,  -192,  -192,  -192,  -192,   492,     0,
       0,  -192,  -192,  -192,     0,     0,     0,  -192,  -192,  -192,
    -192,  -192,     0,   127,   128,     0,   504,     0,   506,     0,
       0,   507,     0,   508,     0,   509,   510,     0,   254,   511,
       0,   155,     0,     0,   155,   513,   514,     0,     0,   515,
       0,     0,     0,     0,   519,   379,     0,     0,     0,   521,
     522,   523,     0,   524,     0,     0,   527,     0,     0,     0,
     155,   529,   530,   531,   532,   533,   534,     0,     0,   536,
       0,   537,   538,     0,     0,   301,     0,     0,     0,   539,
     540,   541,   542,   543,     0,     0,     0,     0,   309,   310,
       0,     0,   311,   118,   312,     0,     0,   407,   408,   409,
     410,   411,   412,     0,     0,   119,     0,     0,   548,   134,
       0,     0,   553,     0,     0,   106,   107,   108,   109,     0,
     556,     0,   110,   111,   112,     0,     0,   162,   113,   114,
     115,   116,   117,     0,     0,  -192,     0,     0,     0,     0,
       0,   126,     0,   106,   107,   108,   109,  -192,     0,   151,
     110,   111,   112,   351,     0,   352,   113,   114,   115,   116,
     117,     0,   127,   128,   162,   106,   107,   108,   109,     0,
     155,   162,   110,   111,   112,   162,     0,     0,   162,     0,
       0,     0,     0,     0,     0,     0,   155,     0,     0,   106,
     107,   108,   109,     0,     0,   162,   110,   111,   112,     0,
       0,     0,   113,   114,   115,   116,   117,     0,     0,   393,
       0,     0,   395,   396,     0,     0,   397,     0,     0,   398,
     126,     0,   106,   107,   108,   109,     0,     0,     0,   110,
     111,   112,     0,     0,     0,     0,     0,     0,     0,   155,
       0,   127,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   155,     0,     0,     0,   118,     0,     0,   420,
     421,   422,   423,     0,   303,   304,   305,   306,   119,   106,
     107,   108,   109,     0,     0,   434,   110,   111,   112,   162,
       0,   152,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,   303,   304,   305,   306,   126,     0,   106,   107,
     108,   109,     0,     0,   151,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,     0,   127,   128,     0,
       0,     0,   551,     0,   106,   107,   108,   109,     0,     0,
     118,   110,   111,   112,     0,     0,     0,   113,   114,   115,
     116,   117,   119,     0,     0,   480,     0,     0,     0,     0,
       0,   106,   107,   108,   109,   488,   435,   441,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     436,     0,     0,     0,     0,     0,   450,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     0,   106,   107,
     108,   109,     0,     0,   151,   110,   111,   112,     0,   175,
     118,   113,   114,   115,   116,   117,     0,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   450,     1,     0,     0,     0,   152,     0,     2,     0,
       0,   170,     0,     0,     0,     0,     0,     3,     0,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   118,     0,    19,    20,    21,
      22,    23,     0,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     0,   152,   126,     0,   106,
     107,   108,   109,     0,     0,   151,   110,   111,   112,     0,
       0,     0,   113,   114,   115,   116,   117,     1,   127,   128,
       0,     0,     0,     2,     0,    86,     0,     0,     0,     0,
       0,     0,     0,    87,    88,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,     0,    19,    20,    21,    22,    23,     0,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       0,     0,     0,   126,     0,   106,   107,   108,   109,     0,
       0,     0,   110,   111,   112,     0,     0,   152,   113,   114,
     115,   116,   117,     0,   127,   128,  -171,     0,  -171,  -171,
    -171,  -171,     0,     0,  -171,  -171,  -171,  -171,    87,    88,
       0,  -171,  -171,  -171,  -171,  -171,   430,     0,   106,   107,
     108,   109,     0,     0,   151,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,   478,     0,   106,   107,
     108,   109,     0,     0,   151,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,   432,     0,   106,   107,
     108,   109,     0,     0,     0,   110,   111,   112,     0,     0,
       0,   113,   114,   115,   116,   117,   106,   107,   108,   109,
       0,     0,   151,   110,   111,   112,     0,     0,     0,   113,
     114,   115,   116,   117,   106,   107,   108,   109,     0,     0,
       0,   110,   111,   112,     0,     0,     0,   113,   114,   115,
     116,   117,   126,   152,  -192,  -192,  -192,  -192,     0,     0,
       0,  -192,  -192,  -192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,     0,  -171,   106,   107,   108,
     109,     0,     0,     0,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,   126,     0,  -192,
    -192,  -192,  -192,     0,     0,     0,  -192,  -192,  -192,     0,
       0,     0,     0,     0,     0,     0,   152,     0,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,     0,   152,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   274,     0,   275,   276,  -192,     0,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,     0,     0,     0,   134
};

static const yytype_int16 yycheck[] =
{
       1,   111,     1,   349,     1,     6,     7,     1,   118,    21,
      22,   314,   139,     1,    28,    29,    30,   338,    18,    22,
      32,    14,    15,    16,   345,     1,    38,     1,    22,    23,
     137,    24,   137,     1,    35,    38,   357,     8,     9,   139,
      52,    53,    54,    55,   137,     1,    22,    23,    22,    23,
      62,    14,    15,    16,    17,     1,   118,     1,   115,   116,
      23,    24,    33,    34,    21,     1,    22,    23,    31,    39,
      40,    72,    42,    87,    88,     0,    22,    23,    22,    23,
      81,   384,    22,    46,   144,    86,    22,    23,     3,     4,
       5,     6,     1,    56,    21,    10,    11,    12,     1,    15,
     322,   137,    73,    74,   326,    76,     1,    78,     3,     4,
       5,     6,   118,    22,    23,    10,    11,    12,   119,    22,
      23,    16,    17,    18,    19,    20,     1,   448,   137,   450,
     118,   132,   133,   140,   455,   136,   141,   138,   142,   138,
     141,   142,   143,   111,   154,   155,   467,    22,    23,   137,
       1,   145,    11,    12,   141,   152,   153,   154,   155,   111,
     157,   152,   153,   154,   155,   177,    25,    26,   180,   111,
     146,    22,    23,    24,   118,   118,   150,   145,   149,   525,
     526,   111,   153,   154,   155,    44,    45,   143,   159,   160,
      49,   162,    51,   139,   206,   119,   197,   518,   199,   170,
      59,    60,   119,   174,   111,     1,   111,    66,   152,   153,
     154,   155,    71,   184,     1,   118,   152,   153,   154,   155,
      79,   192,   137,   111,    83,    84,    22,    23,   118,    16,
      17,    18,    19,    20,   235,   144,   151,   238,   239,   142,
     114,   115,     1,   214,   111,   216,   111,   218,   219,   144,
     221,    90,   253,   116,   118,   256,   257,     1,   118,   260,
      80,   156,   263,    22,    23,   140,    16,    17,    18,    19,
      20,    15,   328,   274,   275,   323,   247,   476,    22,    23,
     437,    -1,     3,     4,     5,     6,     1,    -1,    -1,    10,
      11,    12,    -1,   264,    -1,    16,    17,    18,    19,    20,
     271,   272,   303,   304,   305,   306,    -1,    22,    23,     1,
     273,     1,    -1,    16,    17,    18,    19,    20,   319,   320,
     332,    -1,   323,   316,    -1,    -1,   327,    -1,   328,    -1,
      22,    23,    22,    23,   335,   335,    -1,   338,   338,    -1,
      -1,     1,    -1,    -1,   345,   345,    -1,   310,   141,   142,
     143,   138,    -1,   316,   317,    15,   357,   357,   321,   118,
      -1,   324,    22,    23,    -1,    -1,     1,     5,    -1,     4,
       8,     9,    -1,    -1,   118,    10,    11,    12,   341,    -1,
      18,    19,    20,    21,    22,    23,   398,    -1,   389,    27,
      28,   141,   385,    -1,    32,    33,    34,    -1,   399,    37,
      38,    -1,   403,    41,   405,    43,    -1,    -1,    -1,   380,
      48,    -1,    50,    -1,    52,    53,    54,    55,    -1,    57,
     141,    -1,   385,    61,    62,    63,    64,    65,   118,    67,
      -1,   152,   153,   154,   155,    73,   437,    75,    76,    77,
      78,   144,     1,    81,    82,   238,   239,   448,   448,   450,
     450,    -1,    -1,    -1,   455,   455,    -1,    16,    17,    18,
      19,    20,   425,    22,    23,    -1,   467,   467,    -1,    -1,
      -1,    -1,   443,    -1,    -1,   476,    -1,     1,    -1,     3,
       4,     5,     6,     1,   122,    -1,    10,    11,    12,    -1,
      -1,   129,    16,    17,    18,    19,    20,    15,    22,    23,
     501,    -1,    -1,     1,    22,    23,     4,   366,    -1,   368,
      -1,   149,    10,    11,    12,    -1,    -1,   518,   518,    -1,
       1,    -1,    -1,   161,    22,    23,    -1,   165,    -1,   167,
     168,    -1,     1,    -1,   172,    16,    17,    18,    19,    20,
     178,    22,    23,   181,    -1,   183,    15,   185,   186,    -1,
      -1,    -1,   190,    22,    23,   193,    -1,   195,    -1,    -1,
      -1,    -1,   200,   201,   565,    -1,   204,    -1,    -1,   207,
     208,   209,    -1,   211,   212,    -1,   214,   215,    -1,   217,
      -1,     1,   220,   142,    -1,   223,   224,    -1,   226,    -1,
     228,    -1,   230,    -1,   232,    15,   234,     1,    -1,   237,
      -1,    -1,    22,    23,   242,   243,    -1,     1,    -1,   247,
      -1,    15,   250,   251,    -1,    -1,   254,    -1,    22,    23,
     144,    -1,    16,    17,    18,    19,    20,   265,    22,    23,
     268,    -1,   156,   271,   272,    -1,    -1,    -1,    14,    15,
      16,    17,    18,     1,    20,    21,    22,    23,    24,    16,
      17,    18,    19,    20,    -1,    31,    32,    15,   296,   297,
      36,    -1,    38,   144,    22,    23,    -1,    43,    44,    45,
      46,    47,    48,   311,   312,    -1,    52,    53,    54,    55,
      56,     3,     4,     5,     6,    -1,    62,    -1,    10,    11,
      12,    -1,    -1,    -1,   113,    -1,   334,   116,   117,   337,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   346,    -1,
     129,   130,   131,   351,   352,    -1,    -1,    -1,   356,    -1,
       1,    -1,     3,     4,     5,     6,    -1,     1,    -1,    10,
      11,    12,     6,     7,    -1,    16,    17,    18,    19,    20,
      -1,    -1,   380,     3,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    12,    -1,   392,   393,    -1,   395,   396,   397,
     398,    35,     1,    -1,     3,     4,     5,     6,   406,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,   424,    -1,   426,    -1,
      -1,   429,    -1,   431,    -1,   433,   434,    -1,    72,   437,
      -1,   177,    -1,    -1,   180,   443,   444,    -1,    -1,   447,
      -1,    -1,    -1,    -1,   452,   137,    -1,    -1,    -1,   457,
     458,   459,    -1,   461,    -1,    -1,   464,    -1,    -1,    -1,
     206,   469,   470,   471,   472,   473,   474,    -1,    -1,   477,
      -1,   479,   480,    -1,    -1,   119,    -1,    -1,    -1,   487,
     488,   489,   490,   491,    -1,    -1,    -1,    -1,   132,   133,
      -1,    -1,   136,   144,   138,    -1,    -1,   127,   128,   129,
     130,   131,   132,    -1,    -1,   156,    -1,    -1,   516,   118,
      -1,    -1,   520,    -1,    -1,     3,     4,     5,     6,    -1,
     528,    -1,    10,    11,    12,    -1,    -1,   273,    16,    17,
      18,    19,    20,    -1,    -1,   144,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,   156,    -1,     9,
      10,    11,    12,   197,    -1,   199,    16,    17,    18,    19,
      20,    -1,    22,    23,   310,     3,     4,     5,     6,    -1,
     316,   317,    10,    11,    12,   321,    -1,    -1,   324,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   332,    -1,    -1,     3,
       4,     5,     6,    -1,    -1,   341,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,   253,
      -1,    -1,   256,   257,    -1,    -1,   260,    -1,    -1,   263,
       1,    -1,     3,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   398,    -1,    -1,    -1,   144,    -1,    -1,   303,
     304,   305,   306,    -1,   152,   153,   154,   155,   156,     3,
       4,     5,     6,    -1,    -1,   319,    10,    11,    12,   425,
      -1,   141,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,   152,   153,   154,   155,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,    -1,    -1,
     144,    10,    11,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,   156,    -1,    -1,   389,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,   399,   137,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,    -1,    -1,    -1,    -1,    -1,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    14,
     144,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,     7,    -1,    -1,    -1,   141,    -1,    13,    -1,
      -1,   146,    -1,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,   144,    -1,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,   141,     1,    -1,     3,
       4,     5,     6,    -1,    -1,     9,    10,    11,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,     7,    22,    23,
      -1,    -1,    -1,    13,    -1,   140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   148,   149,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    -1,    -1,   141,    16,    17,
      18,    19,    20,    -1,    22,    23,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,   148,   149,
      -1,    16,    17,    18,    19,    20,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     1,    -1,     3,     4,
       5,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     1,    -1,     3,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,     3,     4,     5,     6,
      -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    18,    19,    20,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,     1,   141,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,   141,     3,     4,     5,
       6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,     1,    -1,     3,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
      -1,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110,    -1,   112,   113,   137,    -1,
      -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,    -1,    -1,    -1,   118
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    13,    22,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    42,
      43,    44,    45,    46,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   140,   148,   149,   159,
     160,   162,   163,   164,   165,   166,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   206,     3,     4,     5,     6,
      10,    11,    12,    16,    17,    18,    19,    20,   144,   156,
     182,   191,   194,   201,   203,   204,     1,    22,    23,   150,
     161,   161,   194,   194,   118,   161,   190,   161,   190,     1,
     138,   179,   179,   179,     1,     4,    10,    11,    12,   185,
     202,     9,   141,   187,   189,   191,   192,   193,   204,   187,
     187,   189,   191,   161,   182,   183,   184,   191,   146,   161,
     146,   161,   186,   187,   189,    14,   161,   181,   186,   161,
     181,   186,   161,   189,   187,   179,   179,   161,     1,   161,
     185,   185,   185,   189,   161,   186,   161,   190,   161,   190,
     194,   191,   139,   161,   177,   161,   181,   186,   177,   177,
     161,   177,   142,   161,   191,   179,   191,   179,   191,   189,
     141,   191,   161,   191,   179,   161,   179,   161,   186,   161,
     186,   161,   186,   161,   186,   189,   161,   137,   179,   179,
     161,   161,   186,   143,   161,   161,   161,   179,   161,   139,
     178,   137,   137,   179,   194,   161,   190,   190,   161,   161,
     190,   161,   161,   190,   179,   178,     1,   161,   180,   194,
     161,   179,   179,    21,   110,   112,   113,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   204,   208,   185,   185,     0,   162,
      22,   194,   144,   152,   153,   154,   155,   161,   161,   194,
     194,   194,   194,     1,   180,     1,   180,   180,   161,   190,
     190,   190,   190,   190,   190,   161,   190,    21,   118,   161,
     161,   161,   190,   161,   186,    15,   161,   186,    15,   161,
     161,   190,   161,   161,   161,    15,     1,   190,   161,   167,
     161,   194,   194,   161,   161,   161,   186,    15,   161,   161,
     161,   161,   161,   161,   190,   161,   190,   161,   190,   190,
     161,   190,   161,   161,   161,   161,   161,   161,   161,   137,
     197,   198,   204,   161,   180,   180,   161,   161,   161,   190,
     161,   161,   137,   194,   161,   194,   194,   194,   194,   190,
     161,   161,   161,   190,   161,   190,   189,   127,   128,   129,
     130,   131,   132,   204,   204,   118,   161,   161,     1,   157,
     194,   194,   194,   194,   188,   190,   189,   161,   161,   188,
       1,   187,     1,   189,   194,   137,   151,   199,   200,   204,
     189,     9,   192,   197,   189,   204,   184,   186,    15,   161,
     110,   182,   195,   196,   204,    15,   161,   195,   189,   195,
     161,   137,   205,   206,   207,   161,   161,    15,   161,   195,
     142,   179,   179,   141,   141,   161,   190,   188,     1,   187,
     194,   161,   161,   161,   161,   161,   161,   186,   194,   204,
     204,    24,   161,   111,   111,   111,   111,   111,   111,   111,
     118,   118,   115,   116,   161,   189,   161,   161,   161,   161,
     161,   161,   200,   161,   161,   161,   195,   195,   145,   161,
     195,   161,   161,   161,   161,   119,   119,   161,   195,   161,
     161,   161,   161,   161,   161,   198,   161,   161,   161,   161,
     161,   161,   161,   161,   118,   114,   115,   204,   161,     1,
     111,     1,   195,   161,   206,   206,   161,   113,   116,   117,
     129,   130,   131,   111,   111,   118,   118,   204,   116
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
        case 2:

/* Line 1464 of yacc.c  */
#line 186 "mon_parse.y"
    { (yyval.i) = 0; }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 187 "mon_parse.y"
    { (yyval.i) = 0; }
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 188 "mon_parse.y"
    { new_cmd = 1; asm_mode = 0;  (yyval.i) = 0; }
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 197 "mon_parse.y"
    { return ERR_EXPECT_END_CMD; }
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 212 "mon_parse.y"
    { return ERR_BAD_CMD; }
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 216 "mon_parse.y"
    { mon_bank(e_default_space, NULL); }
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 218 "mon_parse.y"
    { mon_bank((yyvsp[(2) - (3)].i), NULL); }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 220 "mon_parse.y"
    { mon_bank(e_default_space, (yyvsp[(2) - (3)].str)); }
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 222 "mon_parse.y"
    { mon_bank((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].str)); }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 224 "mon_parse.y"
    { mon_jump((yyvsp[(2) - (3)].a)); }
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 226 "mon_parse.y"
    { mon_display_io_regs(0); }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 228 "mon_parse.y"
    { mon_display_io_regs((yyvsp[(2) - (3)].a)); }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 230 "mon_parse.y"
    { monitor_cpu_type_set(""); }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 232 "mon_parse.y"
    { monitor_cpu_type_set((yyvsp[(2) - (3)].str)); }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 234 "mon_parse.y"
    { mon_cpuhistory(-1); }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 236 "mon_parse.y"
    { mon_cpuhistory((yyvsp[(3) - (4)].i)); }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 238 "mon_parse.y"
    { mon_instruction_return(); }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 240 "mon_parse.y"
    { machine_write_snapshot((yyvsp[(2) - (3)].str),0,0,0); /* FIXME */ }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 242 "mon_parse.y"
    { machine_read_snapshot((yyvsp[(2) - (3)].str), 0); }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 244 "mon_parse.y"
    { mon_instructions_step(-1); }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 246 "mon_parse.y"
    { mon_instructions_step((yyvsp[(3) - (4)].i)); }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 248 "mon_parse.y"
    { mon_instructions_next(-1); }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 250 "mon_parse.y"
    { mon_instructions_next((yyvsp[(3) - (4)].i)); }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 252 "mon_parse.y"
    { mon_stack_up(-1); }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 254 "mon_parse.y"
    { mon_stack_up((yyvsp[(3) - (4)].i)); }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 256 "mon_parse.y"
    { mon_stack_down(-1); }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 258 "mon_parse.y"
    { mon_stack_down((yyvsp[(3) - (4)].i)); }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 260 "mon_parse.y"
    { mon_display_screen(); }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 265 "mon_parse.y"
    { (monitor_cpu_for_memspace[default_memspace]->mon_register_print)(default_memspace); }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 267 "mon_parse.y"
    { (monitor_cpu_for_memspace[(yyvsp[(2) - (3)].i)]->mon_register_print)((yyvsp[(2) - (3)].i)); }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 272 "mon_parse.y"
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[(4) - (5)].str));
                    }
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 277 "mon_parse.y"
    {
                        /* What about the memspace? */
                        mon_playback_init((yyvsp[(2) - (3)].str));
                    }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 282 "mon_parse.y"
    { mon_save_symbols((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].str)); }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 284 "mon_parse.y"
    { mon_save_symbols(e_default_space, (yyvsp[(2) - (3)].str)); }
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 286 "mon_parse.y"
    { mon_add_name_to_symbol_table((yyvsp[(2) - (5)].a), (yyvsp[(4) - (5)].str)); }
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 288 "mon_parse.y"
    { mon_remove_name_from_symbol_table(e_default_space, (yyvsp[(2) - (3)].str)); }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 290 "mon_parse.y"
    { mon_remove_name_from_symbol_table((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].str)); }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 292 "mon_parse.y"
    { mon_print_symbol_table((yyvsp[(2) - (3)].i)); }
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 294 "mon_parse.y"
    { mon_print_symbol_table(e_default_space); }
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 296 "mon_parse.y"
    {
                        mon_add_name_to_symbol_table((yyvsp[(3) - (4)].a), mon_prepend_dot_to_name((yyvsp[(1) - (4)].str)));
                    }
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 300 "mon_parse.y"
    {
                        mon_add_name_to_symbol_table((yyvsp[(3) - (5)].a), mon_prepend_dot_to_name((yyvsp[(1) - (5)].str)));
                    }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 306 "mon_parse.y"
    { mon_start_assemble_mode((yyvsp[(2) - (2)].a), NULL); }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 307 "mon_parse.y"
    { }
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 309 "mon_parse.y"
    { mon_start_assemble_mode((yyvsp[(2) - (3)].a), NULL); }
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 311 "mon_parse.y"
    { mon_disassemble_lines((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1]); }
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 313 "mon_parse.y"
    { mon_disassemble_lines(BAD_ADDR, BAD_ADDR); }
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 317 "mon_parse.y"
    { mon_memory_move((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1], (yyvsp[(4) - (5)].a)); }
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 319 "mon_parse.y"
    { mon_memory_compare((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1], (yyvsp[(4) - (5)].a)); }
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 321 "mon_parse.y"
    { mon_memory_fill((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1],(unsigned char *)(yyvsp[(4) - (5)].str)); }
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 323 "mon_parse.y"
    { mon_memory_hunt((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1],(unsigned char *)(yyvsp[(4) - (5)].str)); }
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 325 "mon_parse.y"
    { mon_memory_display((yyvsp[(2) - (5)].rt), (yyvsp[(4) - (5)].range)[0], (yyvsp[(4) - (5)].range)[1], DF_PETSCII); }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 327 "mon_parse.y"
    { mon_memory_display(default_radix, (yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], DF_PETSCII); }
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 329 "mon_parse.y"
    { mon_memory_display(default_radix, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 331 "mon_parse.y"
    { mon_memory_display_data((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], 8, 8); }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 333 "mon_parse.y"
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 8, 8); }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 335 "mon_parse.y"
    { mon_memory_display_data((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], 24, 21); }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 337 "mon_parse.y"
    { mon_memory_display_data(BAD_ADDR, BAD_ADDR, 24, 21); }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 339 "mon_parse.y"
    { mon_memory_display(0, (yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], DF_PETSCII); }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 341 "mon_parse.y"
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_PETSCII); }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 343 "mon_parse.y"
    { mon_memory_display(0, (yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], DF_SCREEN_CODE); }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 345 "mon_parse.y"
    { mon_memory_display(0, BAD_ADDR, BAD_ADDR, DF_SCREEN_CODE); }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 347 "mon_parse.y"
    { mon_memmap_zap(); }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 349 "mon_parse.y"
    { mon_memmap_show(-1,BAD_ADDR,BAD_ADDR); }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 351 "mon_parse.y"
    { mon_memmap_show((yyvsp[(3) - (4)].i),BAD_ADDR,BAD_ADDR); }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 353 "mon_parse.y"
    { mon_memmap_show((yyvsp[(3) - (5)].i),(yyvsp[(4) - (5)].range)[0],(yyvsp[(4) - (5)].range)[1]); }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 355 "mon_parse.y"
    { mon_memmap_save((yyvsp[(2) - (5)].str),(yyvsp[(4) - (5)].i)); }
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 359 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], TRUE, e_exec, FALSE);
                  }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 363 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1], TRUE, e_exec, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(4) - (5)].cond_node));
                  }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 368 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(3) - (4)].range)[0], (yyvsp[(3) - (4)].range)[1], TRUE, (yyvsp[(2) - (4)].i), FALSE);
                  }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 372 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(3) - (6)].range)[0], (yyvsp[(3) - (6)].range)[1], TRUE, (yyvsp[(2) - (6)].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(5) - (6)].cond_node));
                  }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 377 "mon_parse.y"
    { mon_breakpoint_print_checkpoints(); }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 380 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], TRUE, e_load | e_store, FALSE);
                  }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 384 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1], TRUE, e_load | e_store, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(4) - (5)].cond_node));
                  }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 389 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(3) - (4)].range)[0], (yyvsp[(3) - (4)].range)[1], TRUE, (yyvsp[(2) - (4)].i), FALSE);
                  }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 393 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(3) - (6)].range)[0], (yyvsp[(3) - (6)].range)[1], TRUE, (yyvsp[(2) - (6)].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(5) - (6)].cond_node));
                  }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 398 "mon_parse.y"
    { mon_breakpoint_print_checkpoints(); }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 401 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], FALSE, e_load | e_store | e_exec, FALSE);
                  }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 405 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(2) - (5)].range)[0], (yyvsp[(2) - (5)].range)[1], FALSE, e_load | e_store | e_exec, FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(4) - (5)].cond_node));
                  }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 410 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(3) - (4)].range)[0], (yyvsp[(3) - (4)].range)[1], FALSE, (yyvsp[(2) - (4)].i), FALSE);
                  }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 414 "mon_parse.y"
    {
                      temp = mon_breakpoint_add_checkpoint((yyvsp[(3) - (6)].range)[0], (yyvsp[(3) - (6)].range)[1], FALSE, (yyvsp[(2) - (6)].i), FALSE);
                      mon_breakpoint_set_checkpoint_condition(temp, (yyvsp[(5) - (6)].cond_node));
                  }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 419 "mon_parse.y"
    { mon_breakpoint_print_checkpoints(); }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 422 "mon_parse.y"
    {
                      mon_breakpoint_add_checkpoint((yyvsp[(2) - (3)].range)[0], (yyvsp[(2) - (3)].range)[1], TRUE, e_exec, TRUE);
                  }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 426 "mon_parse.y"
    { mon_breakpoint_print_checkpoints(); }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 431 "mon_parse.y"
    { mon_breakpoint_switch_checkpoint(e_ON, (yyvsp[(2) - (3)].i)); }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 433 "mon_parse.y"
    { mon_breakpoint_switch_checkpoint(e_OFF, (yyvsp[(2) - (3)].i)); }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 435 "mon_parse.y"
    { mon_breakpoint_set_ignore_count((yyvsp[(2) - (3)].i), -1); }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 437 "mon_parse.y"
    { mon_breakpoint_set_ignore_count((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].i)); }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 439 "mon_parse.y"
    { mon_breakpoint_delete_checkpoint((yyvsp[(2) - (3)].i)); }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 441 "mon_parse.y"
    { mon_breakpoint_delete_checkpoint(-1); }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 443 "mon_parse.y"
    { mon_breakpoint_set_checkpoint_condition((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].cond_node)); }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 445 "mon_parse.y"
    { mon_breakpoint_set_checkpoint_command((yyvsp[(2) - (5)].i), (yyvsp[(4) - (5)].str)); }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 447 "mon_parse.y"
    { return ERR_EXPECT_STRING; }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 451 "mon_parse.y"
    { sidefx = (((yyvsp[(2) - (3)].action) == e_TOGGLE) ? (sidefx ^ 1) : (yyvsp[(2) - (3)].action)); }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 453 "mon_parse.y"
    {
                         mon_out("I/O side effects are %s\n",
                                   sidefx ? "enabled" : "disabled");
                     }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 458 "mon_parse.y"
    { default_radix = (yyvsp[(2) - (3)].rt); }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 460 "mon_parse.y"
    {
                         const char *p;

                         if (default_radix == e_hexadecimal)
                             p = "Hexadecimal";
                         else if (default_radix == e_decimal)
                             p = "Decimal";
                         else if (default_radix == e_octal)
                             p = "Octal";
                         else if (default_radix == e_binary)
                             p = "Binary";
                         else
                             p = "Unknown";

                         mon_out("Default radix is %s\n", p);
                     }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 478 "mon_parse.y"
    { monitor_change_device((yyvsp[(2) - (3)].i)); }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 480 "mon_parse.y"
    { mon_export(); }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 482 "mon_parse.y"
    { mon_quit(); YYACCEPT; }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 484 "mon_parse.y"
    { exit_mon = 1; YYACCEPT; }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 488 "mon_parse.y"
    { mon_drive_execute_disk_cmd((yyvsp[(2) - (3)].str)); }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 490 "mon_parse.y"
    { mon_out("\t%d\n",(yyvsp[(2) - (3)].i)); }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 492 "mon_parse.y"
    { mon_command_print_help(NULL); }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 494 "mon_parse.y"
    { mon_command_print_help((yyvsp[(2) - (3)].str)); }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 496 "mon_parse.y"
    { printf("SYSTEM COMMAND: %s\n",(yyvsp[(2) - (3)].str)); }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 498 "mon_parse.y"
    { mon_print_convert((yyvsp[(2) - (3)].i)); }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 500 "mon_parse.y"
    { mon_change_dir((yyvsp[(2) - (3)].str)); }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 502 "mon_parse.y"
    { mon_keyboard_feed((yyvsp[(2) - (3)].str)); }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 504 "mon_parse.y"
    { mon_backtrace(); }
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 506 "mon_parse.y"
    { mon_show_dir((yyvsp[(2) - (3)].str)); }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 508 "mon_parse.y"
    { mon_show_pwd(); }
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 510 "mon_parse.y"
    { mon_screenshot_save((yyvsp[(2) - (3)].str),-1); }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 512 "mon_parse.y"
    { mon_screenshot_save((yyvsp[(2) - (5)].str),(yyvsp[(4) - (5)].i)); }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 514 "mon_parse.y"
    { mon_resource_get((yyvsp[(2) - (3)].str)); }
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 516 "mon_parse.y"
    { mon_resource_set((yyvsp[(2) - (4)].str),(yyvsp[(3) - (4)].str)); }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 518 "mon_parse.y"
    { mon_reset_machine(-1); }
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 520 "mon_parse.y"
    { mon_reset_machine((yyvsp[(3) - (4)].i)); }
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 522 "mon_parse.y"
    { mon_tape_ctrl((yyvsp[(3) - (4)].i)); }
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 524 "mon_parse.y"
    { mon_cart_freeze(); }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 526 "mon_parse.y"
    { }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 530 "mon_parse.y"
    { mon_file_load((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].i), (yyvsp[(4) - (5)].a), FALSE); }
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 532 "mon_parse.y"
    { mon_file_load((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].i), (yyvsp[(4) - (5)].a), TRUE); }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 534 "mon_parse.y"
    { mon_file_save((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].i), (yyvsp[(4) - (5)].range)[0], (yyvsp[(4) - (5)].range)[1], FALSE); }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 536 "mon_parse.y"
    { return ERR_EXPECT_DEVICE_NUM; }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 538 "mon_parse.y"
    { return ERR_EXPECT_ADDRESS; }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 540 "mon_parse.y"
    { mon_file_save((yyvsp[(2) - (5)].str), (yyvsp[(3) - (5)].i), (yyvsp[(4) - (5)].range)[0], (yyvsp[(4) - (5)].range)[1], TRUE); }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 542 "mon_parse.y"
    { return ERR_EXPECT_ADDRESS; }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 544 "mon_parse.y"
    { mon_file_verify((yyvsp[(2) - (5)].str),(yyvsp[(3) - (5)].i),(yyvsp[(4) - (5)].a)); }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 546 "mon_parse.y"
    { return ERR_EXPECT_ADDRESS; }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 548 "mon_parse.y"
    { mon_drive_block_cmd(0,(yyvsp[(2) - (5)].i),(yyvsp[(3) - (5)].i),(yyvsp[(4) - (5)].a)); }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 550 "mon_parse.y"
    { mon_drive_block_cmd(1,(yyvsp[(2) - (5)].i),(yyvsp[(3) - (5)].i),(yyvsp[(4) - (5)].a)); }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 552 "mon_parse.y"
    { mon_drive_list(-1); }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 554 "mon_parse.y"
    { mon_drive_list((yyvsp[(2) - (3)].i)); }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 556 "mon_parse.y"
    { mon_attach((yyvsp[(2) - (4)].str),(yyvsp[(3) - (4)].i)); }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 558 "mon_parse.y"
    { mon_detach((yyvsp[(2) - (3)].i)); }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 560 "mon_parse.y"
    { mon_autostart((yyvsp[(2) - (3)].str),0,1); }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 562 "mon_parse.y"
    { mon_autostart((yyvsp[(2) - (5)].str),(yyvsp[(4) - (5)].i),1); }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 564 "mon_parse.y"
    { mon_autostart((yyvsp[(2) - (3)].str),0,0); }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 566 "mon_parse.y"
    { mon_autostart((yyvsp[(2) - (5)].str),(yyvsp[(4) - (5)].i),0); }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 570 "mon_parse.y"
    { mon_record_commands((yyvsp[(2) - (3)].str)); }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 572 "mon_parse.y"
    { mon_end_recording(); }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 574 "mon_parse.y"
    { mon_playback_init((yyvsp[(2) - (3)].str)); }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 578 "mon_parse.y"
    { mon_memory_fill((yyvsp[(2) - (4)].a), BAD_ADDR, (unsigned char *)(yyvsp[(3) - (4)].str)); }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 580 "mon_parse.y"
    { printf("Not yet.\n"); }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 584 "mon_parse.y"
    { yydebug = 1; }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 587 "mon_parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 590 "mon_parse.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 591 "mon_parse.y"
    { (yyval.str) = NULL; }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 595 "mon_parse.y"
    { return ERR_EXPECT_FILENAME; }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 599 "mon_parse.y"
    { return ERR_EXPECT_DEVICE_NUM; }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 602 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 603 "mon_parse.y"
    { (yyval.i) = e_load | e_store | e_exec; }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 606 "mon_parse.y"
    { (yyval.i) = new_reg(default_memspace, (yyvsp[(1) - (1)].reg)); }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 607 "mon_parse.y"
    { (yyval.i) = new_reg((yyvsp[(1) - (2)].i), (yyvsp[(2) - (2)].reg)); }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 615 "mon_parse.y"
    { (monitor_cpu_for_memspace[reg_memspace((yyvsp[(1) - (3)].i))]->mon_register_set_val)(reg_memspace((yyvsp[(1) - (3)].i)), reg_regid((yyvsp[(1) - (3)].i)), (WORD) (yyvsp[(3) - (3)].i)); }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 618 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 619 "mon_parse.y"
    { return ERR_EXPECT_CHECKNUM; }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 623 "mon_parse.y"
    { (yyval.range)[0] = (yyvsp[(1) - (1)].a); (yyval.range)[1] = BAD_ADDR; }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 626 "mon_parse.y"
    { (yyval.range)[0] = (yyvsp[(1) - (3)].a); (yyval.range)[1] = (yyvsp[(3) - (3)].a); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 628 "mon_parse.y"
    { if (resolve_range(e_default_space, (yyval.range), (yyvsp[(1) - (1)].str))) return ERR_ADDR_TOO_BIG; }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 630 "mon_parse.y"
    { if (resolve_range((yyvsp[(1) - (3)].i), (yyval.range), (yyvsp[(3) - (3)].str))) return ERR_ADDR_TOO_BIG; }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 633 "mon_parse.y"
    { (yyval.a) = (yyvsp[(2) - (2)].a); }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 634 "mon_parse.y"
    { (yyval.a) = BAD_ADDR; }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 638 "mon_parse.y"
    {
             (yyval.a) = new_addr(e_default_space,(yyvsp[(1) - (1)].i));
             if (opt_asm) new_cmd = asm_mode = 1; 
         }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 643 "mon_parse.y"
    {
             (yyval.a) = new_addr((yyvsp[(1) - (3)].i), (yyvsp[(3) - (3)].i));
             if (opt_asm) new_cmd = asm_mode = 1; 
         }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 648 "mon_parse.y"
    {
             temp = mon_symbol_table_lookup_addr(e_default_space, (yyvsp[(1) - (1)].str));
             if (temp >= 0)
                 (yyval.a) = new_addr(e_default_space, temp);
             else
                 return ERR_UNDEFINED_LABEL;
         }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 661 "mon_parse.y"
    { (yyval.i) = e_comp_space; }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 662 "mon_parse.y"
    { (yyval.i) = e_disk8_space; }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 663 "mon_parse.y"
    { (yyval.i) = e_disk9_space; }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 664 "mon_parse.y"
    { (yyval.i) = e_disk10_space; }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 665 "mon_parse.y"
    { (yyval.i) = e_disk11_space; }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 668 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); if (!CHECK_ADDR((yyvsp[(1) - (1)].i))) return ERR_ADDR_TOO_BIG; }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 670 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 672 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (3)].i) + (yyvsp[(3) - (3)].i); }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 673 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (3)].i) - (yyvsp[(3) - (3)].i); }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 674 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (3)].i) * (yyvsp[(3) - (3)].i); }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 675 "mon_parse.y"
    { (yyval.i) = ((yyvsp[(3) - (3)].i)) ? ((yyvsp[(1) - (3)].i) / (yyvsp[(3) - (3)].i)) : 1; }
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 676 "mon_parse.y"
    { (yyval.i) = (yyvsp[(2) - (3)].i); }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 677 "mon_parse.y"
    { return ERR_MISSING_CLOSE_PAREN; }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 678 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 682 "mon_parse.y"
    {
               (yyval.cond_node) = new_cond; (yyval.cond_node)->is_parenthized = FALSE;
               (yyval.cond_node)->child1 = (yyvsp[(1) - (3)].cond_node); (yyval.cond_node)->child2 = (yyvsp[(3) - (3)].cond_node); (yyval.cond_node)->operation = (yyvsp[(2) - (3)].cond_op);
           }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 687 "mon_parse.y"
    { return ERR_INCOMPLETE_COMPARE_OP; }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 689 "mon_parse.y"
    { (yyval.cond_node) = (yyvsp[(2) - (3)].cond_node); (yyval.cond_node)->is_parenthized = TRUE; }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 691 "mon_parse.y"
    { return ERR_MISSING_CLOSE_PAREN; }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 693 "mon_parse.y"
    { (yyval.cond_node) = (yyvsp[(1) - (1)].cond_node); }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 696 "mon_parse.y"
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->reg_num = (yyvsp[(1) - (1)].i); (yyval.cond_node)->is_reg = TRUE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 702 "mon_parse.y"
    { (yyval.cond_node) = new_cond;
                            (yyval.cond_node)->operation = e_INV;
                            (yyval.cond_node)->is_parenthized = FALSE;
                            (yyval.cond_node)->value = (yyvsp[(1) - (1)].i); (yyval.cond_node)->is_reg = FALSE;
                            (yyval.cond_node)->child1 = NULL; (yyval.cond_node)->child2 = NULL;
                          }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 714 "mon_parse.y"
    { mon_add_number_to_buffer((yyvsp[(1) - (1)].i)); }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 715 "mon_parse.y"
    { mon_add_string_to_buffer((yyvsp[(1) - (1)].str)); }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 722 "mon_parse.y"
    { mon_add_number_to_buffer((yyvsp[(1) - (1)].i)); }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 723 "mon_parse.y"
    { mon_add_number_masked_to_buffer((yyvsp[(1) - (1)].i), 0x00); }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 724 "mon_parse.y"
    { mon_add_string_to_buffer((yyvsp[(1) - (1)].str)); }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 727 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 728 "mon_parse.y"
    { (yyval.i) = (monitor_cpu_for_memspace[reg_memspace((yyvsp[(1) - (1)].i))]->mon_register_get_val)(reg_memspace((yyvsp[(1) - (1)].i)), reg_regid((yyvsp[(1) - (1)].i))); }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 731 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 732 "mon_parse.y"
    { (yyval.i) = strtol((yyvsp[(1) - (1)].str), NULL, 10); }
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 733 "mon_parse.y"
    { (yyval.i) = strtol((yyvsp[(1) - (1)].str), NULL, 10); }
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 734 "mon_parse.y"
    { (yyval.i) = strtol((yyvsp[(1) - (1)].str), NULL, 10); }
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 737 "mon_parse.y"
    { (yyval.i) = resolve_datatype(B_NUMBER,(yyvsp[(1) - (1)].str)); }
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 738 "mon_parse.y"
    { (yyval.i) = resolve_datatype(O_NUMBER,(yyvsp[(1) - (1)].str)); }
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 739 "mon_parse.y"
    { (yyval.i) = resolve_datatype(D_NUMBER,(yyvsp[(1) - (1)].str)); }
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 742 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 743 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 744 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 745 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 746 "mon_parse.y"
    { (yyval.i) = (yyvsp[(1) - (1)].i); }
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 754 "mon_parse.y"
    { (yyval.i) = 0;
                                                if ((yyvsp[(1) - (2)].str)) {
                                                    (monitor_cpu_for_memspace[default_memspace]->mon_assemble_instr)((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].i));
                                                } else {
                                                    new_cmd = 1;
                                                    asm_mode = 0;
                                                }
                                                opt_asm = 0;
                                              }
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 765 "mon_parse.y"
    { asm_mode = 0; }
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 768 "mon_parse.y"
    {
                        if ((yyvsp[(2) - (2)].i) > 0xffff) {
                          (yyval.i) = join_ints(ASM_ADDR_MODE_IMMEDIATE_24 | ((yyvsp[(2) - (2)].i) >> 16),((yyvsp[(2) - (2)].i) & 0xffff));
                        } else if ((yyvsp[(2) - (2)].i) > 0xff) {
                          (yyval.i) = join_ints(ASM_ADDR_MODE_IMMEDIATE_16,(yyvsp[(2) - (2)].i));
                        } else {
                          (yyval.i) = join_ints(ASM_ADDR_MODE_IMMEDIATE,(yyvsp[(2) - (2)].i));
                        }
                                       }
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 777 "mon_parse.y"
    { if ((yyvsp[(1) - (1)].i) < 0x100)
               (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE,(yyvsp[(1) - (1)].i));
             else
               (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE,(yyvsp[(1) - (1)].i));
           }
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 782 "mon_parse.y"
    { if ((yyvsp[(1) - (3)].i) < 0x100)
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE_X,(yyvsp[(1) - (3)].i));
                          else
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_X,(yyvsp[(1) - (3)].i));
                        }
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 787 "mon_parse.y"
    { if ((yyvsp[(1) - (3)].i) < 0x100)
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE_Y,(yyvsp[(1) - (3)].i));
                          else
                            (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_Y,(yyvsp[(1) - (3)].i));
                        }
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 792 "mon_parse.y"
    { if ((yyvsp[(2) - (6)].i) < 8)
                                                         (yyval.i) = join_ints((ASM_ADDR_MODE_ZERO_PAGE_BIT0_RELATIVE + (yyvsp[(2) - (6)].i)) | ((yyvsp[(4) - (6)].i) << 8),(yyvsp[(6) - (6)].i));
                                                   }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 795 "mon_parse.y"
    { if ((yyvsp[(2) - (4)].i) < 8)
                                                         (yyval.i) = join_ints(ASM_ADDR_MODE_ZERO_PAGE_BIT0 + (yyvsp[(2) - (4)].i),(yyvsp[(4) - (4)].i));
                                      }
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 798 "mon_parse.y"
    { if ((yyvsp[(2) - (3)].i) < 0x100)
                               (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT,(yyvsp[(2) - (3)].i));
                             else
                               (yyval.i) = join_ints(ASM_ADDR_MODE_ABS_INDIRECT,(yyvsp[(2) - (3)].i));
                           }
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 803 "mon_parse.y"
    { if ((yyvsp[(2) - (5)].i) < 0x100)
                                           (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT_X,(yyvsp[(2) - (5)].i));
                                         else
                                           (yyval.i) = join_ints(ASM_ADDR_MODE_ABS_INDIRECT_X,(yyvsp[(2) - (5)].i));
                                       }
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 809 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT_Y,(yyvsp[(2) - (5)].i)); }
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 811 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_INDIRECT_Z,(yyvsp[(2) - (5)].i)); }
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 813 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_STACK_RELATIVE_Y,(yyvsp[(2) - (7)].i)); }
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 814 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_BC,0); }
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 815 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_DE,0); }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 816 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_HL,0); }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 817 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_IX,0); }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 818 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_IY,0); }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 819 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IND_SP,0); }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 821 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_A,(yyvsp[(2) - (5)].i)); }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 823 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_HL,(yyvsp[(2) - (5)].i)); }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 825 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_IX,(yyvsp[(2) - (5)].i)); }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 827 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ABSOLUTE_IY,(yyvsp[(2) - (5)].i)); }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 828 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_IMPLIED,0); }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 829 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_ACCUMULATOR,0); }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 830 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_B,0); }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 831 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_C,0); }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 832 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_D,0); }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 833 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_E,0); }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 834 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_H,0); }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 835 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IXH,0); }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 836 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IYH,0); }
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 837 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_L,0); }
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 838 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IXL,0); }
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 839 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IYL,0); }
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 840 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_AF,0); }
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 841 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_BC,0); }
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 842 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_DE,0); }
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 843 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_HL,0); }
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 844 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IX,0); }
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 845 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_IY,0); }
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 846 "mon_parse.y"
    { (yyval.i) = join_ints(ASM_ADDR_MODE_REG_SP,0); }
    break;



/* Line 1464 of yacc.c  */
#line 4417 "mon_parse.c"
      default: break;
    }
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1684 of yacc.c  */
#line 850 "mon_parse.y"


void parse_and_execute_line(char *input)
{
   char *temp_buf;
   int i, rc;

   temp_buf = lib_malloc(strlen(input) + 3);
   strcpy(temp_buf,input);
   i = (int)strlen(input);
   temp_buf[i++] = '\n';
   temp_buf[i++] = '\0';
   temp_buf[i++] = '\0';

   make_buffer(temp_buf);
   if ( (rc =yyparse()) != 0) {
       mon_out("ERROR -- ");
       switch(rc) {
         case ERR_BAD_CMD:
           mon_out("Bad command:\n");
           break;
         case ERR_RANGE_BAD_START:
           mon_out("Bad first address in range:\n");
           break;
         case ERR_RANGE_BAD_END:
           mon_out("Bad second address in range:\n");
           break;
         case ERR_EXPECT_CHECKNUM:
           mon_out("Checkpoint number expected:\n");
           break;
         case ERR_EXPECT_END_CMD:
           mon_out("Unexpected token:\n");
           break;
         case ERR_MISSING_CLOSE_PAREN:
           mon_out("')' expected:\n");
           break;
         case ERR_INCOMPLETE_COMPARE_OP:
           mon_out("Compare operation missing an operand:\n");
           break;
         case ERR_EXPECT_FILENAME:
           mon_out("Expecting a filename:\n");
           break;
         case ERR_ADDR_TOO_BIG:
           mon_out("Address too large:\n");
           break;
         case ERR_IMM_TOO_BIG:
           mon_out("Immediate argument too large:\n");
           break;
         case ERR_EXPECT_STRING:
           mon_out("Expecting a string.\n");
           break;
         case ERR_UNDEFINED_LABEL:
           mon_out("Found an undefined label.\n");
           break;
         case ERR_EXPECT_DEVICE_NUM:
           mon_out("Expecting a device number.\n");
           break;
         case ERR_EXPECT_ADDRESS:
           mon_out("Expecting an address.\n");
           break;
         case ERR_ILLEGAL_INPUT:
         default:
           mon_out("Wrong syntax:\n");
       }
       mon_out("  %s\n", input);
       for (i = 0; i < last_len; i++)
           mon_out(" ");
       mon_out("  ^\n");
       asm_mode = 0;
       new_cmd = 1;
   }
   lib_free(temp_buf);
   free_buffer();
}

static int yyerror(char *s)
{
   fprintf(stderr, "ERR:%s\n", s);
   return 0;
}

static int resolve_datatype(unsigned guess_type, const char *num)
{
   /* FIXME: Handle cases when default type is non-numerical */
   if (default_radix == e_hexadecimal) {
       return strtol(num, NULL, 16);
   }

   if ((guess_type == D_NUMBER) || (default_radix == e_decimal)) {
       return strtol(num, NULL, 10);
   }

   if ((guess_type == O_NUMBER) || (default_radix == e_octal)) {
       return strtol(num, NULL, 8);
   }

   return strtol(num, NULL, 2);
}

/*
 * Resolve a character sequence containing 8 hex digits like "08001000". 
 * This could be a lazy version of "0800 1000". If the default radix is not
 * hexadecimal, we handle it like a ordinary number, in the latter case there
 * is only one number in the range.
 */
static int resolve_range(enum t_memspace memspace, MON_ADDR range[2], 
                         const char *num)
{
    char start[5];
    char end[5];
    long sa;

    range[1] = BAD_ADDR;

    switch (default_radix)
    {
    case e_hexadecimal:
        /* checked twice, but as the code must have exactly 8 digits: */
        if (strlen(num) == 8) {
            memcpy(start, num, 4);
            start[4] = '\0';
            memcpy(end, num + 4, 4);
            end[4] = '\0';
            sa = strtol(start, NULL, 16);
            range[1] = new_addr(memspace, strtol(end, NULL, 16));
        }
        else
            sa = strtol(num, NULL, 16);
        break;

    case e_decimal:
       sa = strtol(num, NULL, 10);
       break;

    case e_octal:
       sa = strtol(num, NULL, 8);
       break;

    default:
       sa = strtol(num, NULL, 2);
    }

    if (!CHECK_ADDR(sa))
        return ERR_ADDR_TOO_BIG;

    range[0] = new_addr(memspace, sa);
    return 0;
}

/* If we want 'quit' for OS/2 I couldn't leave the emulator by calling exit(0)
   So I decided to skip this (I think it's unnecessary for OS/2 */
static void mon_quit(void)
{
#ifdef OS2
    /* same as "quit" */
    exit_mon = 1; 
#else
    exit_mon = 2;
#endif
}


