//Class Header
#include "CLessThanExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLessThanExpression::CLessThanExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CLessThanExpression::Combine(int32 left, int32 right) const
{
	return left < right;
}

EOpcode CLessThanExpression::GetOpcode() const
{
	return OPCODE_LESSTHAN;
}