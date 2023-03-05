//Class Header
#include "CClassVariable.h"
//Local
#include "../CCompiler.h"
#include "CClass.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CClassVariable::CClassVariable(const CType &refType, const CString &refName, CClass &refClass) : refClass(refClass)
{
	this->type = refType;
	this->name = refName;
}

//Destructor
CClassVariable::~CClassVariable()
{
	//needs to be there because of virtual destructor
}

//Public methods
void CClassVariable::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.AddSymbol(this);
}

uint32 CClassVariable::GetOffset() const
{
	return this->refClass.GetOffset(this);
}

void CClassVariable::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, CString(), this->GetOffset(), this->type.GetNumberOfElements(), this->type.GetType(), DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR, 0, refClass.GetSymbolIndex());
}