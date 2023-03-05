//Class Header
#include "CExprList.h"
//Local
#include "../OptAST/CCallExpression.h"
#include "../OptAST/CConstArrayExpression.h"
#include "../OptAST/CFunction.h"
#include "../OptAST/CLocalVariable.h"
#include "AExpression.h"
#include "AValueExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CExprList::CExprList() : ANode(CWString(), 0)
{
}

CExprList::CExprList(AExpression *pValue) : ANode(CWString(), 0)
{
	this->expressions.InsertTail(pValue);
}

//Destructor
CExprList::~CExprList()
{
	for(AExpression *pExpr : this->expressions)
		delete pExpr;
	this->expressions.Release();
}

//Public methods
bool CExprList::CheckCallTypes(OptAST::CFunction *pFunction, const ICompilerCallback &refCallback)
{
	bool needsCast;
	const CLinkedList<OptAST::CLocalVariable *> &refFormalParameters = pFunction->GetFormalParameters();
	
	if(this->expressions.GetNoOfElements() != refFormalParameters.GetNoOfElements())
	{
		ASSERT(0);
		return false;
	}
	
	auto &refIt = refFormalParameters.Begin();
	for(AExpression *pExpr : this->expressions)
	{
		if(!pExpr->GetType().IsConvertableTo((*refIt)->GetType(), needsCast))
		{
			refCallback.OnTypeMismatch(pExpr->GetType(), (*refIt)->GetType(), pExpr->GetFileName(), pExpr->GetLineNumber());
			return false;
		}
		if(needsCast)
			pExpr->SetCastTo((*refIt)->GetType());
		++refIt;
	}
	
	return true;
}

OptAST::CConstArrayExpression *CExprList::GetTranslatedExpression(CCompiler &refCompiler)
{
	OptAST::CConstArrayExpression *pConstArr;

	pConstArr = new OptAST::CConstArrayExpression();

	for(AExpression *pExpr : this->expressions)
	{
		pConstArr->Add((OptAST::AValueExpression *)pExpr->GetTranslatedExpression(refCompiler));
	}

	return pConstArr;
}

bool CExprList::Optimize(CCompiler &refCompiler)
{
	bool isConstant;
	AExpression *pOpt;
	
	isConstant = true;
	
	for(AExpression *&refpExpr : this->expressions)
	{
		pOpt = refpExpr->GetOptimizedExpression(refCompiler);
		if(pOpt != refpExpr)
		{
			//value was optimized
			delete refpExpr;
			refpExpr = pOpt;
		}
		
		if(!dynamic_cast<AValueExpression *>(refpExpr))
			isConstant = false;
	}

	return isConstant;
}

void CExprList::PutTranslatedExpressions(OptAST::CCallExpression *pCallExpr, CCompiler &refCompiler)
{
	for(AExpression *pExpr : this->expressions)
	{
		pCallExpr->Add(pExpr->GetTranslatedExpression(refCompiler));
	}
}

bool CExprList::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	for(AExpression *pExpr : this->expressions)
	{
		if(!pExpr->Process(refLocalVariables, NULL, NULL, refCompiler, refCallback))
			return false;
	}

	return true;
}