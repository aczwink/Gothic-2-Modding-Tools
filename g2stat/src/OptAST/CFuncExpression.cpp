//Class Header
#include "CFuncExpression.h"
//Local
#include "../Opcodes.h"
#include "../OptAST/CInstance.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructors
CFuncExpression::CFuncExpression(const ASymbol *pSymbol)
{
	this->pSymbol = pSymbol;
	
	if(!pSymbol)
	{
		stdOut << "CFuncExpression::CFuncExpression()";
	}
}

//Public methods
void CFuncExpression::Compile(CProgramBuffer &refProgram) const
{
	if(this->pSymbol->GetSymbolIndex() == 0xCDCDCDCD)
	{
		stdOut << "CFuncExpression::Compile()" << endl;
	}
	
	refProgram.WriteByte(OPCODE_PUSHINT);
	refProgram.WriteUInt32(this->pSymbol->GetSymbolIndex());
}

AValueExpression *CFuncExpression::Copy() const
{
	CFuncExpression *pCopy;
	
	pCopy = new CFuncExpression(this->pSymbol);
	
	return pCopy;
}