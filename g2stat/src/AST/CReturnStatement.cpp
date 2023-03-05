//Class Header
#include "CReturnStatement.h"
//Local
#include "../OptAST/CReturnStatement.h"
#include "AExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CReturnStatement::CReturnStatement(AExpression *pExpr) : AStatement()
{
	this->pExpr = pExpr;
}

//Destructor
CReturnStatement::~CReturnStatement()
{
	delete this->pExpr;
}

//Public methods
OptAST::AStatement *CReturnStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	AExpression *pExpr;

	if(!this->pExpr)
		return new OptAST::CReturnStatement(NULL);
	
	this->pExpr->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	pExpr = this->pExpr->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pExpr)
	{
		delete this->pExpr;
		this->pExpr = pExpr;
	}
	
	return new OptAST::CReturnStatement(this->pExpr->GetTranslatedExpression(refCompiler));
}