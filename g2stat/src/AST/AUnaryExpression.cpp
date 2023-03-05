//Class Header
#include "AUnaryExpression.h"
//Local
#include "../OptAST/CUnaryExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AUnaryExpression::AUnaryExpression(AExpression *pSubExpression) : AExpression(CWString(), 0)
{
	this->pSubExpression = pSubExpression;
}

//Destructor
AUnaryExpression::~AUnaryExpression()
{
	delete this->pSubExpression;
}

//Public methods
OptAST::AExpression *AUnaryExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	OptAST::AExpression *pOptExpr;
	
	pOptExpr = this->pSubExpression->GetTranslatedExpression(refCompiler);
	
	return new OptAST::CUnaryExpression(this->GetOpcode(), pOptExpr);
}

bool AUnaryExpression::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	this->pSubExpression->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);

	return true;
}

void AUnaryExpression::SetCastTo(const CType &refType)
{
	ASSERT(0);
}