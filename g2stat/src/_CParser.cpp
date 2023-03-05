/*
//Class Header
#include "CParser.h"
//Global
#include <iostream>
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Parser Tables
#include "DaedalusParserTables.h"

//Constructor
CParser::CParser(const ICallback *pCallback) : CLALR1Parser<EToken, SSemanticValue>(NUMBER_OF_ALPHABET_ELEMENTS, NUMBER_OF_NONTERMINALS, actionTable, reductionRuleLengthTable, reductionRuleLeftSideTable, gotoTable)
{
	this->pCallback = pCallback;
}

//Destructor
CParser::~CParser()
{
	this->Release();
}

//Private Functions
void CParser::OnPutToken(const EToken &refToken, const CString &refString, SSemanticValue &refOutput)
{
	switch(refToken)
	{
	case TOKEN_INSTANCE:
		{
			refOutput.lineNumber = this->lexer.GetLineNumber();
		}
		break;
	case TOKEN_IDENTIFIER:
	case TOKEN_INTNUMBER:
	case TOKEN_FLOATNUMBER:
	case TOKEN_LITERAL:
		{
			refOutput.type = SEMANTICVALUETYPE_STRING;
			refOutput.value.pStr = new CString;
			*refOutput.value.pStr = refString;
			refOutput.lineNumber = this->lexer.GetLineNumber();
			
			this->rawSemanticValues.Insert(refOutput.value.pStr);
		}
		break;
	}
}

void CParser::OnReduce(int32 reductionRule, SSemanticValue &refOutput)
{
	SSemanticValue gpv; //general purpose variable
	
	MemZero(&refOutput, sizeof(refOutput));
	
	switch(reductionRule)
	{
	case 2:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
		}
		break;
	case 3:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
			
			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_CONSTANT;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pConstant = gpv.value.pConstant;
		}
		break;
	case 4:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;

			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_CLASS;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pClass = gpv.value.pClass;
		}
		break;
	case 5:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
			
			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_FUNCTION;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pFunction = gpv.value.pFunction;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;
		}
		break;
	case 6:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
			
			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_INSTANCE;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pInstance = gpv.value.pInstance;
		}
		break;
	case 7:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
			
			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_PROTOTYPE;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pPrototype = gpv.value.pPrototype;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;
		}
		break;
	case 8:
		{
			refOutput.type = SEMANTICVALUETYPE_GLOBALS;
			
			refOutput.value.pGlobal = (SGlobals *)this->MemAlloc(sizeof(*refOutput.value.pGlobal));
			refOutput.value.pGlobal->type = GLOBALTYPE_VARIABLE;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pGlobal->value.pVariable = gpv.value.pVariable;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pGlobal->pNext = gpv.value.pGlobal;
		}
		break;
	case 9:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTANT;
			refOutput.value.pConstant = (SConstant *)this->MemAlloc(sizeof(*refOutput.value.pConstant));

			refOutput.value.pConstant->pFilename = this->pFileName;
			
			this->GetSemanticValue(4, gpv);
			refOutput.value.pConstant->pType = gpv.value.pType;
			refOutput.value.pConstant->pType->isArray = false;

			this->GetSemanticValue(3, gpv);
			refOutput.value.pConstant->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			refOutput.value.pConstant->lineNumber = gpv.lineNumber;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pConstant->pValue = gpv.value.pConstValue;
		}
		break;
	case 10:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTANT;
			refOutput.value.pConstant = (SConstant *)this->MemAlloc(sizeof(*refOutput.value.pConstant));

			refOutput.value.pConstant->pFilename = this->pFileName;
			
			this->GetSemanticValue(9, gpv);
			refOutput.value.pConstant->pType = gpv.value.pType;
			refOutput.value.pConstant->pType->isArray = true;
			
			this->GetSemanticValue(8, gpv);
			refOutput.value.pConstant->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			refOutput.value.pConstant->lineNumber = gpv.lineNumber;

			this->GetSemanticValue(6, gpv);
			refOutput.value.pConstant->pNArrayElements = gpv.value.pArrayIndex;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstant->pArray = gpv.value.pConstValues;
		}
		break;
	case 11:
		{
			refOutput.type = SEMANTICVALUETYPE_CLASS;

			refOutput.value.pClass = (SClass *)this->MemAlloc(sizeof(*refOutput.value.pClass));

			refOutput.value.pClass->pFilename = this->pFileName;

			this->GetSemanticValue(4, gpv);
			refOutput.value.pClass->pName = gpv.value.pStr;
			refOutput.value.pClass->lineNumber = gpv.lineNumber;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(2, gpv);
			refOutput.value.pClass->pVariables = gpv.value.pVariables;
		}
		break;
	case 12:
		{
			refOutput.type = SEMANTICVALUETYPE_FUNCTION;

			refOutput.value.pFunction = (SFunction *)this->MemAlloc(sizeof(*refOutput.value.pFunction));

			refOutput.value.pFunction->pFileName = this->pFileName;
			
			this->GetSemanticValue(9, gpv);
			refOutput.value.pFunction->lineNumber = gpv.lineNumber;

			this->GetSemanticValue(8, gpv);
			refOutput.value.pFunction->returnType = gpv.value.returnType;

			this->GetSemanticValue(7, gpv);
			refOutput.value.pFunction->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(5, gpv);
			refOutput.value.pFunction->pArguments = gpv.value.pArguments;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pFunction->pStatements = gpv.value.pStatements;
		}
		break;
	case 13:
		{
			refOutput.type = SEMANTICVALUETYPE_INSTANCE;
			refOutput.value.pInstance = (SInstance *)this->MemAlloc(sizeof(*refOutput.value.pInstance));

			refOutput.value.pInstance->isGlobalInstance = true;
			refOutput.value.pInstance->pFileName = this->pFileName;

			this->GetSemanticValue(5, gpv);
			refOutput.value.pInstance->lineNumber = gpv.lineNumber;
			
			this->GetSemanticValue(4, gpv);
			refOutput.value.pInstance->pNames = gpv.value.pNames;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pInstance->pClassName = gpv.value.pStr;
			refOutput.value.pInstance->pPrototypeName = NULL;
			
			refOutput.value.pInstance->pStatements = NULL;
		}
		break;
	case 14:
		{
			refOutput.type = SEMANTICVALUETYPE_INSTANCE;
			refOutput.value.pInstance = (SInstance *)this->MemAlloc(sizeof(*refOutput.value.pInstance));

			refOutput.value.pInstance->isGlobalInstance = false;
			refOutput.value.pInstance->pFileName = this->pFileName;

			this->GetSemanticValue(8, gpv);
			refOutput.value.pInstance->lineNumber = gpv.lineNumber;
			
			this->GetSemanticValue(7, gpv);
			refOutput.value.pInstance->pNames = gpv.value.pNames;

			this->GetSemanticValue(5, gpv);
			refOutput.value.pInstance->pClassName = gpv.value.pStr;
			refOutput.value.pInstance->pPrototypeName = NULL;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pInstance->pStatements = gpv.value.pStatements;
		}
		break;
	case 15:
		{
			refOutput.type = SEMANTICVALUETYPE_PROTOTYPE;

			refOutput.value.pPrototype = (SPrototype *)this->MemAlloc(sizeof(*refOutput.value.pPrototype));

			refOutput.value.pPrototype->pFileName = this->pFileName;
			
			this->GetSemanticValue(7, gpv);
			refOutput.value.pPrototype->pName = gpv.value.pStr;
			refOutput.value.pPrototype->lineNumber = gpv.lineNumber;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(5, gpv);
			refOutput.value.pPrototype->pClassName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pPrototype->pStatements = gpv.value.pStatements;
		}
		break;
	case 16:
		{
			refOutput.type = SEMANTICVALUETYPE_TYPE;
			refOutput.value.pType = (SType *)this->MemAlloc(sizeof(*refOutput.value.pType));

			refOutput.value.pType->isArray = false;
			refOutput.value.pType->nArrayElements = 0;
			refOutput.value.pType->pIdentifier = NULL;
			refOutput.value.pType->type = DAEDALUS_TYPE_FLOAT;
		}
		break;
	case 17:
		{
			refOutput.type = SEMANTICVALUETYPE_TYPE;
			refOutput.value.pType = (SType *)this->MemAlloc(sizeof(*refOutput.value.pType));

			refOutput.value.pType->isArray = false;
			refOutput.value.pType->nArrayElements = 0;
			refOutput.value.pType->pIdentifier = NULL;
			refOutput.value.pType->type = DAEDALUS_TYPE_FUNC;
		}
		break;
	case 18:
		{
			refOutput.type = SEMANTICVALUETYPE_TYPE;
			refOutput.value.pType = (SType *)this->MemAlloc(sizeof(*refOutput.value.pType));

			refOutput.value.pType->isArray = false;
			refOutput.value.pType->nArrayElements = 0;
			refOutput.value.pType->pIdentifier = NULL;
			refOutput.value.pType->type = DAEDALUS_TYPE_INT;
		}
		break;
	case 19:
		{
			refOutput.type = SEMANTICVALUETYPE_TYPE;
			refOutput.value.pType = (SType *)this->MemAlloc(sizeof(*refOutput.value.pType));

			refOutput.value.pType->isArray = false;
			refOutput.value.pType->nArrayElements = 0;
			refOutput.value.pType->pIdentifier = NULL;
			refOutput.value.pType->type = DAEDALUS_TYPE_STRING;
		}
		break;
	case 20:
		{
			refOutput.type = SEMANTICVALUETYPE_TYPE;
			refOutput.value.pType = (SType *)this->MemAlloc(sizeof(*refOutput.value.pType));

			refOutput.value.pType->isArray = false;
			refOutput.value.pType->nArrayElements = 0;
			refOutput.value.pType->type = DAEDALUS_TYPE_CLASS;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pType->pIdentifier = gpv.value.pStr;
		}
		break;
	case 21:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_IDENTIFIER;
			refOutput.value.pConstValue->value.pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 22:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_FLOAT;
			refOutput.value.pConstValue->value.f = gpv.value.pStr->ToFloat();
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 23:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_INT;
			refOutput.value.pConstValue->value.i = (int32)gpv.value.pStr->ToInt64();
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 24:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_INT;
			refOutput.value.pConstValue->value.i = (int32)-gpv.value.pStr->ToInt64();
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 25:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_STRING;
			refOutput.value.pConstValue->value.pString = gpv.value.pStr;
			//this->rawSemanticValues.Delete(gpv.value.pStr);
		}
		break;
	case 26:
		{
			this->GetSemanticValue(1, gpv);
			refOutput = gpv;
		}
		break;
	case 27:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_CONSTVALUES;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pConstValue->value.pConstValues = gpv.value.pConstValues;
		}
		break;
	case 28:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_PLUS;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValue->value.binaryOp.pLeft = gpv.value.pConstValue;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValue->value.binaryOp.pRight = gpv.value.pConstValue;
		}
		break;
	case 29:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_MULTIPLY;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValue->value.binaryOp.pLeft = gpv.value.pConstValue;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValue->value.binaryOp.pRight = gpv.value.pConstValue;
		}
		break;
	case 30:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_DIVIDE;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValue->value.binaryOp.pLeft = gpv.value.pConstValue;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValue->value.binaryOp.pRight = gpv.value.pConstValue;
		}
		break;
	case 31:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_SHIFTLEFT;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValue->value.binaryOp.pLeft = gpv.value.pConstValue;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValue->value.binaryOp.pRight = gpv.value.pConstValue;
		}
		break;
	case 32:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_BITWISEOR;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValue->value.binaryOp.pLeft = gpv.value.pConstValue;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValue->value.binaryOp.pRight = gpv.value.pConstValue;
		}
		break;
	case 33:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUES;
			refOutput.value.pConstValues = (SConstValues *)this->MemAlloc(sizeof(*refOutput.value.pConstValues));
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValues->pValue = gpv.value.pConstValue;
			
			refOutput.value.pConstValues->pNext = NULL;
		}
		break;
	case 34:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUES;
			refOutput.value.pConstValues = (SConstValues *)this->MemAlloc(sizeof(*refOutput.value.pConstValues));

			this->GetSemanticValue(0, gpv);
			refOutput.value.pConstValues->pNext = gpv.value.pConstValues;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pConstValues->pValue = gpv.value.pConstValue;
		}
		break;
	case 35:
		{
			refOutput.type = SEMANTICVALUETYPE_VARIABLES;
		}
		break;
	case 36:
		{
			refOutput.type = SEMANTICVALUETYPE_VARIABLES;
			refOutput.value.pVariables = (SVariables *)this->MemAlloc(sizeof(*refOutput.value.pVariables));

			this->GetSemanticValue(0, gpv);
			refOutput.value.pVariables->pNext = gpv.value.pVariables;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pVariables->pVariable = gpv.value.pVariable;
		}
		break;
	case 37:
		{
			refOutput.type = SEMANTICVALUETYPE_VARIABLE;
			refOutput.value.pVariable = (SVariable *)this->MemAlloc(sizeof(*refOutput.value.pVariable));
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pVariable->pType = gpv.value.pType;
			refOutput.value.pVariable->pType->isArray = false;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pVariable->pNames = gpv.value.pNames;
		}
		break;
	case 38:
		{
			refOutput.type = SEMANTICVALUETYPE_VARIABLE;
			refOutput.value.pVariable = (SVariable *)this->MemAlloc(sizeof(*refOutput.value.pVariable));
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pVariable->pArraySize = gpv.value.pArrayIndex;

			this->GetSemanticValue(4, gpv);
			refOutput.value.pVariable->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(5, gpv);
			refOutput.value.pVariable->pType = gpv.value.pType;
			refOutput.value.pVariable->pType->isArray = true;
		}
		break;
	case 39:
		{
			this->GetSemanticValue(0, gpv);

			refOutput.type = SEMANTICVALUETYPE_NAMES;
			refOutput.value.pNames = (SNames *)this->MemAlloc(sizeof(*refOutput.value.pNames));
			
			refOutput.value.pNames->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			refOutput.value.pNames->pNext = NULL;
		}
		break;
	case 40:
		{
			refOutput.type = SEMANTICVALUETYPE_NAMES;
			refOutput.value.pNames = (SNames *)this->MemAlloc(sizeof(*refOutput.value.pNames));

			this->GetSemanticValue(2, gpv);
			refOutput.value.pNames->pName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(0, gpv);
			refOutput.value.pNames->pNext = gpv.value.pNames;
		}
		break;
	case 41:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENTS;
		}
		break;
	case 42:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENTS;

			refOutput.value.pStatements = (SStatements *)this->MemAlloc(sizeof(*refOutput.value.pStatements));

			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatements->pStatement = gpv.value.pStatement;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pStatements->pNext = gpv.value.pStatements;
		}
		break;
	case 43:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_DECLARATION;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pStatement->value.decl.pType = gpv.value.pType;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatement->value.decl.pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 44:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;

			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_ASSIGNEXPR;

			this->GetSemanticValue(3, gpv);
			refOutput.value.pStatement->value.assign.pLeftValue = gpv.value.pLeftValue;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatement->value.assign.pExpr = gpv.value.pExpr;
		}
		break;
	case 45:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_MINUSASSIGNEXPR;
			
			this->GetSemanticValue(3, gpv);
			refOutput.value.pStatement->value.assign.pLeftValue = gpv.value.pLeftValue;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatement->value.assign.pExpr = gpv.value.pExpr;
		}
		break;
	case 46:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_PLUSASSIGNEXPR;
			
			this->GetSemanticValue(3, gpv);
			refOutput.value.pStatement->value.assign.pLeftValue = gpv.value.pLeftValue;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatement->value.assign.pExpr = gpv.value.pExpr;
		}
		break;
	case 47:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_CALL;
			
			this->GetSemanticValue(4, gpv);
			refOutput.value.pStatement->value.call.pFunctionName = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pStatement->value.call.pArgs = gpv.value.pCallArgs;
		}
		break;
	case 48:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_IF;
			
			this->GetSemanticValue(4, gpv);
			refOutput.value.pStatement->value.ifStm.pConditionExpr = gpv.value.pExpr;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pStatement->value.ifStm.pNestedStatements = gpv.value.pStatements;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pStatement->value.ifStm.pElseIfs = gpv.value.pElseIfs;
		}
		break;
	case 49:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_RETURN;
		}
		break;
	case 50:
		{
			refOutput.type = SEMANTICVALUETYPE_STATEMENT;
			
			refOutput.value.pStatement = (SStatement *)this->MemAlloc(sizeof(*refOutput.value.pStatement));
			refOutput.value.pStatement->type = STATEMENTTYPE_RETURNEXPR;

			this->GetSemanticValue(1, gpv);
			refOutput.value.pStatement->value.pExpr = gpv.value.pExpr;
		}
		break;
	case 51:
		{
			this->GetSemanticValue(1, gpv);
			
			this->pCallback->OnWarning(DAEDALUS_WARNING_USELESS_STATEMENT, this->pFileName->ToCString() + ':' + CString(gpv.lineNumber));
		}
		break;
	case 52:
		{
			this->GetSemanticValue(3, gpv);
			
			this->pCallback->OnWarning(DAEDALUS_WARNING_USELESS_STATEMENT, this->pFileName->ToCString() + ':' + CString(gpv.value.pLeftValue->lineNumber));
		}
		break;
	case 53:
		{
			refOutput.type = SEMANTICVALUETYPE_LEFTVALUE;
			
			refOutput.value.pLeftValue = (SLeftValue *)this->MemAlloc(sizeof(*refOutput.value.pLeftValue));
			
			refOutput.value.pLeftValue->type = LEFTVALUETYPE_IDENTIFIER;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pLeftValue->lineNumber = gpv.lineNumber;
			refOutput.value.pLeftValue->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 54:
		{
			refOutput.type = SEMANTICVALUETYPE_LEFTVALUE;
			
			refOutput.value.pLeftValue = (SLeftValue *)this->MemAlloc(sizeof(*refOutput.value.pLeftValue));
			
			refOutput.value.pLeftValue->type = LEFTVALUETYPE_MEMBER;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pLeftValue->lineNumber = gpv.lineNumber;
			refOutput.value.pLeftValue->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pLeftValue->pMemberIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 55:
		{
			refOutput.type = SEMANTICVALUETYPE_LEFTVALUE;
			
			refOutput.value.pLeftValue = (SLeftValue *)this->MemAlloc(sizeof(*refOutput.value.pLeftValue));
			
			refOutput.value.pLeftValue->type = LEFTVALUETYPE_MEMBERARRAY;
			
			this->GetSemanticValue(5, gpv);
			refOutput.value.pLeftValue->lineNumber = gpv.lineNumber;
			refOutput.value.pLeftValue->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(3, gpv);
			refOutput.value.pLeftValue->pMemberIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pLeftValue->pArrayIndex = gpv.value.pArrayIndex;
		}
		break;
	case 56:
		{
			refOutput.type = SEMANTICVALUETYPE_LEFTVALUE;

			refOutput.value.pLeftValue = (SLeftValue *)this->MemAlloc(sizeof(*refOutput.value.pLeftValue));

			refOutput.value.pLeftValue->type = LEFTVALUETYPE_ARRAY;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pLeftValue->pArrayIndex = gpv.value.pArrayIndex;

			this->GetSemanticValue(3, gpv);
			refOutput.value.pLeftValue->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(4, gpv);
			refOutput.value.pLeftValue->lineNumber = gpv.lineNumber;
		}
		break;
	case 57:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_CONSTVALUE;
			refOutput.value.pExpr->value.pConstValue = gpv.value.pConstValue;
		}
		break;
	case 58:
		{
			this->GetSemanticValue(0, gpv);
			
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_LEFTVALUE;
			refOutput.value.pExpr->value.pLeftValue = gpv.value.pLeftValue;
		}
		break;
	case 59:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_NEGATE;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.pSubExpression = gpv.value.pExpr;
		}
		break;
	case 60:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_UNARYMINUS;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.pSubExpression = gpv.value.pExpr;
		}
		break;
	case 61:
		{
			this->GetSemanticValue(0, gpv);
			refOutput = gpv;
		}
		break;
	case 62:
		{
			this->GetSemanticValue(1, gpv);
			refOutput = gpv;
		}
		break;
	case 63:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_PLUS;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 64:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_MINUS;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 65:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_MULTIPLY;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 66:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_DIVIDE;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 67:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_EQUALS;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 68:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_NOTEQUALS;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 69:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_LESSTHAN;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 70:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_LESSOREQUAL;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 71:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_GREATERTHAN;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 72:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_GREATEROREQUAL;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 73:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_LOGICALAND;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 74:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_LOGICALOR;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 75:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_BITWISEAND;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 76:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_BITWISEOR;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pExpr->value.binaryOp.pLeft = gpv.value.pExpr;
			
			this->GetSemanticValue(0, gpv);
			refOutput.value.pExpr->value.binaryOp.pRight = gpv.value.pExpr;
		}
		break;
	case 77:
		{
			refOutput.type = SEMANTICVALUETYPE_EXPR;
			
			refOutput.value.pExpr = (SExpression *)this->MemAlloc(sizeof(*refOutput.value.pExpr));
			refOutput.value.pExpr->type = EXPRESSIONTYPE_CALL;

			this->GetSemanticValue(3, gpv);
			refOutput.value.pExpr->value.call.pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pExpr->value.call.pCallArgs = gpv.value.pCallArgs;
		}
		break;
	case 78:
		{
			refOutput.type = SEMANTICVALUETYPE_RETURNVALUE;
			refOutput.value.returnType = DAEDALUS_TYPE_VOID;
		}
		break;
	case 79:
		{
			refOutput.type = SEMANTICVALUETYPE_RETURNVALUE;
			refOutput.value.returnType = DAEDALUS_TYPE_INT;
		}
		break;
	case 80:
		{
			refOutput.type = SEMANTICVALUETYPE_RETURNVALUE;
			refOutput.value.returnType = DAEDALUS_TYPE_STRING;
		}
		break;
	case 81:
		{
			refOutput.type = SEMANTICVALUETYPE_ARGUMENTS;
			refOutput.value.pArguments = NULL;
		}
		break;
	case 82:
		{
			refOutput.type = SEMANTICVALUETYPE_ARGUMENTS;
			refOutput.value.pArguments = (SArguments *)this->MemAlloc(sizeof(*refOutput.value.pArguments));

			this->GetSemanticValue(1, gpv);
			refOutput.value.pArguments->pType = gpv.value.pType;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pArguments->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			refOutput.value.pArguments->pNext = NULL;
		}
		break;
	case 83:
		{
			refOutput.type = SEMANTICVALUETYPE_ARGUMENTS;
			refOutput.value.pArguments = (SArguments *)this->MemAlloc(sizeof(*refOutput.value.pArguments));

			this->GetSemanticValue(3, gpv);
			refOutput.value.pArguments->pType = gpv.value.pType;

			this->GetSemanticValue(2, gpv);
			refOutput.value.pArguments->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);

			this->GetSemanticValue(0, gpv);
			refOutput.value.pArguments->pNext = gpv.value.pArguments;
		}
		break;
	case 84:
		{
			refOutput.type = SEMANTICVALUETYPE_CALLARGS;
		}
		break;
	case 85:
		{
			refOutput.type = SEMANTICVALUETYPE_CALLARGS;

			refOutput.value.pCallArgs = (SCallArgs *)this->MemAlloc(sizeof(*refOutput.value.pCallArgs));

			this->GetSemanticValue(0, gpv);
			refOutput.value.pCallArgs->pExpr = gpv.value.pExpr;

			refOutput.value.pCallArgs->pNext = NULL;
		}
		break;
	case 86:
		{
			refOutput.type = SEMANTICVALUETYPE_CALLARGS;

			refOutput.value.pCallArgs = (SCallArgs *)this->MemAlloc(sizeof(*refOutput.value.pCallArgs));

			this->GetSemanticValue(2, gpv);
			refOutput.value.pCallArgs->pExpr = gpv.value.pExpr;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pCallArgs->pNext = gpv.value.pCallArgs;
		}
		break;
	case 87:
		{
			refOutput.type = SEMANTICVALUETYPE_ELSEIFS;
		}
		break;
	case 88:
		{
			refOutput.type = SEMANTICVALUETYPE_ELSEIFS;
		}
		break;
	case 89:
		{
			refOutput.type = SEMANTICVALUETYPE_ELSEIFS;

			refOutput.value.pElseIfs = (SElseIfs *)this->MemAlloc(sizeof(*refOutput.value.pElseIfs));

			this->GetSemanticValue(2, gpv);
			refOutput.value.pElseIfs->pNestedStatements = gpv.value.pStatements;

			refOutput.value.pElseIfs->pCondition = NULL;
			refOutput.value.pElseIfs->pNext = NULL;
		}
		break;
	case 90:
		{
			refOutput.type = SEMANTICVALUETYPE_ELSEIFS;

			refOutput.value.pElseIfs = (SElseIfs *)this->MemAlloc(sizeof(*refOutput.value.pElseIfs));

			this->GetSemanticValue(4, gpv);
			refOutput.value.pElseIfs->pCondition = gpv.value.pExpr;
			
			this->GetSemanticValue(2, gpv);
			refOutput.value.pElseIfs->pNestedStatements = gpv.value.pStatements;

			this->GetSemanticValue(0, gpv);
			refOutput.value.pElseIfs->pNext = gpv.value.pElseIfs;
		}
		break;
	case 91:
		{
			refOutput.type = SEMANTICVALUETYPE_ARRAYINDEX;
			
			refOutput.value.pArrayIndex = (SArrayIndex *)this->MemAlloc(sizeof(*refOutput.value.pArrayIndex));

			this->GetSemanticValue(0, gpv);

			refOutput.value.pArrayIndex->pFileName = this->pFileName;
			refOutput.value.pArrayIndex->lineNumber = gpv.lineNumber;
			
			refOutput.value.pArrayIndex->isIdentifier = false;
			refOutput.value.pArrayIndex->index = (uint32)gpv.value.pStr->ToUInt64();
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	case 92:
		{
			refOutput.type = SEMANTICVALUETYPE_ARRAYINDEX;
			
			refOutput.value.pArrayIndex = (SArrayIndex *)this->MemAlloc(sizeof(*refOutput.value.pArrayIndex));

			this->GetSemanticValue(0, gpv);
			refOutput.value.pArrayIndex->pFileName = this->pFileName;
			refOutput.value.pArrayIndex->lineNumber = gpv.lineNumber;

			refOutput.value.pArrayIndex->isIdentifier = true;
			refOutput.value.pArrayIndex->pIdentifier = gpv.value.pStr;
			//this->asd.Delete(gpv.value.pStr);
		}
		break;
	default:
		ASSERT(0);
	}
}

//Public Functions
void *CParser::MemAlloc(uint32 size)
{
	void *pMem;

	pMem = malloc(size);
	this->treeNodes.Insert(pMem);

	return pMem;
}

void CParser::MemFree(SArrayIndex *pArrayIdx)
{
	ASSERT(this->treeNodes.Contains(pArrayIdx));

	if(pArrayIdx->isIdentifier)
		this->MemFree(pArrayIdx->pIdentifier);
	
	free(pArrayIdx);
	this->treeNodes.Delete(pArrayIdx);
}

void CParser::MemFree(SConstValue *pConstValue)
{
	ASSERT(this->treeNodes.Contains(pConstValue));
	
	switch(pConstValue->type)
	{
	case CONSTANTVALUETYPE_INT:
		break;
	default:
		ASSERT(0);
	}
	
	free(pConstValue);
	this->treeNodes.Delete(pConstValue);
}

void CParser::MemFree(CString *pStr)
{
	ASSERT(this->rawSemanticValues.Contains(pStr));
	
	delete pStr;
	this->rawSemanticValues.Delete(pStr);
}

bool CParser::Parse(const byte *pInput, CWString filename)
{
	this->pFileName = this->garbageCollector.AllocWideString();
	*this->pFileName = filename;
	
	this->lexer.Init(pInput);

	return CLALR1Parser<Daedalus::EToken, Daedalus::SSemanticValue>::Parse(this->lexer);
}

void CParser::Release()
{
	foreach(it, this->rawSemanticValues)
	{
		delete it.GetValue();
	}
	this->rawSemanticValues.Release();

	foreach(it, this->treeNodes)
	{
		free(it.GetValue());
	}
	this->treeNodes.Release();
}
*/