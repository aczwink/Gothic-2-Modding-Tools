//Class Header
#include "CIntExpression.h"
//Local
#include "../OptAST/CIntExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CIntExpression::CIntExpression(int32 value, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->value = value;
}

//Public methods
OptAST::AExpression *CIntExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	return new OptAST::CIntExpression(this->value);
}

CType CIntExpression::GetType() const
{
	return CType(DAEDALUS_TYPE_INT);
}