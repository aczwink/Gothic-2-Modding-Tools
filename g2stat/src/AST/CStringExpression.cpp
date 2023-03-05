//Class Header
#include "CStringExpression.h"
//Local
#include "../OptAST/CStringExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CStringExpression::CStringExpression(const CString &refLiteral, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->literal = refLiteral;
}

//Destructpr
CStringExpression::~CStringExpression()
{
	this->literal.Release();
}

//Public methods
OptAST::AExpression *CStringExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	return new OptAST::CStringExpression(this->literal);
}

CType CStringExpression::GetType() const
{
	return CType(DAEDALUS_TYPE_STRING);
}