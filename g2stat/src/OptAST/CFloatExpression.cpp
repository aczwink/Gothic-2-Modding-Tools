//Class Header
#include "CFloatExpression.h"
//Local
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CFloatExpression::CFloatExpression(float32 value)
{
	this->value = value;
}

//Public methods
void CFloatExpression::Compile(CProgramBuffer &refProgram) const
{
	int32 value;
	
	MemCopy(&value, &this->value, 4);
	refProgram.WriteByte(OPCODE_PUSHINT);
	refProgram.WriteInt32(value);
}

AValueExpression *CFloatExpression::Copy() const
{
	return new CFloatExpression(this->value);
}