/*//Class Header
#include "CExpressionConstValue.h"
//Local
#include "AConstValue.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Constructor
CExpressionConstValue::CExpressionConstValue(AConstValue *pConstValue) : AExpression(CWString(), 0)
{
	this->pConstValue = pConstValue;
}

//Public methods
void CExpressionConstValue::Compile(AOutputStream &refOutputStream, CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	this->pConstValue->Compile(refOutputStream, refLocalVariables, pClass, refCompiler);
}

AExpression *CExpressionConstValue::Copy() const
{
	ASSERT(0);
	return NULL;
}

void CExpressionConstValue::DistributeSymbolIndices(uint32 &refCurrentIndexCounter)
{
	ASSERT(0);
}

AExpression *CExpressionConstValue::Eval(CCompiler &refCompiler)
{
	ASSERT(0);
	return NULL;
}

CType CExpressionConstValue::GetType(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler) const
{
	ASSERT(0);
	return CType(DAEDALUS_TYPE_VOID);
}

void CExpressionConstValue::Optimize(CCompiler &refCompiler)
{
	ASSERT(0);
}

void CExpressionConstValue::Preprocess(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	this->pConstValue->Preprocess(refLocalVariables, pClass, refCompiler);
}*/