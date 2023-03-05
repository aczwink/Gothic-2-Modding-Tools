//Class Header
#include "CMultiplyExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CMultiplyExpression::CMultiplyExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CMultiplyExpression::Combine(int32 left, int32 right) const
{
	return left * right;
}

EOpcode CMultiplyExpression::GetOpcode() const
{
	return OPCODE_MULTIPLICATE;
}