/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 18

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS { /*defining all elements that can be found in a KIA file*/
	ERR_T,		/*  0: Error token */ // how to define in case?
	MNID_T,		/*  1: Method name identifier token (start: &) */ 
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */		
	EOS_T,		/*  9: End of statement (semicolon) */ 
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	FLO_T,		/* 13. Float literal token */ /* ADDED*/
	VAR_T,		/* 14. Variable token*/     
	PER_T,		/* 15. Period token*/
	QOUT_T,		/* 16. Single quote token*/
	UNDER_T,	/* 17. Underscore token*/
	

};

/* TO_DO: Define the list of keywords */
static str tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"FLO_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"VAR_T",
	"PER_T",
	"QOUT_T",
	"UNDER_T",
	
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT, OP_GTHEN, OP_LTHEN, OP_INC } RelOperator; 
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int intValue;				/* integer literal attribute (value) */
	int keywordIndex;			/* keyword index in the keyword table */
	int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float floatValue;				/* floating-point literal attribute (value) */
	kimsan_bytes idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	kimsan_bytes errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	kimsan_byte flags;			/* Flags information */
	union {
		int intValue;				/* Integer value */
		float floatValue;			/* Float value */
		str stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF


/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '#'
#define CHRCOL8 '&'
#define CHRCOL3 '\n'
#define CHRCOL6 '_'
#define CHRCOL4 '.'
#define CHRCOL5 "\'"
#define CHRCOL7 '('



/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		13
#define CHAR_CLASSES	9

/* TO_DO: Transition table - type of states defined in separate table */

static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
//     L(0),D(1)   C(2)  N(3)	P(4)  Q1(5)	U(6)	B1(7)	O(7)
//	   [A-z],[0-9]	#	 \n		 (.)	'     _		(      other
	
	{ 1,    8,    4,  ESNR, ESNR,  6,   ESNR,   ESNR,   ESNR		},		// S0: NOAS
	{ 1,    1,    3,    3,	  3,   3,    1,     2,		3		},			// S1: NOAS
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		},		// S2: ASNR (FUNCTION)
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		},		// S3: ASWR (KEYWORD/VARIABLE)
	{ 4,    4,    4,    5,    4,   4,	 4,     4,		4		},		// S4: NOAS
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		},		// S5: ASNR (COMMENT)
	{ 6,    6,    6,    6,    6,   7,	 6,     6,		6		},		// S6: NOAS
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		},		// S7: ASNR (STRING)
	{ 9,    8,    9,    9,    9,   9,	 9,     9,		9		},		// S8: ASNR (ES)
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		},			// S9: ASWR (LITERAL INT)
	{ ESNR, ESNR, ESNR, ESNR, 10,  ESNR, ESNR,  ESNR,	ESNR	},			// S9: ASWR (ER)
	{ 12,   11,   12,   12,   12,  12,	 12,    12,		12		},			// S9: ASWR (ER)
	{ FS,   FS,   FS,   FS,   FS,  FS,	 FS,    FS,		FS		}			// S9: ASWR (FLOAT)

};





/* Define accepting states types */
#define NOFS	0		/* not accepting state */ 
#define FSNR	1		/* accepting state with no retract */ 
#define FSWR	2		/* accepting state with retract */ 

/* TO_DO: Define list of acceptable states */
static int stateType[NUM_STATES] = {
	NOFS, // 00 
	NOFS, // 01 
	FSNR, // 02 (MID) - Methods 
	FSWR, // 03 (KEY) 
	NOFS, // 04 
	FSNR, // 05 (SL) 
	NOFS, // 06 
	FSNR, // 07 (COM) 
	NOFS, // 08 (Err1 - no retract) 
	FSWR,  // 09 (Err2 - retract) 
	NOFS, // 010
	NOFS, // 011
	FSWR  // 012(Err2 - retract)
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int			startScanner(BufferPointer psc_buf);
static int	nextClass(kimsan_bytes c);					/* character class function */
static int	nextState(int, kimsan_bytes);		/* state machine function */
kimsan_void			printScannerData(ScannerData scData);
Token				tokenizer(kimsan_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(str lexeme);

/* Declare accepting states functions */
Token funcSL	(str lexeme); // string function
Token funcIL	(str lexeme); // int function
Token funcID	(str lexeme); // method function
Token funcCMT   (str lexeme); // comment function
Token funcKEY	(str lexeme); // keyword and variable function
Token funcErr	(str lexeme); // error function


/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		// -		[00] 
	NULL,		// -		[01] 
	funcID,		// METHOD	[02] 
	funcKEY,	// VAR/KEY  [03] 
	NULL,		// -		[04] 
	funcCMT,	// COMMENT  [05] 
	NULL,		// -		[06] 
	funcSL,		// STRING	[07] 
	NULL,		// -		[08]
	funcIL,		// INT		[09] 
	NULL,		// -		[10]
	NULL,		// -		[11]
	funcIL		// FLOAT	[12] 
};


/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 13 //13

/* TO_DO: Define the list of keywords */
static str keywordTable[KWT_SIZE] = {
	"def",		// KW00 
	"while",	// KW01 
	"if",		// KW02 
	"elif",		// KW03 
	"else",		// KW04 
	"return",	// KW05 
	"import",	// KW06 
	"print",	// KW07 
	"try",		// KW08 
	"except",	// KW09
	"int",		// KW010
	"float",	// KW011
	"str"		// KW012

};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	kimsan_bytes indentationCharType;
	int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
