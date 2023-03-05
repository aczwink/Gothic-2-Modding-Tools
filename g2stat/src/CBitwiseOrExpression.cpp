/*//Class Header
#include "CBitwiseOrExpression.h"
//Local
#include "CConstValueInt.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Constructor
CBitwiseOrExpression::CBitwiseOrExpression(AExpression *pLeft, AExpression *pRight) : ABinaryExpression(pLeft, pRight)
{
}

//Public methods
void CBitwiseOrExpression::Compile(AOutputStream &refOutputStream, CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}

AExpression *CBitwiseOrExpression::Copy() const
{
	ASSERT(0);
	return NULL;
}

void CBitwiseOrExpression::DistributeSymbolIndices(uint32 &refCurrentIndexCounter)
{
	ASSERT(0);
}

AExpression *CBitwiseOrExpression::Eval(CCompiler &refCompiler)
{
	int32 value;
	AExpression *pExpr;
	
	//try to eval left
	pExpr = this->pLeft->Eval(refCompiler);
	if(!pExpr) //can't be evaluated
		return NULL;
	if(pExpr != this->pLeft)
	{
		delete this->pLeft;
		this->pLeft = pExpr;
	}

	pExpr = this->pRight->Eval(refCompiler);
	if(!pExpr)
		return NULL;
	if(pExpr != this->pRight)
	{
		delete this->pRight;
		this->pRight = pExpr;
	}

	ASSERT(dynamic_cast<CConstValueInt *>(this->pLeft));
	ASSERT(dynamic_cast<CConstValueInt *>(this->pRight));
	
	value = (((CConstValueInt *)this->pLeft)->GetValue() | ((CConstValueInt *)this->pRight)->GetValue());
	
	return new CConstValueInt(value);
}

CType CBitwiseOrExpression::GetType(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler) const
{
	ASSERT(0);
	return CType(DAEDALUS_TYPE_VOID);
}

void CBitwiseOrExpression::Optimize(CCompiler &refCompiler)
{
	ASSERT(0);
}

void CBitwiseOrExpression::Preprocess(CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	ASSERT(0);
}*/