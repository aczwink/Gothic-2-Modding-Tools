//Class Header
#include "CPrototype.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CPrototype.h"
#include "CStatements.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CPrototype::CPrototype(const CString &refName, const CString &refClassName, CStatements *pConstructorStatements, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->name = refName;
	this->className = refClassName;
	this->pConstructorStatements = pConstructorStatements;
}

//Destructor
CPrototype::~CPrototype()
{
	delete this->pConstructorStatements;
}

//Public methods
bool CPrototype::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CClass *pClass;
	OptAST::CPrototype *pPrototype;
	CMap<CString, OptAST::CLocalVariable *> localVariables;

	pClass = refCompiler.FindClass(this->className);
	
	pPrototype = new OptAST::CPrototype(this->name, pClass, this->GetFileName(), this->GetLineNumber());
	refCompiler.Add(pPrototype);
	
	return this->pConstructorStatements->Process(localVariables, pClass, NULL, refCompiler, pPrototype, refCallback);
}