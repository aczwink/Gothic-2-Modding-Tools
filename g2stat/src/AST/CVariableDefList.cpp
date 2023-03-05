//Class Header
#include "CVariableDefList.h"
//Local
#include "..\CCompiler.h"
#include "CIdentifierList.h"
#include "CVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CVariableDefList::CVariableDefList(CType *pType, CIdentifierList *pNames) : AVariable(pType, CWString(), 0)
{
	this->pNames = pNames;
}

//Destructor
CVariableDefList::~CVariableDefList()
{
	delete this->pNames;
}

//Public methods
uint32 CVariableDefList::GetSize() const
{
	ASSERT(0);
	return 0;
}

bool CVariableDefList::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	ASSERT(0);
	return true;
}

bool CVariableDefList::Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass)
{
	const CLinkedList<CString> &refIdentifiers = this->pNames->GetIdentifiers();

	for(const CString &refIdentifier : refIdentifiers)
	{
		pOptClass->AddVariable(*this->pType, refIdentifier);
	}
	
	return false;
}

void CVariableDefList::Unfold(CCompiler &refCompiler)
{
	CVariable *pVariable;
	CType *pType;
	
	const CLinkedList<CString> &refIdentifiers = this->pNames->GetIdentifiers();
	
	foreach(it, refIdentifiers)
	{
		pType = new CType(*this->pType);
		pVariable = new CVariable(pType, *it);
		refCompiler.AddUnprocessedVariable((*it).ToLowercase(), pVariable);
	}
	
	delete this; //don't need this anymore
}