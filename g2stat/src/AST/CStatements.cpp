//Class Header
#include "CStatements.h"
//Local
#include "../OptAST/AStatementContainer.h"
#include "AStatement.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CStatements::CStatements() : ANode(L"", 0)
{
}

//Destructor
CStatements::~CStatements()
{
	for(AStatement *pStatement : this->statements)
	{
		delete pStatement;
	}
}

//Public methods
bool CStatements::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, OptAST::AStatementContainer *pStmContainer, const ICompilerCallback &refCallback)
{
	OptAST::AStatement *pOptStatement;

	for(AStatement *pStatement : this->statements)
	{
		if(pStatement)
		{
			pOptStatement = pStatement->Process(refLocalVariables, pClass, pInstance, pStmContainer, refCompiler, refCallback);
			if(!pOptStatement)
				return false;
			pStmContainer->AddStatement(pOptStatement);
		}
	}

	return true;
}