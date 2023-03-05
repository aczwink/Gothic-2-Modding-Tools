/*4//Class Header
#include "CConstValues.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Constructor
CConstValues::CConstValues(AConstValue *pValue) : AConstValue(CWString(), 0)
{
	this->constValues.Push(pValue);
}

//Public methods
void CConstValues::Compile(AOutputStream &refOutputStream, CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}

AConstValue *CConstValues::Copy() const
{
	ASSERT(0);
	return NULL;
}

void CConstValues::DistributeSymbolIndices(uint32 &refCurrentIndexCounter)
{
	ASSERT(0);
}

AExpression *CConstValues::Eval(CCompiler &refCompiler)
{
	ASSERT(0);
	return NULL;
}

/*AConstValue *CConstValues::Eval(CCompiler &refCompiler)
{
	foreach(it, this->constValues)
	{
		ASSERT(it.GetValue()->Eval(refCompiler) == it.GetValue());
	}
	
	return this;
}

CType CConstValues::GetType(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler) const
{
	ASSERT(0);
	return CType(DAEDALUS_TYPE_VOID);
}

void CConstValues::Optimize(CCompiler &refCompiler)
{
	AExpression *pExpr;
	
	foreach(it, this->constValues)
	{
		pExpr = it.GetValue()->Eval(refCompiler);
		if(pExpr != it.GetValue())
			it.GetValue() = (AConstValue *)pExpr;
	}
}

void CConstValues::Preprocess(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}*/