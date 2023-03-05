//Class Header
#include "CParser.h"
//Global
#include <iostream>
//Local
#include "AST\AInstance.h"
#include "AST\CArguments.h"
#include "AST\CArrayIndex.h"
#include "AST\CAssignStatement.h"
#include "AST\CBitwiseAndExpression.h"
#include "AST\CBitwiseOrExpression.h"
#include "AST\CCallExpression.h"
#include "AST\CCallStatement.h"
#include "AST\CClass.h"
#include "AST\CConstant.h"
#include "AST\CConstantArray.h"
#include "AST\CDeclarationStatement.h"
#include "AST\CDivideExpression.h"
#include "AST\CElseIfs.h"
#include "AST\CEqualsExpression.h"
#include "AST\CExprList.h"
#include "AST\CFloatExpression.h"
#include "AST\CFunction.h"
#include "AST\CGreaterThanExpression.h"
#include "AST\CGreaterThanOrEqualToExpression.h"
#include "AST\CIdentifierList.h"
#include "AST\CIfStatement.h"
#include "AST\CInstanceList.h"
#include "AST\CIntExpression.h"
#include "AST\CLeftValueArray.h"
#include "AST\CLeftValueIdentifier.h"
#include "AST\CLeftValueMember.h"
#include "AST\CLeftValueMemberArray.h"
#include "AST\CLessThanExpression.h"
#include "AST\CLessThanOrEqualToExpression.h"
#include "AST\CLogicalAndExpression.h"
#include "AST\CLogicalOrExpression.h"
#include "AST\CMinusAssignStatement.h"
#include "AST\CMinusExpression.h"
#include "AST\CMultiplyExpression.h"
#include "AST\CNotEqualsExpression.h"
#include "AST\CNotExpression.h"
#include "AST\CPlusAssignStatement.h"
#include "AST\CPlusExpression.h"
#include "AST\CPrototype.h"
#include "AST\CReturnStatement.h"
#include "AST\CShiftLeftExpression.h"
#include "AST\CStatements.h"
#include "AST\CStringExpression.h"
#include "AST\CSubtractExpression.h"
#include "AST\CTextNode.h"
#include "AST\CVariable.h"
#include "AST\CVariableArray.h"
#include "AST\CVariableDefList.h"
#include "AST\CVariables.h"
#include "CType.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Parser Tables
#include "DaedalusParserTables.h"

//Constructor
CParser::CParser(const ICompilerCallback &refCallback) : CLALR1Parser<EToken, ANode *>(NUMBER_OF_ALPHABET_ELEMENTS, NUMBER_OF_NONTERMINALS, actionTable, reductionRuleLengthTable, reductionRuleLeftSideTable, gotoTable), refCallback(refCallback)
{
}

//Destructor
CParser::~CParser()
{
	this->Release();
}

//Private Functions
void CParser::OnPutToken(const EToken &refToken, const CString &refString, ANode *&refOutput)
{
	switch(refToken)
	{
	case TOKEN_IDENTIFIER:
	case TOKEN_INTNUMBER:
	case TOKEN_FLOATNUMBER:
	case TOKEN_LITERAL:
	case TOKEN_FUNC:
	case TOKEN_INSTANCE:
		{
			refOutput = new CTextNode(refString, this->lexer.GetLineNumber());
			this->Register(refOutput);
		}
		break;
	}
}

