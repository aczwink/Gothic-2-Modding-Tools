//Class Header
#include "CBitwiseOrExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CBitwiseOrExpression::CBitwiseOrExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CBitwiseOrExpression::Combine(int32 left, int32 right) const
{
	return left | right;
}

EOpcode CBitwiseOrExpression::GetOpcode() const
{
	return OPCODE_BITWISEOR;
}