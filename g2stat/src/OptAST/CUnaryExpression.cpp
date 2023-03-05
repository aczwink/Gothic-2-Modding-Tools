//Class Header
#include "CUnaryExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CUnaryExpression::CUnaryExpression(EOpcode op, AExpression *pSubExpr)
{
	this->op = op;
	this->pSubExpr = pSubExpr;
}

//Destructor
CUnaryExpression::~CUnaryExpression()
{
	delete this->pSubExpr;
}

//Public methods
void CUnaryExpression::CollectSymbols(CCompiler &refCompiler)
{
	this->pSubExpr->CollectSymbols(refCompiler);
}

void CUnaryExpression::Compile(CProgramBuffer &refProgram) const
{
	this->pSubExpr->Compile(refProgram);
	refProgram.WriteByte(this->op);
}