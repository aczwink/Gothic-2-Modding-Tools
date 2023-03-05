//Class Header
#include "CInstance.h"
//Local
#include "../OptAST/CInstance.h"
#include "..\CCompiler.h"
#include "CStatements.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CInstance::CInstance(const CString &refName, const CString &refClassName, CStatements *pStatements, const CWString &refFileName, uint32 lineNumber) : AInstance(refClassName, refFileName, lineNumber)
{
	this->name = refName;
	this->pStatements = pStatements;
}

//Destructor
CInstance::~CInstance()
{
	HeapDeleteSafe(this->pStatements);
}

//Public methods
bool CInstance::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CClass *pClass;
	OptAST::CPrototype *pPrototype;
	OptAST::CInstance *pInstance;
	CMap<CString, OptAST::CLocalVariable *> localVariables;
	
	pClass = NULL;
	pPrototype = NULL;
	
	//hm... shitty cyclic reference
	pInstance = new OptAST::CInstance(this->name, pClass, pPrototype, this->GetFileName(), this->GetLineNumber());
	refCompiler.Add(pInstance);
	
	if(refCompiler.ProcessPrototype(this->className))
	{
		pPrototype = refCompiler.FindPrototype(this->className);
		pClass = pPrototype->GetClass();

		pInstance->SetClass(pClass);
		pInstance->SetPrototype(pPrototype);
	}
	else if(refCompiler.ProcessClass(this->className))
	{
		pClass = refCompiler.FindClass(this->className);

		pInstance->SetClass(pClass);
	}
	else
	{
		ASSERT(0);
	}
	
	if(this->pStatements)
		return this->pStatements->Process(localVariables, pClass, pInstance, refCompiler, pInstance, refCallback);

	return true;
}

/*void CInstance::WriteSymbols(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->name, 0, 0, DAEDALUS_TYPE_INSTANCE, 0, this->constructorProgramOffset, 0, 0, UINT32_MAX);
}*/