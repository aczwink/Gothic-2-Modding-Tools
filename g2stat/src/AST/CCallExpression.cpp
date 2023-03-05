//Class Header
#include "CCallExpression.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CCallExpression.h"
#include "CExprList.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CCallExpression::CCallExpression(const CString &refFunctionName, CExprList *pArgs) : AExpression(CWString(), 0)
{
	this->functionName = refFunctionName;
	this->pArgs = pArgs;
}

//Destructor
CCallExpression::~CCallExpression()
{
	delete this->pArgs;
}

//Public methods
AExpression *CCallExpression::GetOptimizedExpression(CCompiler &refCompiler)
{
	this->pArgs->Optimize(refCompiler);
	
	return this;
}

OptAST::AExpression *CCallExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	OptAST::CCallExpression *pExpr;
	
	pExpr = new OptAST::CCallExpression(refCompiler.FindFunction(this->functionName));
	this->pArgs->PutTranslatedExpressions(pExpr, refCompiler);
	
	return pExpr;
}

CType CCallExpression::GetType() const
{
	return this->pFunction->GetReturnType();
}

bool CCallExpression::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	refCompiler.ProcessFunction(this->functionName);
	if(!this->pArgs->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
		return false;
	
	this->pFunction = refCompiler.FindFunction(this->functionName);
	if(!this->pArgs->CheckCallTypes(this->pFunction, refCallback))
		return false;
	
	return true;
}

void CCallExpression::SetCastTo(const CType &refType)
{
	ASSERT(0);
}