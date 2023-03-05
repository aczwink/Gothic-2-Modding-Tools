//Class Header
#include "CStringExpression.h"
//Local
#include "../CCompiler.h"
#include "../Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CStringExpression::CStringExpression(const CString &refLiteral)
{
	this->literal = refLiteral;
}

//Destructor
CStringExpression::~CStringExpression()
{
	this->literal.Release();
}

//Private methods
const CString &CStringExpression::GetData(uint16 index) const
{
	return this->literal;
}

//Public methods
void CStringExpression::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.GetConstantStringSymbolIndex(this->literal, this);
}

void CStringExpression::Compile(CProgramBuffer &refProgram) const
{
	if(this->symbolIndex == 0xCDCDCDCD)
	{
		stdOut << "blasd";
	}
	
	refProgram.WriteByte(OPCODE_PUSHVAR);
	refProgram.WriteUInt32(this->symbolIndex);
}

AValueExpression *CStringExpression::Copy() const
{
	CStringExpression *pCopy;

	pCopy = new CStringExpression(this->literal);
	pCopy->symbolIndex = this->symbolIndex;
	
	return pCopy;
}

void CStringExpression::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, CString(), 0, 1, DAEDALUS_TYPE_STRING, 0, 0, UINT32_MAX);
}