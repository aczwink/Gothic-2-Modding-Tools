//Class Header
#include "CIntExpression.h"
//Local
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CIntExpression::CIntExpression(int32 value)
{
	this->value = value;
}

//Public methods
void CIntExpression::Compile(CProgramBuffer &refProgram) const
{
	refProgram.WriteByte(OPCODE_PUSHINT);
	refProgram.WriteInt32(this->value);
}

AValueExpression *CIntExpression::Copy() const
{
	return new CIntExpression(this->value);
}