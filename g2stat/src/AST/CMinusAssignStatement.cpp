//Class Header
#include "CMinusAssignStatement.h"
//Local
#include "../OptAST/CAssignStatement.h"
#include "AExpression.h"
#include "CLeftValueIdentifier.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CMinusAssignStatement::CMinusAssignStatement(CLeftValueIdentifier *pLeftValue, AExpression *pExpression) : AStatement()
{
	this->pLeftValue = pLeftValue;
	this->pExpression = pExpression;
}

//Destructor
CMinusAssignStatement::~CMinusAssignStatement()
{
	delete this->pLeftValue;
	delete this->pExpression;
}

//Public methods
OptAST::AStatement *CMinusAssignStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	AExpression *pExpr;
	OptAST::CAssignStatement *pOptStatement;
	
	this->pExpression->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	pExpr = this->pExpression->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pExpression)
	{
		delete this->pExpression;
		this->pExpression = pExpr;
	}
	
	this->pLeftValue->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	pExpr = this->pLeftValue->GetOptimizedExpression(refCompiler);
	
	pOptStatement = new OptAST::CAssignStatement(pExpr->GetType().GetType(), OPCODE_SUBTRACT, pExpr->GetTranslatedExpression(refCompiler), this->pExpression->GetTranslatedExpression(refCompiler));
	if(pExpr != this->pLeftValue)
	{
		delete pExpr;
	}

	return pOptStatement;
}