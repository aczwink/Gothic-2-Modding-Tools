//Class Header
#include "CAssignStatement.h"
//Local
#include "../OptAST/CAssignStatement.h"
#include "AExpression.h"
#include "CLeftValueIdentifier.h"
#include "CType.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CAssignStatement::CAssignStatement(CLeftValueIdentifier *pLeftValue, AExpression *pExpression) : AStatement()
{
	this->pLeftValue = pLeftValue;
	this->pExpression = pExpression;
}

//Destructor
CAssignStatement::~CAssignStatement()
{
	delete this->pLeftValue;
	delete this->pExpression;
}

//Public methods
OptAST::AStatement *CAssignStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	bool needCast;
	AExpression *pExpr;
	OptAST::CAssignStatement *pOptStatement;
	
	if(!this->pExpression->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
		return NULL;
	pExpr = this->pExpression->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pExpression)
	{
		delete this->pExpression;
		this->pExpression = pExpr;
	}
	
	this->pLeftValue->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	pExpr = this->pLeftValue->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pLeftValue)
	{
		delete this->pLeftValue;
		this->pLeftValue = (CLeftValueIdentifier *)pExpr;
	}

	if(!this->pExpression->GetType().IsConvertableTo(this->pLeftValue->GetType(), needCast))
	{
		refCallback.OnTypeMismatch(this->pExpression->GetType(), this->pLeftValue->GetType(), this->pLeftValue->GetFileName(), this->pLeftValue->GetLineNumber());
		return NULL;
	}
	if(needCast)
		this->pExpression->SetCastTo(this->pLeftValue->GetType());
	
	pOptStatement = new OptAST::CAssignStatement(this->pLeftValue->GetType().GetType(), this->pLeftValue->GetTranslatedExpression(refCompiler), this->pExpression->GetTranslatedExpression(refCompiler));
	
	return pOptStatement;
}