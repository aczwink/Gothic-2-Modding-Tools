//Class Header
#include "CElseIfs.h"
//Local
#include "../OptAST/CIfAlternative.h"
#include "../OptAST/CIfStatement.h"
#include "AExpression.h"
#include "CStatements.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CElseIfs::CElseIfs() : ANode(CWString(), 0)
{
}

CElseIfs::CElseIfs(AExpression *pConditionExpr, CStatements *pNestedStatements) : ANode(CWString(), 0)
{
	this->AddFront(pConditionExpr, pNestedStatements);
}

//Destructor
CElseIfs::~CElseIfs()
{
	for(const SIfEntry &refEntry : this->ifChain)
	{
		delete refEntry.pConditionExpr;
		delete refEntry.pNestedStatements;
	}
	this->ifChain.Release();
}

//Public methods
void CElseIfs::AddFront(AExpression *pConditionExpr, CStatements *pNestedStatements)
{
	SIfEntry entry;

	entry.pConditionExpr = pConditionExpr;
	entry.pNestedStatements = pNestedStatements;

	this->ifChain.InsertFront(entry);
}

bool CElseIfs::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::CIfStatement *pIfChainContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	AExpression *pOptExpr;
	OptAST::AExpression *pOptCondition;
	OptAST::CIfAlternative *pAlternative;
	
	for(SIfEntry &refEntry : this->ifChain)
	{
		if(refEntry.pConditionExpr)
		{
			if(!refEntry.pConditionExpr->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
				return false;
			pOptExpr = refEntry.pConditionExpr->GetOptimizedExpression(refCompiler);
			if(refEntry.pConditionExpr != pOptExpr)
			{
				delete refEntry.pConditionExpr;
				refEntry.pConditionExpr = pOptExpr;
			}
			
			pOptCondition = refEntry.pConditionExpr->GetTranslatedExpression(refCompiler);
		}
		else
		{
			pOptCondition = NULL;
		}
		
		pAlternative = new OptAST::CIfAlternative(pOptCondition);

		//there is no scope between if alternatives, so use same local variables map
		if(!refEntry.pNestedStatements->Process(refLocalVariables, pClass, pInstance, refCompiler, pAlternative, refCallback))
			return false;
		pIfChainContainer->AddAlternative(pAlternative);
	}

	return true;
}