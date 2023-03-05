//Class Header
#include "CExprStatement.h"
//Local
#include "AExpression.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CExprStatement::CExprStatement(AExpression *pExpr)
{
	this->pExpr = pExpr;
}

//Destructor
CExprStatement::~CExprStatement()
{
	delete this->pExpr;
}

//Public methods
void CExprStatement::CollectSymbols(CCompiler &refCompiler)
{
	this->pExpr->CollectSymbols(refCompiler);
}

void CExprStatement::Compile(CProgramBuffer &refProgram) const
{
	this->pExpr->Compile(refProgram);
}