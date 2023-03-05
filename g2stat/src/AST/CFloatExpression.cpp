//Class Header
#include "CFloatExpression.h"
//Local
#include "../OptAST/CFloatExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CFloatExpression::CFloatExpression(float32 value, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->value = value;
}

//Public methods
OptAST::AExpression *CFloatExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	return new OptAST::CFloatExpression(this->value);
}

CType CFloatExpression::GetType() const
{
	return CType(DAEDALUS_TYPE_FLOAT);
}