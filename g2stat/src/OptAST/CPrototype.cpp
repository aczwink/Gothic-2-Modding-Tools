//Class Header
#include "CPrototype.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CPrototype::CPrototype(const CString &refName, CClass *pClass, const CWString &refFileName, uint32 lineNumber) : AGlobal(refName, refFileName, lineNumber)
{
	this->isCompiled = false;
	this->pClass = pClass;
}

//Public methods
void CPrototype::CollectSymbols(CCompiler &refCompiler)
{
	for(AStatement *pStatement : this->statements)
		pStatement->CollectSymbols(refCompiler);
	
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CPrototype::Compile(CProgramBuffer &refProgram)
{
	this->constructorProgramOffset = refProgram.GetCurrentOffset();
	
	for(AStatement *pStatement : this->statements)
		pStatement->Compile(refProgram);
	
	//Always put a return statement at the end of a prototype constructor
	refProgram.WriteByte(OPCODE_RETURN);
	
	//finishing stuff
	this->isCompiled = true;
	foreach(it, this->callProgramOffsets)
	{
		refProgram.WriteAt(it.GetValue(), this->constructorProgramOffset);
	}
	this->callProgramOffsets.Release();
}

void CPrototype::CompileCallTo(CProgramBuffer &refProgram)
{
	refProgram.WriteByte(OPCODE_CALL);
	if(this->isCompiled)
	{
		refProgram.WriteUInt32(this->constructorProgramOffset);
	}
	else
	{
		//insert later
		this->callProgramOffsets.Push(refProgram.GetCurrentOffset());
		refProgram.WriteUInt32(0); //reserve the place
	}
}

void CPrototype::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, CString(), 0, 0, DAEDALUS_TYPE_PROTOTYPE, 0, this->constructorProgramOffset, UINT32_MAX);
}