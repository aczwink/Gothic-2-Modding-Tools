//Class Header
#include "CVariableArray.h"
//Local
#include "CArrayIndex.h"
#include "../CCompiler.h"
#include "..\CType.h"
#include "../OptAST/CClass.h"
#include "../OptAST/CGlobalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CVariableArray::CVariableArray(CType *pType, const CString &refIdentifier, CArrayIndex *pArraySize) : CVariable(pType, refIdentifier)
{
	this->pArraySize = pArraySize;
}

//Destructor
CVariableArray::~CVariableArray()
{
	delete this->pArraySize;
}

//Public methods
uint32 CVariableArray::GetSize() const
{
	return this->pType->GetSize();
}

bool CVariableArray::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CGlobalVariable *pVariable;
	
	this->pArraySize->Process(refCompiler);
	this->pType->SetNumberOfElements(this->pArraySize->GetIndex());
	
	pVariable = new OptAST::CGlobalVariable(*this->pType, this->GetName());
	refCompiler.Add(pVariable);

	return true;
}

bool CVariableArray::Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass)
{
	this->pArraySize->Process(refCompiler);
	this->pType->SetNumberOfElements(this->pArraySize->GetIndex());
	
	pOptClass->AddVariable(*this->pType, this->GetName());
	
	return true;
}