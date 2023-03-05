//Class Header
#include "CNotEqualsExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CNotEqualsExpression::CNotEqualsExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CNotEqualsExpression::Combine(int32 left, int32 right) const
{
	return left != right;
}

EOpcode CNotEqualsExpression::GetOpcode() const
{
	return OPCODE_NOTEQUALS;
}