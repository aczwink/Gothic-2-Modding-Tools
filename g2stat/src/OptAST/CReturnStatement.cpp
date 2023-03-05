//Class Header
#include "CReturnStatement.h"
//Local
#include "../Opcodes.h"
#include "AExpression.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CReturnStatement::CReturnStatement(AExpression *pExpr)
{
	this->pExpr = pExpr;
}

//Destructor
CReturnStatement::~CReturnStatement()
{
	HeapDeleteSafe(this->pExpr);
}

//Public methods
void CReturnStatement::CollectSymbols(CCompiler &refCompiler)
{
	if(this->pExpr)
		this->pExpr->CollectSymbols(refCompiler);
}

void CReturnStatement::Compile(CProgramBuffer &refProgram) const
{
	if(this->pExpr)
		this->pExpr->Compile(refProgram);
	refProgram.WriteByte(OPCODE_RETURN);
}