//Class Header
#include "CMinusExpression.h"
//Local
#include "CIntExpression.h"
#include "CFloatExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CMinusExpression::CMinusExpression(AExpression *pSubExpr) : AUnaryExpression(pSubExpr)
{
}

//Private methods
EOpcode CMinusExpression::GetOpcode() const
{
	return OPCODE_UNARYMINUS;
}

//Public methods
AExpression *CMinusExpression::GetOptimizedExpression(CCompiler &refCompiler)
{
	AExpression *pExpr;
	CIntExpression *pInt;
	CFloatExpression *pFloat;
	
	pExpr = this->pSubExpression->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pSubExpression)
	{
		delete this->pSubExpression;
		this->pSubExpression = pExpr;
	}

	pInt = dynamic_cast<CIntExpression *>(this->pSubExpression);
	if(pInt)
		return new CIntExpression(-pInt->GetValue(), this->GetFileName(), this->GetLineNumber());
	pFloat = dynamic_cast<CFloatExpression *>(this->pSubExpression);
	if(pFloat)
		return new CFloatExpression(-pFloat->GetValue(), this->GetFileName(), this->GetLineNumber());

	return this;
}

CType CMinusExpression::GetType() const
{
	//float or int
	return this->pSubExpression->GetType();
}