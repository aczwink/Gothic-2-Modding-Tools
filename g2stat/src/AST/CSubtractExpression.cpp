//Class Header
#include "CSubtractExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CSubtractExpression::CSubtractExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CSubtractExpression::Combine(int32 left, int32 right) const
{
	return left - right;
}

EOpcode CSubtractExpression::GetOpcode() const
{
	return OPCODE_SUBTRACT;
}