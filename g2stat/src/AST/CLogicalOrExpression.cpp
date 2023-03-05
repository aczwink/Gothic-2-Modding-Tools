//Class Header
#include "CLogicalOrExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLogicalOrExpression::CLogicalOrExpression(AExpression *pLeft, AExpression *pRight) : ALogicalBinaryExpression(pLeft, pRight)
{
}

//Private Methods
int32 CLogicalOrExpression::Combine(int32 left, int32 right) const
{
	return left || right;
}

EOpcode CLogicalOrExpression::GetOpcode() const
{
	return OPCODE_LOGICALOR;
}

//Public methods
void CLogicalOrExpression::Process(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}