//Class Header
#include "CCallExpression.h"
//Local
#include "../Opcodes.h"
#include "../OptAST/CFunction.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CCallExpression::CCallExpression(CFunction *pFunction)
{
	if(!pFunction)
	{
		stdOut << "here";
	}

	this->pFunction = pFunction;
}

//Destructor
CCallExpression::~CCallExpression()
{
	for(AExpression *pExpr : this->callArgs)
		delete pExpr;
}

//Public methods
void CCallExpression::CollectSymbols(CCompiler &refCompiler)
{
	for(AExpression *pExpr : this->callArgs)
		pExpr->CollectSymbols(refCompiler);
}

void CCallExpression::Compile(CProgramBuffer &refProgram) const
{
	for(AExpression *pExpr : this->callArgs)
		pExpr->Compile(refProgram);
	
	this->pFunction->CompileCallTo(refProgram);
}