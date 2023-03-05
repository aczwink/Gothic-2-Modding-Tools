//Class Header
#include "CIfStatement.h"
//Local
#include "../OptAST/CIfStatement.h"
#include "CElseIfs.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CIfStatement::CIfStatement(CElseIfs *pIfChain) : AStatement()
{
	this->pIfChain = pIfChain;
}

//Destructor
CIfStatement::~CIfStatement()
{
	delete this->pIfChain;
}

//Public methods
OptAST::AStatement *CIfStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CIfStatement *pOptStatement;
	
	pOptStatement = new OptAST::CIfStatement;
	
	if(!this->pIfChain->Process(refLocalVariables, pClass, pInstance, pOptStatement, refCompiler, refCallback))
	{
		delete pOptStatement;
		return NULL;
	}

	return pOptStatement;
}