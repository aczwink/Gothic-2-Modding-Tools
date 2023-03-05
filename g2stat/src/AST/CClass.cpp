//Class Header
#include "CClass.h"
//Local
#include "..\OptAST\CClass.h"
#include "..\CCompiler.h"
#include "CVariables.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CClass::CClass(const CString &refClassName, CVariables *pVariables, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->name = refClassName;
	this->pVariables = pVariables;
}

//Destructor
CClass::~CClass()
{
	delete this->pVariables;
}

//Public methods
void CClass::AddVariableAfter(AVariable *pNew, AVariable *pAfter)
{
	this->pVariables->AddVariableAfter(pNew, pAfter);
}

bool CClass::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CClass *pClass;
	
	pClass = new OptAST::CClass(this->name, this->GetFileName(), this->GetLineNumber());
	
	this->pVariables->Process(refCompiler, this, pClass);
	
	refCompiler.Add(pClass);

	return true;
}

void CClass::RemoveVariable(AVariable *pVariable)
{
	this->pVariables->RemoveVariable(pVariable);
}