//Class Header
#include "CInstance.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CInstance::CInstance(const CString &refName, CClass *pClass, CPrototype *pPrototype, const CWString &refFileName, uint32 lineNumber) : AGlobal(refName, refFileName, lineNumber)
{
	this->pClass = pClass;
	this->pPrototype = pPrototype;
}

//Public methods
void CInstance::CollectSymbols(CCompiler &refCompiler)
{
	for(AStatement *pStatement : this->statements)
		pStatement->CollectSymbols(refCompiler);
	
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CInstance::Compile(CProgramBuffer &refProgram)
{
	this->constructorProgramOffset = refProgram.GetCurrentOffset();

	if(this->pPrototype) //compile prototype constructor
		this->pPrototype->CompileCallTo(refProgram);

	for(AStatement *pStatement : this->statements)
		pStatement->Compile(refProgram);
	
	refProgram.WriteByte(OPCODE_RETURN); //Always put a return statement at the end of a constructor
}

void CInstance::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), 0, 0, DAEDALUS_TYPE_INSTANCE, 0, this->constructorProgramOffset, UINT32_MAX);
}