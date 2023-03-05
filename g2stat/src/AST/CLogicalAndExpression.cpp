//Class Header
#include "CLogicalAndExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLogicalAndExpression::CLogicalAndExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CLogicalAndExpression::Combine(int32 left, int32 right) const
{
	return left && right;
}

EOpcode CLogicalAndExpression::GetOpcode() const
{
	return OPCODE_LOGICALAND;
}

//Public methods
void CLogicalAndExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}