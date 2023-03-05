//Class Header
#include "CFunction.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CFunction.h"
#include "CArguments.h"
#include "CStatements.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CFunction::CFunction(CType *pRetType, const CString &refName, CArguments *pArgs, CStatements *pStatements, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->pRetType = pRetType;
	this->name = refName;
	this->pArgs = pArgs;
	this->pStatements = pStatements;
}

//Destructor
CFunction::~CFunction()
{
	delete this->pRetType;
	delete this->pArgs;
	delete this->pStatements;
}

//Public methods
bool CFunction::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	OptAST::CFunction *pFunction;
	CMap<CString, OptAST::CLocalVariable *> localVariables;
	
	pFunction = new OptAST::CFunction(*this->pRetType, this->name, this->GetFileName(), this->GetLineNumber());
	refCompiler.Add(pFunction);
	if(this->pArgs)
		this->pArgs->AddArgs(localVariables, pFunction, refCompiler);
	if(this->pStatements)
		return this->pStatements->Process(localVariables, NULL, NULL, refCompiler, pFunction, refCallback);
	
	return true;
}