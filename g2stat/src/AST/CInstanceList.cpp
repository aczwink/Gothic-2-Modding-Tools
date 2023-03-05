//Class Header
#include "CInstanceList.h"
//Local
#include "..\CCompiler.h"
#include "CIdentifierList.h"
#include "CInstance.h"
#include "CStatements.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CInstanceList::CInstanceList(CIdentifierList *pNames, const CString &refClassName, CStatements *pStatements, const CWString &refFileName, uint32 lineNumber) : AInstance(refClassName, refFileName, lineNumber)
{
	this->pNames = pNames;
	this->pStatements = pStatements;
}

//Destructor
CInstanceList::~CInstanceList()
{
	delete this->pNames;
	HeapDeleteSafe(this->pStatements);
}

//Public methods
bool CInstanceList::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	ASSERT(0);
	return true;
}

void CInstanceList::Unfold(CCompiler &refCompiler)
{
	CInstance *pInstance, *pProgramSibling;
	CStatements *pStatements;
	
	const CLinkedList<CString> &refIdentifiers = this->pNames->GetIdentifiers();

	pProgramSibling = NULL;
	pStatements = this->pStatements;
	
	foreach(it, refIdentifiers)
	{
		pInstance = new CInstance(*it, this->GetClassName(), pStatements, this->GetFileName(), this->GetLineNumber());
		if(!pProgramSibling)
		{
			pProgramSibling = pInstance;
		}
		else
		{
			pInstance->SetProgramSibling(pProgramSibling->GetName());
		}
		refCompiler.AddUnprocessedInstance((*it).ToLowercase(), pInstance);

		pStatements = NULL;
	}

	this->pStatements = NULL; //so that destructor does not delete it
	delete this; //don't need this anymore
}