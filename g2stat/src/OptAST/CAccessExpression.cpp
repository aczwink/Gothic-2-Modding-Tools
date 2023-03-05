//Class Header
#include "CAccessExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CAccessExpression::CAccessExpression(const ASymbol *pAccessor, AExpression *pAccessExpr)
{
	this->pAccessor = pAccessor;
	this->pSubExpr = pAccessExpr;
}

//Destructor
CAccessExpression::~CAccessExpression()
{
	delete this->pSubExpr;
}

//Public methods
void CAccessExpression::CollectSymbols(CCompiler &refCompiler)
{
	this->pSubExpr->CollectSymbols(refCompiler);
}

void CAccessExpression::Compile(CProgramBuffer &refProgram) const
{
	refProgram.WriteByte(OPCODE_SET_INSTANCE);
	refProgram.WriteUInt32(this->pAccessor->GetSymbolIndex());
	this->pSubExpr->Compile(refProgram);
}