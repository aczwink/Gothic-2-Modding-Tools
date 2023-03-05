//Class Header
#include "CDeclarationStatement.h"
//Local
#include "../CCompiler.h"
#include "../CType.h"
#include "../OptAST/CDeclarationStatement.h"
#include "../OptAST/CLocalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CDeclarationStatement::CDeclarationStatement(CType *pType, const CString &refVarName) : AStatement()
{
	this->pType = pType;
	this->varName = refVarName;
}

//Destructor
CDeclarationStatement::~CDeclarationStatement()
{
	delete this->pType;
}

//Public methods
OptAST::AStatement *CDeclarationStatement::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	CType type;
	OptAST::CLocalVariable *pVariable;
	
	if(this->pType->GetType() == DAEDALUS_TYPE_INSTANCE)
	{
		OptAST::CClass *pClass;
		
		pClass = refCompiler.FindClass(this->pType->GetClassName());
		type = CType(pClass->GetName());
	}
	else
	{
		type = *this->pType;
	}
	
	pVariable = new OptAST::CLocalVariable(type, this->varName);
	refLocalVariables.Insert(pVariable->GetName().ToLowercase(), pVariable);
	
	return new OptAST::CDeclarationStatement(pVariable);
}