//Class Header
#include "CIfAlternative.h"
//Local
#include "../Opcodes.h"
#include "AExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CIfAlternative::CIfAlternative(AExpression *pCondition)
{
	this->pCondition = pCondition;
}

//Destructor
CIfAlternative::~CIfAlternative()
{
	HeapDeleteSafe(this->pCondition);
}

//Public methods
void CIfAlternative::CollectSymbols(CCompiler &refCompiler)
{
	if(this->pCondition)
		this->pCondition->CollectSymbols(refCompiler);

	for(AStatement *pStatement : this->statements)
		pStatement->CollectSymbols(refCompiler);
}

void CIfAlternative::Compile(CProgramBuffer &refProgram, CArray<uint32> &refEndOfChainInsertOffsets)
{
	bool hasCondition;
	uint32 jumpAddressOffset;
	
	hasCondition = false;
	
	//compile the condition
	if(this->pCondition) //else{}-statement has no condition
	{
		this->pCondition->Compile(refProgram);

		refProgram.WriteByte(OPCODE_JUMP_IF);
		jumpAddressOffset = refProgram.GetCurrentOffset();
		refProgram.WriteUInt32(0); //reserve space for real address
		hasCondition = true;
	}

	//compile body
	for(AStatement *pStatement : this->statements)
		pStatement->Compile(refProgram);

	//jump out of chain
	refProgram.WriteByte(OPCODE_JUMP);
	refEndOfChainInsertOffsets.Push(refProgram.GetCurrentOffset()); //we need the offset
	refProgram.WriteUInt32(0); //reserve space for address

	//set end address of alternative
	if(hasCondition)
		refProgram.WriteAt(jumpAddressOffset, refProgram.GetCurrentOffset());
}