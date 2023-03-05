//Class Header
#include "CVariable.h"
//Local
#include "..\CCompiler.h"
#include "..\CType.h"
#include "../OptAST/CGlobalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CVariable::CVariable(CType *pType, const CString &refName) : AVariable(pType, CWString(), 0)
{
	this->name = refName;
}

//Destructor
CVariable::~CVariable()
{
	this->name.Release();
}

//Public methods
uint32 CVariable::GetSize() const
{
	return this->pType->GetSize();
}

bool CVariable::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CGlobalVariable *pVariable;
	CType type;
	
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
	
	pVariable = new OptAST::CGlobalVariable(type, this->name);
	refCompiler.Add(pVariable);

	return true;
}

bool CVariable::Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass)
{
	ASSERT(0);
	return true;
}

void CVariable::Unfold(CCompiler &refCompiler)
{
	refCompiler.AddUnprocessedVariable(this->name, this);
}

/*void CVariable::WriteSymbol(AOutputStream &refOutputStream, const CClass &refClass) const
{
	//class variable
	this->WriteSymbol(refOutputStream, CString(), refClass.GetOffset(this), this->pType->GetNumberOfElements(), this->pType->GetType(), DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR, 0, 0, 0, refClass.GetSymbolIndex());
}*/