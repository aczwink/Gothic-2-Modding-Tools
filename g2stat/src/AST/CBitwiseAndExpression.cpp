//Class Header
#include "CBitwiseAndExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CBitwiseAndExpression::CBitwiseAndExpression(AExpression *pLeft, AExpression *pRight) : ABinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CBitwiseAndExpression::Combine(int32 left, int32 right) const
{
	return left & right;
}

EOpcode CBitwiseAndExpression::GetOpcode() const
{
	return OPCODE_BITWISEAND;
}

//Public methods
CType CBitwiseAndExpression::GetType() const
{
	ASSERT(0);
	return CType();
}

void CBitwiseAndExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}