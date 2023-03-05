//Class Header
#include "CConstArrayExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CConstArrayExpression::CConstArrayExpression()
{
}

//Destructor
CConstArrayExpression::~CConstArrayExpression()
{
	for(AValueExpression *pExpr : this->constValues)
		delete pExpr;
	this->constValues.Release();
}

//Methods
void CConstArrayExpression::Compile(CProgramBuffer &refProgram) const
{
	ASSERT(0);
}

AValueExpression *CConstArrayExpression::Copy() const
{
	CConstArrayExpression *pCopy;

	pCopy = new CConstArrayExpression();
	for(AValueExpression *pExpr : this->constValues)
		pCopy->Add(pExpr->Copy());
	
	return pCopy;
}