//Class Header
#include "AValueExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AValueExpression::AValueExpression(const CWString &refFileName, uint32 lineNumber) : AExpression(refFileName, lineNumber)
{
}

//Public methods
AExpression *AValueExpression::GetOptimizedExpression(CCompiler &refCompiler)
{
	//this is a leaf and can't be optimized
	
	return this;
}

bool AValueExpression::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	//nothing to be done
	return true;
}

void AValueExpression::SetCastTo(const CType &refType)
{
}