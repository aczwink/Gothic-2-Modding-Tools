//Class Header
#include "CNotExpression.h"
//Local
#include "CIntExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CNotExpression::CNotExpression(AExpression *pSubExpr) : AUnaryExpression(pSubExpr)
{
}

//Private methods
EOpcode CNotExpression::GetOpcode() const
{
	return OPCODE_NOT;
}

//Public methods
AExpression *CNotExpression::GetOptimizedExpression(CCompiler &refCompiler)
{
	AExpression *pExpr;
	CIntExpression *pInt;
	
	pExpr = this->pSubExpression->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pSubExpression)
	{
		delete this->pSubExpression;
		this->pSubExpression = pExpr;
	}
	
	pInt = dynamic_cast<CIntExpression *>(this->pSubExpression);
	if(pInt)
		return new CIntExpression(!pInt->GetValue(), this->GetFileName(), this->GetLineNumber());
	
	return this;
}

CType CNotExpression::GetType() const
{
	ASSERT(0);
	return CType();
}