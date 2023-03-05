//Class Header
#include "CEqualsExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CEqualsExpression::CEqualsExpression(AExpression *pLeft, AExpression *pRight) : ABinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CEqualsExpression::Combine(int32 left, int32 right) const
{
	return left == right;
}

EOpcode CEqualsExpression::GetOpcode() const
{
	return OPCODE_EQUALS;
}

//Public methods
CType CEqualsExpression::GetType() const
{
	ASSERT(0);
	return CType();
}