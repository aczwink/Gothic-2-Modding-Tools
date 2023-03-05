//Class Header
#include "CArguments.h"
//Local
#include "../CCompiler.h"
#include "../CType.h"
#include "../OptAST/CFunction.h"
#include "../OptAST/CLocalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CArguments::CArguments(CType *pType, const CString &refName) : ANode(CWString(), 0)
{
	this->Add(pType, refName);
}

//Destructor
CArguments::~CArguments()
{
	for(const SArg &refArg : this->args)
		delete refArg.pType;
	this->args.Release();
}

//Public methods
void CArguments::Add(CType *pType, const CString &refName)
{
	SArg arg;
	
	arg.pType = pType;
	arg.name = refName;
	
	this->args.InsertFront(arg);
}

void CArguments::AddArgs(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CFunction *pFunction, CCompiler &refCompiler)
{
	OptAST::CLocalVariable *pVariable;
	CType type;
	
	for(const SArg &refArg : this->args)
	{
		if(refArg.pType->GetType() == DAEDALUS_TYPE_INSTANCE)
		{
			OptAST::CClass *pClass;
			
			pClass = refCompiler.FindClass(refArg.pType->GetClassName());
			type = CType(pClass->GetName());
		}
		else
		{
			type = *refArg.pType;
		}
		
		pVariable = new OptAST::CLocalVariable(type, refArg.name);
		refLocalVariables.Insert(pVariable->GetName().ToLowercase(), pVariable);
		pFunction->AddArgument(pVariable);
	}
}