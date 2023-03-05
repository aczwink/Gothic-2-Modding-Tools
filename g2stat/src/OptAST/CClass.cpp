//Class Header
#include "CClass.h"
//Local
#include "../CCompiler.h"
#include "CClassVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CClass::CClass(const CString &refName, const CWString &refFileName, uint32 lineNumber) : AGlobal(refName, refFileName, lineNumber)
{
}

//Destructor
CClass::~CClass()
{
	for(CClassVariable *pVariable : this->variables)
		delete pVariable;
	this->variables.Release();
}

//Private methods
uint32 CClass::GetBaseSize() const
{
	if(this->GetName() == "C_INFO")
		return 0;

	//subclass of AVob
	return 288;
}

//Public methods
void CClass::AddVariable(const CType &refType, const CString &refName)
{
	this->variables.InsertTail(new CClassVariable(refType, refName, *this));
}

void CClass::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.AddSymbol(this);
	
	for(CClassVariable *pVariable : this->variables)
		pVariable->CollectSymbols(refCompiler);
}

CClassVariable *CClass::FindVariable(const CString &refName) const
{
	for(CClassVariable *pVariable : this->variables)
	{
		if(pVariable->GetName() == refName)
			return pVariable;
	}

	return NULL;
}

uint32 CClass::GetOffset(const CClassVariable *pVariable) const
{
	uint32 offset;
	
	offset = this->GetBaseSize();
	for(CClassVariable *pVar : this->variables)
	{
		if(pVar == pVariable)
			break;
		offset += pVar->GetSize();
	}
	
	return offset;
}

void CClass::WriteSymbol(SJCLib::AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), this->GetSize(), this->variables.GetNoOfElements(), DAEDALUS_TYPE_CLASS, 0, 0, 0);
}