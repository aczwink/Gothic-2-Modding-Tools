//Class Header
#include "CShiftLeftExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CShiftLeftExpression::CShiftLeftExpression(AExpression *pLeft, AExpression *pRight) : AArithmeticBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CShiftLeftExpression::Combine(int32 left, int32 right) const
{
	return left << right;
}

EOpcode CShiftLeftExpression::GetOpcode() const
{
	ASSERT(0);
	return OPCODE_ADD; //there is no opcode for this???
}