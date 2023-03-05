//Class Header
#include "CCallStatement.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CCallExpression.h"
#include "../OptAST/CExprStatement.h"
#include "CExprList.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CCallStatement::CCallStatement(const CString &refFunctionName, CExprList *pArgs) : AStatement()
{
	this->functionName = refFunctionName;
	this->pArgs = pArgs;
}

//Destructor
CCallStatement::~CCallStatement()
{
	delete this->pArgs;
}

//Public methods
OptAST::AStatement *CCallStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CFunction *pFunction;
	OptAST::CCallExpression *pCallExpr;
	
	refCompiler.ProcessFunction(this->functionName);
	if(this->pArgs->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
	{
		pFunction = refCompiler.FindFunction(this->functionName);
		if(!this->pArgs->CheckCallTypes(pFunction, refCallback))
			return NULL;
		
		pCallExpr = new OptAST::CCallExpression(pFunction);
		this->pArgs->PutTranslatedExpressions(pCallExpr, refCompiler);
		
		return new OptAST::CExprStatement(pCallExpr);
	}
	
	return NULL;
}