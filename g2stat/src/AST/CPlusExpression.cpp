//Class Header
#include "CPlusExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CPlusExpression::CPlusExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CPlusExpression::Combine(int32 left, int32 right) const
{
	return left + right;
}

EOpcode CPlusExpression::GetOpcode() const
{
	return OPCODE_ADD;
}