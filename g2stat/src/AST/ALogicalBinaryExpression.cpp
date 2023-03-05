//Class Header
#include "ALogicalBinaryExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
ALogicalBinaryExpression::ALogicalBinaryExpression(AExpression *pLeft, AExpression *pRight) : ABinaryExpression(pLeft, pRight)
{
}

//Public methods
CType ALogicalBinaryExpression::GetType() const
{
	return DAEDALUS_TYPE_INT;
}