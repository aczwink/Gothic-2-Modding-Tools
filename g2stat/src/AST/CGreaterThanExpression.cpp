//Class Header
#include "CGreaterThanExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CGreaterThanExpression::CGreaterThanExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CGreaterThanExpression::Combine(int32 left, int32 right) const
{
	return left > right;
}

EOpcode CGreaterThanExpression::GetOpcode() const
{
	return OPCODE_GREATERTHAN;
}

//Public methods
void CGreaterThanExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}