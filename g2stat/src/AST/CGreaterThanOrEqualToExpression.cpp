//Class Header
#include "CGreaterThanOrEqualToExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CGreaterThanOrEqualToExpression::CGreaterThanOrEqualToExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CGreaterThanOrEqualToExpression::Combine(int32 left, int32 right) const
{
	return left >= right;
}

EOpcode CGreaterThanOrEqualToExpression::GetOpcode() const
{
	return OPCODE_GREATERTHANOREQUALTO;
}

//Public methods
void CGreaterThanOrEqualToExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}