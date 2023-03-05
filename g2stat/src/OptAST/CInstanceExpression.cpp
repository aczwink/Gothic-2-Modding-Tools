//Class Header
#include "CInstanceExpression.h"
//Local
#include "../Opcodes.h"
#include "../OptAST/CInstance.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructors
CInstanceExpression::CInstanceExpression(const ASymbol *pSymbol)
{
	this->pSymbol = pSymbol;
	
	if(!pSymbol)
	{
		stdOut << "CInstanceExpression::CInstanceExpression()";
	}
}

//Public methods
void CInstanceExpression::Compile(CProgramBuffer &refProgram) const
{
	if(this->pSymbol->GetSymbolIndex() == 0xCDCDCDCD)
	{
		stdOut << "CInstanceExpression::Compile()" << endl;
	}
	
	refProgram.WriteByte(OPCODE_PUSHINSTANCE);
	refProgram.WriteUInt32(this->pSymbol->GetSymbolIndex());
}

AValueExpression *CInstanceExpression::Copy() const
{
	CInstanceExpression *pCopy;
	
	pCopy = new CInstanceExpression(this->pSymbol);
	
	return pCopy;
}