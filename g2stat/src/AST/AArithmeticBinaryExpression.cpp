//Class Header
#include "AArithmeticBinaryExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AArithmeticBinaryExpression::AArithmeticBinaryExpression(AExpression *pLeft, AExpression *pRight) : ABinaryExpression(pLeft, pRight)
{
}

//Public methods
CType AArithmeticBinaryExpression::GetType() const
{
	bool needsCast;
	
	const CType &refLeftType = this->pLeft->GetType();
	const CType &refRightType = this->pRight->GetType();
	
	ASSERT(refLeftType.IsConvertableTo(refRightType, needsCast));
	
	return refLeftType;
}