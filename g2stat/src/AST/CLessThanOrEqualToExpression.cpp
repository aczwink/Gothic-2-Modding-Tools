//Class Header
#include "CLessThanOrEqualToExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLessThanOrEqualToExpression::CLessThanOrEqualToExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CLessThanOrEqualToExpression::Combine(int32 left, int32 right) const
{
	return left <= right;
}

EOpcode CLessThanOrEqualToExpression::GetOpcode() const
{
	return OPCODE_LESSTHANOREQUALTO;
}

//Public methods
void CLessThanOrEqualToExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}