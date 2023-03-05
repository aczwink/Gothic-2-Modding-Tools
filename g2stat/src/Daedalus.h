#pragma once
//SJCLib
#include <SJCLib.h>
//Definitions
#define DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR 4
#define DAEDALUS_SYMBOL_INSTANCE_HELP "ÿINSTANCE_HELP"
//Definitions: External offsets
#define EXTERNAL_AI_OUTPUT 6901984
#define EXTERNAL_AI_OUTPUTSVM 6902640
#define EXTERNAL_AI_OUTPUTSVM_OVERLAY 6903184
#define EXTERNAL_AI_PLAYANI 6904112
#define EXTERNAL_AI_PRINTSCREEN 6873632
#define EXTERNAL_AI_REMOVEWEAPON 6912000
#define EXTERNAL_AI_STANDUP 6946176
#define EXTERNAL_AI_STOPFX 6861264
#define EXTERNAL_AI_STOPPROCESSINFOS 6843584
#define EXTERNAL_AI_TELEPORT 6854064
#define EXTERNAL_AI_USEITEMTOSTATE 6933840
#define EXTERNAL_AI_WAIT 6904928
#define EXTERNAL_CONCATSTRINGS 6872000
#define EXTERNAL_CREATEINVITEM 6891472
#define EXTERNAL_CREATEINVITEMS 6892816
#define EXTERNAL_DOC_CREATE 6835584
#define EXTERNAL_DOC_CREATEMAP 6835520
#define EXTERNAL_DOC_PRINTLINE 6837008
#define EXTERNAL_DOC_PRINTLINES 6837296
#define EXTERNAL_DOC_SETFONT 6836304
#define EXTERNAL_DOC_SETLEVEL 6836592
#define EXTERNAL_DOC_SETLEVELCOORDS 6836832
#define EXTERNAL_DOC_SETMARGINS 6836064
#define EXTERNAL_DOC_SETPAGE 6835760
#define EXTERNAL_DOC_SETPAGES 6835648
#define EXTERNAL_DOC_SHOW 6837584
#define EXTERNAL_EQUIPITEM 6895120
#define EXTERNAL_HLP_GETINSTANCEID 6957424
#define EXTERNAL_HLP_GETNPC 6922176
#define EXTERNAL_HLP_ISVALIDNPC 6922352
#define EXTERNAL_HLP_RANDOM 6957504
#define EXTERNAL_INTRODUCECHAPTER 6973072
#define EXTERNAL_INTTOSTRING 6871264
#define EXTERNAL_LOG_ADDENTRY 6877088
#define EXTERNAL_LOG_CREATETOPIC 6876752
#define EXTERNAL_LOG_SETTOPICSTATUS 6877376
#define EXTERNAL_MDL_APPLYOVERLAYMDS 6967024
#define EXTERNAL_MDL_APPLYOVERLAYMDSTIMED 6967680
#define EXTERNAL_MDL_SETMODELFATNESS 6971120
#define EXTERNAL_MDL_SETMODELSCALE 6970784
#define EXTERNAL_MDL_SETVISUAL 6965520
#define EXTERNAL_MDL_SETVISUALBODY 6966160
#define EXTERNAL_NPC_CHANGEATTRIBUTE 6896624
#define EXTERNAL_NPC_EXCHANGEROUTINE 6851840
#define EXTERNAL_NPC_GETBODYSTATE 6941056
#define EXTERNAL_NPC_GETDISTTOWP 6938080
#define EXTERNAL_NPC_GETLOOKATTARGET 6914864
#define EXTERNAL_NPC_GETTALENTSKILL 6887824
#define EXTERNAL_NPC_HASITEMS 6890640
#define EXTERNAL_NPC_ISDEAD 6896400
#define EXTERNAL_NPC_ISINFIGHTMODE 6885232
#define EXTERNAL_NPC_ISINSTATE 6881664
#define EXTERNAL_NPC_ISPLAYER 6935280
#define EXTERNAL_NPC_KNOWSINFO 6846032
#define EXTERNAL_NPC_PERCEIVEALL 6898224
#define EXTERNAL_NPC_REMOVEINVITEMS 6894512
#define EXTERNAL_NPC_SETATTITUDE 6896880
#define EXTERNAL_NPC_SETTALENTSKILL 6888080
#define EXTERNAL_NPC_SETTEMPATTITUDE 6897104
#define EXTERNAL_NPC_SETTOFIGHTMODE 6889664
#define EXTERNAL_NPC_SETTOFISTMODE 6889360
#define EXTERNAL_NPC_STOPANI 6855760
#define EXTERNAL_PLAYVIDEO 6813536
#define EXTERNAL_PLAYVIDEOEX 6813760
#define EXTERNAL_PRINT 6872400
#define EXTERNAL_PRINTDEBUG 6872656
#define EXTERNAL_PRINTSCREEN 6872912
#define EXTERNAL_SND_PLAY 6961472
#define EXTERNAL_TA_MIN 6848080
#define EXTERNAL_WLD_ASSIGNROOMTOGUILD 6880160
#define EXTERNAL_WLD_GETPLAYERPORTALGUILD 6879408
#define EXTERNAL_WLD_INSERTITEM 6862544
#define EXTERNAL_WLD_INSERTNPC 6857632
#define EXTERNAL_WLD_ISTIME 6972816
#define EXTERNAL_WLD_PLAYEFFECT 6860240
#define EXTERNAL_WLD_SETGUILDATTITUDE 6868864
#define EXTERNAL_WLD_SETMOBROUTINE 6856960
#define EXTERNAL_WLD_SETTIME 6852592
#define EXTERNAL_WLD_SPAWNNPCRANGE 6859248

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward Declarations
		class AAccessable;
		
		//Daedalus Alphabet
		enum EToken
		{
			TOKEN_ILLEGAL,
			TOKEN_END,
			TOKEN_WHITESPACE,
			TOKEN_LINEFEED,
			TOKEN_SINGLELINECOMMENT,
			TOKEN_MULTILINECOMMENT,
			TOKEN_IDENTIFIER,
			TOKEN_INTNUMBER,
			TOKEN_FLOATNUMBER,
			TOKEN_LITERAL,
			//keywords
			TOKEN_CLASS,
			TOKEN_CONST,
			TOKEN_ELSE,
			TOKEN_FLOAT,
			TOKEN_FUNC,
			TOKEN_IF,
			TOKEN_INSTANCE,
			TOKEN_INT,
			TOKEN_PROTOTYPE,
			TOKEN_RETURN,
			TOKEN_STRING,
			TOKEN_VAR,
			TOKEN_VOID,
			//operators
			TOKEN_ASSIGNMENT,
			TOKEN_BITWISEAND,
			TOKEN_BITWISEOR,
			TOKEN_BRACECLOSE,
			TOKEN_BRACEOPEN,
			TOKEN_COMMA,
			TOKEN_DIVIDE,
			TOKEN_DOT,
			TOKEN_EQUALS,
			TOKEN_GREATEROREQUAL,
			TOKEN_GREATERTHAN,
			TOKEN_LESSOREQUAL,
			TOKEN_LESSTHAN,
			TOKEN_LOGICALAND,
			TOKEN_LOGICALOR,
			TOKEN_MINUS,
			TOKEN_MINUSASSIGN,
			TOKEN_MULTIPLY,
			TOKEN_NOT,
			TOKEN_NOTEQUALS,
			TOKEN_PARENCLOSE,
			TOKEN_PARENOPEN,
			TOKEN_PLUS,
			TOKEN_PLUSASSIGN,
			TOKEN_SEMICOLON,
			TOKEN_SHIFTLEFT,
			TOKEN_SQUAREDBRACKETCLOSE,
			TOKEN_SQUAREDBRACKETOPEN,
		};
		
		//Abstract Syntax Tree
		//Forward Declarations
		enum EType;
		struct SConstValue;
		struct SConstValues;
		struct SExpression;
		struct SInstance;
		struct SLeftValue;
		struct SNames;
		struct SPrototype;
		struct SStatement;
		struct SStatements;
		struct SType;
		struct SVariable;
		struct SVariables;

		//Arguments
		struct SArguments
		{
			SType *pType;
			SJCLib::CString *pIdentifier;
			SArguments *pNext;
		};
		
		//ArrayIndex
		struct SArrayIndex
		{
			SJCLib::CWString *pFileName;
			uint32 lineNumber;
			bool isIdentifier;
			SJCLib::CString *pIdentifier;
			uint32 index;
		};
		
		//CallArgs
		struct SCallArgs
		{
			SExpression *pExpr;
			SCallArgs *pNext;
		};

		//Class
		struct SClass
		{
			SJCLib::CWString *pFilename;
			uint32 lineNumber;
			SJCLib::CString *pName;
			SVariables *pVariables;
		};

		//Constant
		struct SConstant
		{
			SJCLib::CWString *pFilename;
			uint32 lineNumber;
			SType *pType;
			SJCLib::CString *pName;
			SConstValue *pValue; //if not array
			SArrayIndex *pNArrayElements;
			SConstValues *pArray; //if is array
		};

		//ConstValue
		enum EConstantValueType
		{
			CONSTANTVALUETYPE_BITWISEOR,
			CONSTANTVALUETYPE_CONSTVALUES,
			CONSTANTVALUETYPE_DIVIDE,
			CONSTANTVALUETYPE_FLOAT,
			CONSTANTVALUETYPE_FUNC,
			CONSTANTVALUETYPE_IDENTIFIER,
			CONSTANTVALUETYPE_INT,
			CONSTANTVALUETYPE_MULTIPLY,
			CONSTANTVALUETYPE_PLUS,
			CONSTANTVALUETYPE_SHIFTLEFT,
			CONSTANTVALUETYPE_STRING,
		};

		struct SConstValue
		{
			EConstantValueType type;
			union
			{
				float f;
				int32 i;
				SJCLib::CString *pIdentifier;
				SJCLib::CString *pString;
				struct
				{
					SConstValue *pLeft;
					SConstValue *pRight;
				} binaryOp;
				SConstValue *pConstValue;
				SConstValues *pConstValues;
			} value;
		};

		//ConstValues
		struct SConstValues
		{
			SConstValue *pValue;
			SConstValues *pNext;
		};

		//ElseIfs
		struct SElseIfs
		{
			SExpression *pCondition;
			SStatements *pNestedStatements;
			SElseIfs *pNext;
		};

		//Expression
		enum EExpressionType
		{
			EXPRESSIONTYPE_BITWISEAND,
			EXPRESSIONTYPE_BITWISEOR,
			EXPRESSIONTYPE_CALL,
			EXPRESSIONTYPE_CONSTVALUE,
			EXPRESSIONTYPE_DIVIDE,
			EXPRESSIONTYPE_EQUALS,
			EXPRESSIONTYPE_GREATEROREQUAL,
			EXPRESSIONTYPE_GREATERTHAN,
			EXPRESSIONTYPE_LEFTVALUE,
			EXPRESSIONTYPE_LESSOREQUAL,
			EXPRESSIONTYPE_LESSTHAN,
			EXPRESSIONTYPE_LOGICALAND,
			EXPRESSIONTYPE_LOGICALOR,
			EXPRESSIONTYPE_MINUS,
			EXPRESSIONTYPE_MULTIPLY,
			EXPRESSIONTYPE_NEGATE,
			EXPRESSIONTYPE_NOTEQUALS,
			EXPRESSIONTYPE_PLUS,
			EXPRESSIONTYPE_UNARYMINUS,
		};

		struct SExpression
		{
			EExpressionType type;
			union
			{
				SConstValue *pConstValue;
				SLeftValue *pLeftValue;
				SExpression *pSubExpression;
				struct
				{
					SExpression *pLeft;
					SExpression *pRight;
				} binaryOp;
				struct
				{
					SJCLib::CString *pIdentifier;
					SCallArgs *pCallArgs;
				} call;
			} value;
		};

		//Functions
		struct SFunction
		{
			SJCLib::CWString *pFileName;
			uint32 lineNumber;
			EType returnType;
			SJCLib::CString *pName;
			SArguments *pArguments;
			SStatements *pStatements;
		};

		//Globals
		enum EGlobalType
		{
			GLOBALTYPE_CLASS,
			GLOBALTYPE_CONSTANT,
			GLOBALTYPE_FUNCTION,
			GLOBALTYPE_INSTANCE,
			GLOBALTYPE_PROTOTYPE,
			GLOBALTYPE_VARIABLE,
		};

		struct SGlobals
		{
			EGlobalType type;
			union
			{
				SClass *pClass;
				SConstant *pConstant;
				SFunction *pFunction;
				SInstance *pInstance;
				SPrototype *pPrototype;
				SVariable *pVariable;
			} value;
			SGlobals *pNext;
		};
		
		//LeftValue
		enum ELeftValueType
		{
			LEFTVALUETYPE_ARRAY,
			LEFTVALUETYPE_IDENTIFIER,
			LEFTVALUETYPE_MEMBER,
			LEFTVALUETYPE_MEMBERARRAY,
		};

		struct SLeftValue
		{
			uint32 lineNumber;
			ELeftValueType type;
			SJCLib::CString *pIdentifier;
			SJCLib::CString *pMemberIdentifier;
			SArrayIndex *pArrayIndex;
		};

		//Names
		struct SNames
		{
			SJCLib::CString *pName;
			SNames *pNext;
		};

		//Prototype
		struct SPrototype
		{
			SJCLib::CWString *pFileName;
			uint32 lineNumber;
			SJCLib::CString *pName;
			SJCLib::CString *pClassName;
			SStatements *pStatements;
		};
		
		//Semantic Value Definition
		enum ESemanticValueType
		{
			SEMANTICVALUETYPE_ARGUMENTS,
			SEMANTICVALUETYPE_ARRAYINDEX,
			SEMANTICVALUETYPE_CALLARGS,
			SEMANTICVALUETYPE_CLASS,
			SEMANTICVALUETYPE_CONSTANT,
			SEMANTICVALUETYPE_CONSTVALUE,
			SEMANTICVALUETYPE_CONSTVALUES,
			SEMANTICVALUETYPE_ELSEIFS,
			SEMANTICVALUETYPE_EXPR,
			SEMANTICVALUETYPE_FUNCTION,
			SEMANTICVALUETYPE_GLOBALS,
			SEMANTICVALUETYPE_INSTANCE,
			SEMANTICVALUETYPE_LEFTVALUE,
			SEMANTICVALUETYPE_NAMES,
			SEMANTICVALUETYPE_PROTOTYPE,
			SEMANTICVALUETYPE_RETURNVALUE,
			SEMANTICVALUETYPE_STATEMENT,
			SEMANTICVALUETYPE_STATEMENTS,
			SEMANTICVALUETYPE_STRING,
			SEMANTICVALUETYPE_TYPE,
			SEMANTICVALUETYPE_VARIABLE,
			SEMANTICVALUETYPE_VARIABLES,
		};

		struct SSemanticValue
		{
			ESemanticValueType type;
			uint32 lineNumber;
			union
			{
				SArguments *pArguments;
				SArrayIndex *pArrayIndex;
				SCallArgs *pCallArgs;
				SClass *pClass;
				SConstant *pConstant;
				SConstValue *pConstValue;
				SConstValues *pConstValues;
				SElseIfs *pElseIfs;
				SExpression *pExpr;
				SFunction *pFunction;
				SGlobals *pGlobal;
				SInstance *pInstance;
				SLeftValue *pLeftValue;
				SNames *pNames;
				SPrototype *pPrototype;
				SStatement *pStatement;
				SStatements *pStatements;
				SJCLib::CString *pStr;
				SType *pType;
				SVariable *pVariable;
				SVariables *pVariables;
				EType returnType;
			} value;
		};

		//Statement
		enum EStatementType
		{
			STATEMENTTYPE_ASSIGNEXPR,
			STATEMENTTYPE_CALL,
			STATEMENTTYPE_DECLARATION,
			STATEMENTTYPE_IF,
			STATEMENTTYPE_MINUSASSIGNEXPR,
			STATEMENTTYPE_PLUSASSIGNEXPR,
			STATEMENTTYPE_RETURN,
			STATEMENTTYPE_RETURNEXPR,
		};

		struct SStatement
		{
			EStatementType type;
			union
			{
				struct
				{
					SType *pType;
					SJCLib::CString *pIdentifier;
				} decl;
				struct
				{
					SLeftValue *pLeftValue;
					SExpression *pExpr;
				} assign;
				struct
				{
					SJCLib::CString *pFunctionName;
					SCallArgs *pArgs;
				} call;
				struct
				{
					SExpression *pConditionExpr;
					SStatements *pNestedStatements;
					SElseIfs *pElseIfs;
				} ifStm;
				SExpression *pExpr;
			} value;
		};

		//Statements
		struct SStatements
		{
			SStatement *pStatement;
			SStatements *pNext;
		};
		
		struct SType
		{
			EType type;
			SJCLib::CString *pIdentifier;
			bool isArray;
			uint32 nArrayElements;
		};

		//Variable
		struct SVariable
		{
			SType *pType;
			SJCLib::CString *pName;
			SNames *pNames; //if not an array
			SArrayIndex *pArraySize;
		};

		//Variables
		struct SVariables
		{
			SVariable *pVariable;
			SVariables *pNext;
		};

		/*//Enums

		//Forward Declarations
		enum EReturnValue;
		enum EType;
		struct SConstValue;
		struct SConstValues;
		struct SExpression;
		struct SInstance;
		struct SLeftValue;
		struct SNames;
		struct SPrototype;
		struct SStatements;
		struct SType;
		struct SVariable;
		struct SVariables;
		union UValue;
		class CDaedalusArray;
		class CFunction;

		//General
		union UValue
		{
			int32 i;
			float f;
			SJCLib::CString *pString;
			CDaedalusArray *pArray;
			Daedalus::CFunction *pFunction;
		};
		*/

		//Compiling stuff
		/*
		struct SInstanceData
		{
			uint32 programOffset;
			uint32 nOpcodes;
			SJCLib::CString className;
		};

		struct SVariableData
		{
			SJCLib::CString *pName;
			EType type;
			bool isArray;
			uint32 nArrayElements;
		};*/

		//Binary Daedalus
		enum EType //As stored in the ZenGine
		{
			DAEDALUS_TYPE_VOID, //0
			DAEDALUS_TYPE_FLOAT, //1
			DAEDALUS_TYPE_INT, //2
			DAEDALUS_TYPE_STRING, //3
			DAEDALUS_TYPE_CLASS, //4
			DAEDALUS_TYPE_FUNC, //5
			DAEDALUS_TYPE_PROTOTYPE, //6
			DAEDALUS_TYPE_INSTANCE //7
		};
		
		union UValue
		{
			float32 f;
			int32 i;
			SJCLib::CString *pStr;
		};

		union USymbolData
		{
			UValue *pData;
			uint32 classOffset;
			uint32 programOffset;
		};
		
		struct SSymbol
		{
			SJCLib::CString name;
			uint32 offSizeRet; //offset if isClassVar, size if class, returntype if func
			uint16 nEntries;
			EType type;
			bool isClassVar;
			USymbolData data;
			Daedalus::AAccessable *pCurrentInstance; //only valid if this symbol is an instance
		};

		struct SExternalInfo
		{
			SSymbol external;
			SSymbol args[8];
		};

		//Functions
		SJCLib::CString ValueToString(const SConstant &refConstant);
		SJCLib::CString ValueToString(const SConstValue &refConstValue, EType type);
		SJCLib::CString ToString(const SType &refType);
		SJCLib::CString ToString(const SFunction &refFunc);
		//SJCLib::CString ToString(UValue value, const SType &refType);
	}
}