void CParser::OnReduce(int32 reductionRule, ANode *&refOutput)
{
	switch(reductionRule)
	{
	case 2:
		{
			refOutput = new CGlobals();
		}
		break;
	case 3:
		{
			CGlobals *pGlobals;
			CConstant *pConstant;

			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pConstant = (CConstant *)this->GetSemanticValue(1);

			pGlobals->Add(pConstant);

			refOutput = pGlobals;
		}
		break;
	case 4:
		{
			CGlobals *pGlobals;
			CClass *pClass;

			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pClass = (CClass *)this->GetSemanticValue(1);

			pGlobals->Add(pClass);

			refOutput = pGlobals;
		}
		break;
	case 5: //GLOBALS -> * FUNCTION GLOBALS
		{
			CGlobals *pGlobals;
			CFunction *pFunction;
			
			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pFunction = (CFunction *)this->GetSemanticValue(1);
			
			pGlobals->Add(pFunction);
			
			refOutput = pGlobals;
		}
		break;
	case 6:
		{
			CGlobals *pGlobals;
			AInstance *pInstance;
			
			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pInstance = (AInstance *)this->GetSemanticValue(1);

			pGlobals->Add(pInstance);
			
			refOutput = pGlobals;
		}
		break;
	case 7: //GLOBALS -> * PROTOTYPE GLOBALS
		{
			CGlobals *pGlobals;
			CPrototype *pPrototype;
			
			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pPrototype = (CPrototype *)this->GetSemanticValue(1);
			
			pGlobals->Add(pPrototype);
			
			refOutput = pGlobals;
		}
		break;
	case 8:
		{
			CGlobals *pGlobals;
			CVariable *pVariable;

			pGlobals = (CGlobals *)this->GetSemanticValue(0);
			pVariable = (CVariable *)this->GetSemanticValue(1);

			pGlobals->Add(pVariable);

			refOutput = pGlobals;
		}
		break;
	case 9:
		{
			CTextNode *pIdentifierNode;
			
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(3);
			refOutput = new CConstant((CType *)this->GetSemanticValue(4), pIdentifierNode->GetText(), (AExpression *)this->GetSemanticValue(1), this->fileName, pIdentifierNode->GetLineNumber());
			delete pIdentifierNode;
		}
		break;
	case 10: //CONSTANT -> * TOKEN_CONST TYPE TOKEN_IDENTIFIER TOKEN_SQUAREDBRACKETOPEN ARRAYINDEX TOKEN_SQUAREDBRACKETCLOSE TOKEN_ASSIGNMENT TOKEN_BRACEOPEN CONSTVALUES TOKEN_BRACECLOSE TOKEN_SEMICOLON
		{
			CTextNode *pIdentifierNode;
			
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(8);
			refOutput = new CConstantArray((CType *)this->GetSemanticValue(9), pIdentifierNode->GetText(), (CArrayIndex *)this->GetSemanticValue(6), (CExprList *)this->GetSemanticValue(2), this->fileName, pIdentifierNode->GetLineNumber());
			delete pIdentifierNode;
		}
		break;
	case 11:
		{
			CTextNode *pNode;
			CVariables *pVariables;
			
			pNode = (CTextNode *)this->GetSemanticValue(4);
			pVariables = (CVariables *)this->GetSemanticValue(2);

			refOutput = new CClass(pNode->GetText(), pVariables, this->fileName, pNode->GetLineNumber());

			delete pNode;
		}
		break;
	case 12: //FUNCTION -> * TOKEN_FUNC RETURNVALUE TOKEN_IDENTIFIER TOKEN_PARENOPEN ARGUMENTS TOKEN_PARENCLOSE TOKEN_BRACEOPEN STATEMENTS TOKEN_BRACECLOSE TOKEN_SEMICOLON
		{
			CType *pReturnType;
			CTextNode *pNameNode, *pFuncTokenNode;
			CArguments *pArgs;
			CStatements *pStatements;
			
			pFuncTokenNode = (CTextNode *)this->GetSemanticValue(9);
			pReturnType = (CType *)this->GetSemanticValue(8);
			pNameNode = (CTextNode *)this->GetSemanticValue(7);
			pArgs = (CArguments *)this->GetSemanticValue(5);
			pStatements = (CStatements *)this->GetSemanticValue(2);
			
			refOutput = new CFunction(pReturnType, pNameNode->GetText(), pArgs, pStatements, this->fileName, pFuncTokenNode->GetLineNumber());
			
			delete pNameNode;
			delete pFuncTokenNode;
		}
		break;
	case 13:
		{
			CIdentifierList *pList;
			CTextNode *pClassNameNode, *pInstanceTokenNode;
			
			pInstanceTokenNode = (CTextNode *)this->GetSemanticValue(5);
			pList = (CIdentifierList *)this->GetSemanticValue(4);
			pClassNameNode = (CTextNode *)this->GetSemanticValue(2);
			
			refOutput = new CInstanceList(pList, pClassNameNode->GetText(), NULL, this->fileName, pInstanceTokenNode->GetLineNumber());

			delete pClassNameNode;
			delete pInstanceTokenNode;
		}
		break;
	case 14:
		{
			CIdentifierList *pList;
			CTextNode *pClassNameNode, *pInstanceTokenNode;
			CStatements *pStatements;
			
			pInstanceTokenNode = (CTextNode *)this->GetSemanticValue(8);
			pList = (CIdentifierList *)this->GetSemanticValue(7);
			pClassNameNode = (CTextNode *)this->GetSemanticValue(5);
			pStatements = (CStatements *)this->GetSemanticValue(2);
			
			refOutput = new CInstanceList(pList, pClassNameNode->GetText(), pStatements, this->fileName, pInstanceTokenNode->GetLineNumber());

			delete pClassNameNode;
			delete pInstanceTokenNode;
		}
		break;
	case 15: //PROTOTYPE -> * TOKEN_PROTOTYPE TOKEN_IDENTIFIER TOKEN_PARENOPEN TOKEN_IDENTIFIER TOKEN_PARENCLOSE TOKEN_BRACEOPEN STATEMENTS TOKEN_BRACECLOSE TOKEN_SEMICOLON
		{
			CStatements *pStatements;
			CTextNode *pClassNameNode, *pInstanceName;

			pStatements = (CStatements *)this->GetSemanticValue(2);
			pClassNameNode = (CTextNode *)this->GetSemanticValue(5);
			pInstanceName = (CTextNode *)this->GetSemanticValue(7);
			
			refOutput = new CPrototype(pInstanceName->GetText(), pClassNameNode->GetText(), pStatements, this->fileName, pInstanceName->GetLineNumber());

			delete pClassNameNode;
			delete pInstanceName;
		}
		break;
	case 16:
		{
			refOutput = new CType(DAEDALUS_TYPE_FLOAT);
		}
		break;
	case 17:
		{
			refOutput = new CType(DAEDALUS_TYPE_FUNC);
		}
		break;
	case 18:
		{
			refOutput = new CType(DAEDALUS_TYPE_INT);
		}
		break;
	case 19:
		{
			refOutput = new CType(DAEDALUS_TYPE_STRING);
		}
		break;
	case 20:
		{
			CTextNode *pIdentifierNode;
			
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(0);
			
			refOutput = new CType(pIdentifierNode->GetText());
			
			delete pIdentifierNode;
		}
		break;
	case 21:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CLeftValueIdentifier(pNode->GetText(), pNode->GetFileName(), pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 22:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CFloatExpression((float32)pNode->GetText().ToFloat(), this->fileName, pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 23:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CIntExpression((int32)pNode->GetText().ToInt64(), this->fileName, pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 24:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CIntExpression(-(int32)pNode->GetText().ToInt64(), this->fileName, pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 25:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CStringExpression(pNode->GetText(), this->fileName, pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 26: //CONSTVALUE -> * TOKEN_PARENOPEN CONSTVALUE TOKEN_PARENCLOSE
		{
			refOutput = this->GetSemanticValue(1);
		}
		break;
	/*case 27:
		{
			refOutput.type = SEMANTICVALUETYPE_CONSTVALUE;
			
			refOutput.value.pConstValue = (SConstValue *)this->MemAlloc(sizeof(*refOutput.value.pConstValue));
			refOutput.value.pConstValue->type = CONSTANTVALUETYPE_CONSTVALUES;
			
			this->GetSemanticValue(1, gpv);
			refOutput.value.pConstValue->value.pConstValues = gpv.value.pConstValues;
		}
		break;*/
	case 28: //CONSTVALUE -> * CONSTVALUE TOKEN_PLUS CONSTVALUE
		{
			refOutput = new CPlusExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 29: //CONSTVALUE -> * CONSTVALUE TOKEN_MULTIPLY CONSTVALUE
		{
			refOutput = new CMultiplyExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 30:
		{
			refOutput = new CDivideExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 31:
		{
			refOutput = new CShiftLeftExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 32:
		{
			refOutput = new CBitwiseOrExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 33: //CONSTVALUES -> * CONSTVALUE
		{
			refOutput = new CExprList((AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 34:
		{
			AExpression *pConstValue;
			CExprList *pConstValues;

			pConstValue = (AExpression *)this->GetSemanticValue(2);
			pConstValues = (CExprList *)this->GetSemanticValue(0);

			pConstValues->Add(pConstValue);

			refOutput = pConstValues;
		}
		break;
	case 35:
		{
			refOutput = new CVariables();
		}
		break;
	case 36:
		{
			AVariable *pVariable;
			CVariables *pVariables;
			
			pVariable = (AVariable *)this->GetSemanticValue(1);
			pVariables = (CVariables *)this->GetSemanticValue(0);
			
			pVariables->Add(pVariable);
			
			refOutput = pVariables;
		}
		break;
	case 37: //VARIABLE -> * TOKEN_VAR TYPE NAMES TOKEN_SEMICOLON
		{
			CIdentifierList *pNames;
			CType *pType;
			
			pNames = (CIdentifierList *)this->GetSemanticValue(1);
			pType = (CType *)this->GetSemanticValue(2);
			
			refOutput = new CVariableDefList(pType, pNames);
		}
		break;
	case 38:
		{
			CTextNode *pIdentifierNode;
			CType *pType;
			CArrayIndex *pArrayIndex;

			pArrayIndex = (CArrayIndex *)this->GetSemanticValue(2);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(4);
			pType = (CType *)this->GetSemanticValue(5);
			
			refOutput = new CVariableArray(pType, pIdentifierNode->GetText(), pArrayIndex);
			
			delete pIdentifierNode;
		}
		break;
	case 39:
		{
			CTextNode *pIdentifierNode;

			pIdentifierNode = (CTextNode *)this->GetSemanticValue(0);

			refOutput = new CIdentifierList(pIdentifierNode->GetText());
			
			delete pIdentifierNode;
		}
		break;
	case 40:
		{
			CTextNode *pIdentifierNode;
			CIdentifierList *pList;

			pList = (CIdentifierList *)this->GetSemanticValue(0);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(2);

			pList->Add(pIdentifierNode->GetText());
			
			refOutput = pList;
			
			delete pIdentifierNode;
		}
		break;
	case 41:
		{
			refOutput = new CStatements();
		}
		break;
	case 42:
		{
			AStatement *pStatement;
			CStatements *pStatements;

			pStatements = (CStatements *)this->GetSemanticValue(0);
			pStatement = (AStatement *)this->GetSemanticValue(1);

			pStatements->Add(pStatement);

			refOutput = pStatements;
		}
		break;
	case 43: //STATEMENT -> * TOKEN_VAR TYPE TOKEN_IDENTIFIER TOKEN_SEMICOLON
		{
			CTextNode *pNameNode;
			CType *pType;

			pNameNode = (CTextNode *)this->GetSemanticValue(1);
			pType = (CType *)this->GetSemanticValue(2);
			
			refOutput = new CDeclarationStatement(pType, pNameNode->GetText());

			delete pNameNode;
		}
		break;
	case 44:
		{
			refOutput = new CAssignStatement((CLeftValueIdentifier *)this->GetSemanticValue(3), (AExpression *)this->GetSemanticValue(1));
		}
		break;
	case 45: //STATEMENT -> * LEFTVALUE TOKEN_MINUSASSIGN EXPR TOKEN_SEMICOLON
		{
			refOutput = new CMinusAssignStatement((CLeftValueIdentifier *)this->GetSemanticValue(3), (AExpression *)this->GetSemanticValue(1));
		}
		break;
	case 46: //STATEMENT -> * LEFTVALUE TOKEN_PLUSASSIGN EXPR TOKEN_SEMICOLON
		{
			refOutput = new CPlusAssignStatement((CLeftValueIdentifier *)this->GetSemanticValue(3), (AExpression *)this->GetSemanticValue(1));
		}
		break;
	case 47: //STATEMENT -> * TOKEN_IDENTIFIER TOKEN_PARENOPEN CALLARGS TOKEN_PARENCLOSE TOKEN_SEMICOLON
		{
			CExprList *pCallArgs;
			CTextNode *pIdentifierNode;

			pCallArgs = (CExprList *)this->GetSemanticValue(2);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(4);
			
			refOutput = new CCallStatement(pIdentifierNode->GetText(), pCallArgs);
			
			delete pIdentifierNode;
		}
		break;
	case 48: //STATEMENT -> * TOKEN_IF EXPR TOKEN_BRACEOPEN STATEMENTS TOKEN_BRACECLOSE ELSEIFS
		{
			CElseIfs *pElseIfs;
			CStatements *pStatements;
			AExpression *pExpr;
			
			pElseIfs = (CElseIfs *)this->GetSemanticValue(0);
			pStatements = (CStatements *)this->GetSemanticValue(2);
			pExpr = (AExpression *)this->GetSemanticValue(4);

			pElseIfs->AddFront(pExpr, pStatements);
			refOutput = new CIfStatement(pElseIfs);
		}
		break;
	case 49: //STATEMENT -> * TOKEN_RETURN TOKEN_SEMICOLON
		{
			refOutput = new CReturnStatement(NULL);
		}
		break;
	case 50: //STATEMENT -> * TOKEN_RETURN EXPR TOKEN_SEMICOLON
		{
			AExpression *pExpr;

			pExpr = (AExpression *)this->GetSemanticValue(1);
			refOutput = new CReturnStatement(pExpr);
		}
		break;
	case 51: //STATEMENT -> * TOKEN_IDENTIFIER TOKEN_SEMICOLON
		{
			CTextNode *pIdentifierNode;

			pIdentifierNode = (CTextNode *)this->GetSemanticValue(1);

			refOutput = NULL;
			
			this->refCallback.OnUselessStatement(this->fileName, pIdentifierNode->GetLineNumber());
			
			delete pIdentifierNode;
		}
		break;
	case 52: //STATEMENT -> * LEFTVALUE TOKEN_EQUALS EXPR TOKEN_SEMICOLON
		{
			CLeftValueIdentifier *pLeftValue;
			AExpression *pExpr;

			pLeftValue = (CLeftValueIdentifier *)this->GetSemanticValue(3);
			pExpr = (AExpression *)this->GetSemanticValue(1);
			
			this->refCallback.OnUselessStatement(this->fileName, pLeftValue->GetLineNumber());
			
			refOutput = NULL;

			delete pLeftValue;
			delete pExpr;
		}
		break;
	case 53: //LEFTVALUE -> * TOKEN_IDENTIFIER
		{
			CTextNode *pIdentifierNode;

			pIdentifierNode = (CTextNode *)this->GetSemanticValue(0);
			
			refOutput = new CLeftValueIdentifier(pIdentifierNode->GetText(), this->fileName, pIdentifierNode->GetLineNumber());

			delete pIdentifierNode;
		}
		break;
	case 54: //LEFTVALUE -> * TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER
		{
			CTextNode *pIdentifierNode, *pSubIdentifierNode;
			
			pSubIdentifierNode = (CTextNode *)this->GetSemanticValue(0);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(2);
			
			refOutput = new CLeftValueMember(pIdentifierNode->GetText(), pSubIdentifierNode->GetText(), this->fileName, pIdentifierNode->GetLineNumber());
			
			delete pIdentifierNode;
			delete pSubIdentifierNode;
		}
		break;
	case 55: //LEFTVALUE -> * TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER TOKEN_SQUAREDBRACKETOPEN ARRAYINDEX TOKEN_SQUAREDBRACKETCLOSE
		{
			CArrayIndex *pArrayIndex;
			CTextNode *pMemberNode, *pIdentifierNode;
			
			pArrayIndex = (CArrayIndex *)this->GetSemanticValue(1);
			pMemberNode = (CTextNode *)this->GetSemanticValue(3);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(5);
			
			refOutput = new CLeftValueMemberArray(pIdentifierNode->GetText(), pMemberNode->GetText(), pArrayIndex, this->fileName, pIdentifierNode->GetLineNumber());

			delete pMemberNode;
			delete pIdentifierNode;
		}
		break;
	case 56: //LEFTVALUE -> * TOKEN_IDENTIFIER TOKEN_SQUAREDBRACKETOPEN ARRAYINDEX TOKEN_SQUAREDBRACKETCLOSE
		{
			CTextNode *pIdentifierNode;
			CArrayIndex *pArrayIndex;
			
			pArrayIndex = (CArrayIndex *)this->GetSemanticValue(1);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(3);
			
			refOutput = new CLeftValueArray(pIdentifierNode->GetText(), pArrayIndex, this->fileName, pIdentifierNode->GetLineNumber());
			
			delete pIdentifierNode;
		}
		break;
	case 57:
		{
			refOutput = this->GetSemanticValue(0);
		}
		break;
	case 58: //EXPR -> * LEFTVALUE
		{
			refOutput = this->GetSemanticValue(0);
		}
		break;
	case 59: //EXPR -> * TOKEN_NOT EXPR
		{
			AExpression *pSubExpr;
			
			pSubExpr = (AExpression *)this->GetSemanticValue(0);
			refOutput = new CNotExpression(pSubExpr);
		}
		break;
	case 60:
		{
			AExpression *pSubExpr;
			
			pSubExpr = (AExpression *)this->GetSemanticValue(0);
			refOutput = new CMinusExpression(pSubExpr);
		}
		break;
	case 61: //EXPR -> * TOKEN_PLUS EXPR
		{
			refOutput = this->GetSemanticValue(0);
		}
		break;
	case 62: //EXPR -> * TOKEN_PARENOPEN EXPR TOKEN_PARENCLOSE
		{
			refOutput = this->GetSemanticValue(1);
		}
		break;
	case 63: //EXPR -> * EXPR TOKEN_PLUS EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CPlusExpression(pLeft, pRight);
		}
		break;
	case 64: //EXPR -> * EXPR TOKEN_MINUS EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CSubtractExpression(pLeft, pRight);
		}
		break;
	case 65: //EXPR -> * EXPR TOKEN_MULTIPLY EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CMultiplyExpression(pLeft, pRight);
		}
		break;
	case 66: //EXPR -> * EXPR TOKEN_DIVIDE EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CDivideExpression(pLeft, pRight);
		}
		break;
	case 67: //EXPR -> * EXPR TOKEN_EQUALS EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CEqualsExpression(pLeft, pRight);
		}
		break;
	case 68: //EXPR -> * EXPR TOKEN_NOTEQUALS EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CNotEqualsExpression(pLeft, pRight);
		}
		break;
	case 69: //EXPR -> * EXPR TOKEN_LESSTHAN EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CLessThanExpression(pLeft, pRight);
		}
		break;
	case 70: //EXPR -> * EXPR TOKEN_LESSOREQUAL EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CLessThanOrEqualToExpression(pLeft, pRight);
		}
		break;
	case 71: //EXPR -> * EXPR TOKEN_GREATERTHAN EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CGreaterThanExpression(pLeft, pRight);
		}
		break;
	case 72: //EXPR -> * EXPR TOKEN_GREATEROREQUAL EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CGreaterThanOrEqualToExpression(pLeft, pRight);
		}
		break;
	case 73: //EXPR -> * EXPR TOKEN_LOGICALAND EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CLogicalAndExpression(pLeft, pRight);
		}
		break;
	case 74: //EXPR -> * EXPR TOKEN_LOGICALOR EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CLogicalOrExpression(pLeft, pRight);
		}
		break;
	case 75: //EXPR -> * EXPR TOKEN_BITWISEAND EXPR
		{
			refOutput = new CBitwiseAndExpression((AExpression *)this->GetSemanticValue(2), (AExpression *)this->GetSemanticValue(0));
		}
		break;
	case 76: //EXPR -> * EXPR TOKEN_BITWISEOR EXPR
		{
			AExpression *pLeft, *pRight;
			
			pRight = (AExpression *)this->GetSemanticValue(0);
			pLeft = (AExpression *)this->GetSemanticValue(2);
			
			refOutput = new CBitwiseOrExpression(pLeft, pRight);
		}
		break;
	case 77: //EXPR -> * TOKEN_IDENTIFIER TOKEN_PARENOPEN CALLARGS TOKEN_PARENCLOSE
		{
			CExprList *pCallArgs;
			CTextNode *pIdentifierNode;
			
			pCallArgs = (CExprList *)this->GetSemanticValue(1);
			pIdentifierNode = (CTextNode *)this->GetSemanticValue(3);
			
			refOutput = new CCallExpression(pIdentifierNode->GetText(), pCallArgs);
			
			delete pIdentifierNode;
		}
		break;
	case 78:
		{
			refOutput = new CType(DAEDALUS_TYPE_VOID);
		}
		break;
	case 79: //RETURNVALUE -> * TOKEN_INT
		{
			refOutput = new CType(DAEDALUS_TYPE_INT);
		}
		break;
	case 80: //RETURNVALUE -> * TOKEN_STRING
		{
			refOutput = new CType(DAEDALUS_TYPE_STRING);
		}
		break;
	case 81: //ARGUMENTS -> *
		{
			refOutput = NULL;
		}
		break;
	case 82: //ARGUMENTS -> * TOKEN_VAR TYPE TOKEN_IDENTIFIER
		{
			CType *pType;
			CTextNode *pNode;
			
			pType = (CType *)this->GetSemanticValue(1);
			pNode = (CTextNode *)this->GetSemanticValue(0);
			
			refOutput = new CArguments(pType, pNode->GetText());
			
			delete pNode;
		}
		break;
	case 83: //ARGUMENTS -> * TOKEN_VAR TYPE TOKEN_IDENTIFIER TOKEN_COMMA ARGUMENTS
		{
			CType *pType;
			CTextNode *pNode;
			CArguments *pArgs;
			
			pType = (CType *)this->GetSemanticValue(3);
			pNode = (CTextNode *)this->GetSemanticValue(2);
			pArgs = (CArguments *)this->GetSemanticValue(0);

			pArgs->Add(pType, pNode->GetText());
			refOutput = pArgs;
			
			delete pNode;
		}
		break;
	case 84: //CALLARGS -> *
		{
			refOutput = new CExprList;
		}
		break;
	case 85: //CALLARGS -> * EXPR
		{
			AExpression *pExpr;
			
			pExpr = (AExpression *)this->GetSemanticValue(0);
			
			refOutput = new CExprList(pExpr);
		}
		break;
	case 86: //CALLARGS -> * EXPR TOKEN_COMMA CALLARGS
		{
			CExprList *pArgs;
			AExpression *pExpr;

			pArgs = (CExprList *)this->GetSemanticValue(0);
			pExpr = (AExpression *)this->GetSemanticValue(2);

			pArgs->AddFront(pExpr);
			refOutput = pArgs;
		}
		break;
	case 87: //ELSEIFS -> *
		{
			refOutput = new CElseIfs;
		}
		break;
	case 88: //ELSEIFS -> * TOKEN_SEMICOLON
		{
			refOutput = new CElseIfs;
		}
		break;
	case 89: //ELSEIFS -> * TOKEN_ELSE TOKEN_BRACEOPEN STATEMENTS TOKEN_BRACECLOSE TOKEN_SEMICOLON
		{
			CStatements *pStatements;
			
			pStatements = (CStatements *)this->GetSemanticValue(2);
			refOutput = new CElseIfs(NULL, pStatements);
		}
		break;
	case 90: //ELSEIFS -> * TOKEN_ELSE TOKEN_IF EXPR TOKEN_BRACEOPEN STATEMENTS TOKEN_BRACECLOSE ELSEIFS
		{
			CElseIfs *pElseIfs;
			CStatements *pStatements;
			AExpression *pExpr;

			pElseIfs = (CElseIfs *)this->GetSemanticValue(0);
			pStatements = (CStatements *)this->GetSemanticValue(2);
			pExpr = (AExpression *)this->GetSemanticValue(4);

			pElseIfs->AddFront(pExpr, pStatements);
			refOutput = pElseIfs;
		}
		break;
	case 91:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CArrayIndex((uint32)pNode->GetText().ToUInt64(), this->fileName, pNode->GetLineNumber());
			delete pNode;
		}
		break;
	case 92:
		{
			CTextNode *pNode;
			
			pNode = (CTextNode *)this->GetSemanticValue(0);
			refOutput = new CArrayIndex(pNode->GetText(), pNode->GetFileName(), pNode->GetLineNumber());
			delete pNode;
		}
		break;
	default:
		ASSERTMSG(0, CString(reductionRule));
	}

	this->Register(refOutput);
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

bool CParser::Parse(const byte *pInput, CWString fileName)
{
	this->fileName = fileName;
	
	this->lexer.Init(pInput);
	
	return CLALR1Parser<Daedalus::EToken, Daedalus::AST::ANode *>::Parse(this->lexer);
}

void CParser::Release()
{
	foreach(it, this->tmpNodes)
	{
		delete it.GetValue();
	}
	this->tmpNodes.Release();

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