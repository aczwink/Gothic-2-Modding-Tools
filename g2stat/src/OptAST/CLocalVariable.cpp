//Class Header
#include "CLocalVariable.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CLocalVariable::CLocalVariable(const CType &refType, const CString &refName) : AGlobal(refName, CWString(), 0)
{
	this->type = refType;
}

//Public methods
void CLocalVariable::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CLocalVariable::CompileAssign(CProgramBuffer &refProgram)
{
	switch(this->type.GetType())
	{
	case DAEDALUS_TYPE_INT:
		refProgram.WriteByte(OPCODE_PUSHVAR);
		refProgram.WriteUInt32(this->symbolIndex);
		refProgram.WriteByte(OPCODE_ASSIGN);
		break;
	case DAEDALUS_TYPE_STRING:
		refProgram.WriteByte(OPCODE_PUSHVAR);
		refProgram.WriteUInt32(this->symbolIndex);
		refProgram.WriteByte(OPCODE_ASSIGN_STRING);
		break;
	case DAEDALUS_TYPE_INSTANCE:
		refProgram.WriteByte(OPCODE_PUSHINSTANCE);
		refProgram.WriteUInt32(this->symbolIndex);
		refProgram.WriteByte(OPCODE_ASSIGN_INSTANCE);
		break;
	}
}

void CLocalVariable::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), 0, this->type.GetNumberOfElements(), this->type.GetType(), 0, 0, UINT32_MAX);
}