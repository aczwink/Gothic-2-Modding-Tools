//Class Header
#include "CDivideExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CDivideExpression::CDivideExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CDivideExpression::Combine(int32 left, int32 right) const
{
	return left / right;
}

EOpcode CDivideExpression::GetOpcode() const
{
	return OPCODE_DIVIDE;
}