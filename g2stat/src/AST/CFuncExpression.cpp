//Class Header
#include "CFuncExpression.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CFuncExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CFuncExpression::CFuncExpression(const CString &refFunctionName, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->functionName = refFunctionName;
}

//Public methods
OptAST::AExpression *CFuncExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	return new OptAST::CFuncExpression(refCompiler.FindFunction(this->functionName));
}

CType CFuncExpression::GetType() const
{
	return CType(DAEDALUS_TYPE_FUNC);
}