//Class Header
#include "CFunction.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
#include "../OptAST/CLocalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CFunction::CFunction(const CType &refRetType, const CString &refName, const CWString &refFileName, uint32 lineNumber) : AGlobal(refName, refFileName, lineNumber)
{
	this->retType = refRetType;
	this->isCompiled = false;
}

//Destructor
CFunction::~CFunction()
{
	for(CLocalVariable *pVariable : this->arguments)
		delete pVariable;
}

//Public methods
void CFunction::CollectSymbols(CCompiler &refCompiler)
{
	for(CLocalVariable *pVariable : this->arguments)
		pVariable->CollectSymbols(refCompiler);
	
	for(AStatement *pStatement : this->statements)
		pStatement->CollectSymbols(refCompiler);
	
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CFunction::Compile(CProgramBuffer &refProgram)
{
	CLinkedList<CLocalVariable *> formalParametersReversed;
	
	this->programOffset = refProgram.GetCurrentOffset();
	
	for(CLocalVariable *pVariable : this->arguments)
		formalParametersReversed.InsertFront(pVariable);

	for(CLocalVariable *pVariable : formalParametersReversed)
		pVariable->CompileAssign(refProgram);
	
	for(AStatement *pStatement : this->statements)
		pStatement->Compile(refProgram);
	
	refProgram.WriteByte(OPCODE_RETURN); //always put a return statement at end of a function

	//finishing stuff
	this->isCompiled = true;
	foreach(it, this->callProgramOffsets)
	{
		refProgram.WriteAt(it.GetValue(), this->programOffset);
	}
	this->callProgramOffsets.Release();
}

void CFunction::CompileCallTo(CProgramBuffer &refProgram)
{
	refProgram.WriteByte(OPCODE_CALL);
	if(this->isCompiled)
	{
		refProgram.WriteUInt32(this->programOffset);
	}
	else
	{
		//insert later
		this->callProgramOffsets.Push(refProgram.GetCurrentOffset());
		refProgram.WriteUInt32(0); //reserve the place
	}
}

void CFunction::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), this->retType.GetType(), 0, DAEDALUS_TYPE_FUNC, 0, this->programOffset, UINT32_MAX);
}