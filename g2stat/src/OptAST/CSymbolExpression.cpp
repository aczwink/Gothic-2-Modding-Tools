//Class Header
#include "CSymbolExpression.h"
//Local
#include "../Opcodes.h"
#include "../OptAST/CInstance.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CSymbolExpression::CSymbolExpression(const ASymbol *pSymbol)
{
	this->pSymbol = pSymbol;
	this->hasIndex = false;
	
	if(!pSymbol)
	{
		stdOut << "CSymbolExpression::CSymbolExpression()";
	}
}

CSymbolExpression::CSymbolExpression(const ASymbol *pSymbol, uint8 index)
{
	this->pSymbol = pSymbol;
	this->hasIndex = true;
	this->index = index;
}

//Public methods
void CSymbolExpression::Compile(CProgramBuffer &refProgram) const
{
	if(this->pSymbol->GetSymbolIndex() == 0xCDCDCDCD)
	{
		stdOut << "here2" << endl;
	}

	if(this->hasIndex && this->index)
	{
		refProgram.WriteByte(OPCODE_PUSH_ARRAY_VAR);
		refProgram.WriteUInt32(this->pSymbol->GetSymbolIndex());
		refProgram.WriteByte(this->index);
	}
	else
	{
		refProgram.WriteByte(OPCODE_PUSHVAR);
		refProgram.WriteUInt32(this->pSymbol->GetSymbolIndex());
	}
}

AValueExpression *CSymbolExpression::Copy() const
{
	CSymbolExpression *pCopy;

	pCopy = new CSymbolExpression(this->pSymbol);
	pCopy->hasIndex = this->hasIndex;
	pCopy->index = this->index;
	//pCopy->isInstance = this->isInstance;
	pCopy->pSymbol = this->pSymbol;

	return pCopy;
}