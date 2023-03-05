//Class Header
#include "CExternal.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
#include "CLocalVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CExternal::CExternal(const CType &refRetType, const CString &refName, uint32 externalProgramOffset) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
}

CExternal::CExternal(const CType &refRetType, const CString &refName, uint32 externalProgramOffset, const CType &refParam1Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
	this->AddArgument(new CLocalVariable(refParam4Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
	this->AddArgument(new CLocalVariable(refParam4Type, CString()));
	this->AddArgument(new CLocalVariable(refParam5Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
	this->AddArgument(new CLocalVariable(refParam4Type, CString()));
	this->AddArgument(new CLocalVariable(refParam5Type, CString()));
	this->AddArgument(new CLocalVariable(refParam6Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type, const CType &refParam7Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
	this->AddArgument(new CLocalVariable(refParam4Type, CString()));
	this->AddArgument(new CLocalVariable(refParam5Type, CString()));
	this->AddArgument(new CLocalVariable(refParam6Type, CString()));
	this->AddArgument(new CLocalVariable(refParam7Type, CString()));
}

CExternal::CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type, const CType &refParam7Type, const CType &refParam8Type) : CFunction(refRetType, refName, CWString(), 0)
{
	this->externalProgramOffset = externalProgramOffset;
	this->AddArgument(new CLocalVariable(refParam1Type, CString()));
	this->AddArgument(new CLocalVariable(refParam2Type, CString()));
	this->AddArgument(new CLocalVariable(refParam3Type, CString()));
	this->AddArgument(new CLocalVariable(refParam4Type, CString()));
	this->AddArgument(new CLocalVariable(refParam5Type, CString()));
	this->AddArgument(new CLocalVariable(refParam6Type, CString()));
	this->AddArgument(new CLocalVariable(refParam7Type, CString()));
	this->AddArgument(new CLocalVariable(refParam8Type, CString()));
}

//Destructor
CExternal::~CExternal()
{
}

//Public methods
void CExternal::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CExternal::Compile(CProgramBuffer &refProgram)
{
}

void CExternal::CompileCallTo(CProgramBuffer &refProgram)
{
	refProgram.WriteByte(OPCODE_CALLEXTERNAL);
	refProgram.WriteUInt32(this->symbolIndex);
}

void CExternal::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), this->retType.GetType(), 0, DAEDALUS_TYPE_FUNC, 0, this->externalProgramOffset, UINT32_MAX);
}