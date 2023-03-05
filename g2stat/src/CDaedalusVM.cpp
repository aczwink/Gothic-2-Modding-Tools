//Class Header
#include "CDaedalusVM.h"
//Global
#include <iostream>
#include <ctime>
//Local
#include "AVob.h"
#include "CDaedalusProgram.h"
#include "CNPC.h"
#include "Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Constructor
CDaedalusVM::CDaedalusVM(CDaedalusProgram *pProgram)
{
	this->pProgram = pProgram;

	srand((uint32)time(NULL)); //Init random number generator
	this->selfSymbolIndex = this->pProgram->FindSymbol("self");
	this->instance_helpSymbolIndex = this->pProgram->FindSymbol("ÿINSTANCE_HELP");
}

//Destructor
CDaedalusVM::~CDaedalusVM()
{
}

//Private Functions
int32 CDaedalusVM::PopInt()
{
	switch(this->dataStack.Pop())
	{
	case OPCODE_PUSHINT:
		return (int32)this->dataStack.Pop();
	case OPCODE_PUSHVAR:
		return *((int32 *)this->dataStack.Pop());
	default:
		return 0;
	}
}

CString *CDaedalusVM::PopString()
{
	this->dataStack.Pop();
	
	return (CString *)this->dataStack.Pop();
}

void *CDaedalusVM::PopVar()
{
	switch(this->dataStack.Pop())
	{
	case OPCODE_PUSHVAR:
		return (void *)this->dataStack.Pop();
	default:
		ASSERT(0);
		this->dataStack.Pop();
		return 0;
	}
}

void CDaedalusVM::PushInt(int32 value)
{
	this->dataStack.Push(value);
	this->dataStack.Push(OPCODE_PUSHINT);
}

void CDaedalusVM::PushVar(void *pVar)
{
	this->dataStack.Push((uint64)pVar);
	this->dataStack.Push(OPCODE_PUSHVAR);
}

//Public Functions
void CDaedalusVM::Run(uint32 offset)
{
	register const byte *pc;
	CArray<const byte *> callStack;

	pc = &this->pProgram->GetProgram()[offset];

	/*
	Implementation as of NicoDE's specification
	Should be equal to Gothic2 Engine VM
	*/
	
	while(true)
	{
		switch(*pc++)
		{
		case OPCODE_ADD:
			{
				this->PushInt(this->PopInt() + this->PopInt());
			}
			break;
		case OPCODE_SUBTRACT:
			{
				int32 left;
				
				left = this->PopInt();

				this->PushInt(left - this->PopInt());
			}
			break;
		case OPCODE_MULTIPLICATE:
			{
				this->PushInt(this->PopInt() * this->PopInt());
			}
			break;
		case OPCODE_DIVIDE:
			{
				int32 left;
				
				left = this->PopInt();
				
				this->PushInt(left / this->PopInt());
			}
			break;
		case OPCODE_MODULO:
			{
				int32 left;
				
				left = this->PopInt();
				
				this->PushInt(left % this->PopInt());
			}
			break;
		case OPCODE_BITWISEOR:
			{
				this->PushInt(this->PopInt() | this->PopInt());
			}
			break;
		case OPCODE_BITWISEAND:
			{
				this->PushInt(this->PopInt() & this->PopInt());
			}
			break;
		case OPCODE_LESSTHAN:
			{
				int32 left;
				
				left = this->PopInt();
				
				this->PushInt(left < this->PopInt());
			}
			break;
		case OPCODE_GREATERTHAN:
			{
				int32 left;
				
				left = this->PopInt();
				
				this->PushInt(left > this->PopInt());
			}
			break;
		case OPCODE_ASSIGN:
			{
				int32 *pVar;
				
				pVar = (int32 *)this->PopVar();
				*pVar = this->PopInt();
			}
			break;
		case OPCODE_LOGICALOR:
			{
				register int32 left, right;

				left = this->PopInt();
				right = this->PopInt();
				this->PushInt(left || right);
			}
			break;
		case OPCODE_LOGICALAND:
			{
				register int32 left, right;

				left = this->PopInt();
				right = this->PopInt();
				this->PushInt(left && right);
			}
			break;
		case OPCODE_LESSTHANOREQUALTO:
			{
				int32 left;

				left = this->PopInt();

				this->PushInt(left <= this->PopInt());
			}
			break;
		case OPCODE_EQUALS:
			{
				this->PushInt(this->PopInt() == this->PopInt());
			}
			break;
		case OPCODE_NOTEQUALS:
			{
				this->PushInt(this->PopInt() != this->PopInt());
			}
			break;
		case OPCODE_GREATERTHANOREQUALTO:
			{
				int32 left;

				left = this->PopInt();

				this->PushInt(left >= this->PopInt());
			}
			break;
		case OPCODE_ADDASSIGN:
			{
				int32 *pData;
				
				pData = (int32 *)this->PopVar();

				*pData += this->PopInt();
			}
			break;
		case OPCODE_UNARYMINUS:
			{
				this->PushInt(-this->PopInt());
			}
			break;
		case OPCODE_NOT:
			{
				this->PushInt(!this->PopInt());
			}
			break;
		case OPCODE_RETURN:
			{
				if(callStack.IsEmpty())
					return;
				pc = callStack.Pop();
			}
			break;
		case OPCODE_CALL:
			{
				uint32 address;
				
				address = *(uint32 *)pc;
				pc += 4;
				callStack.Push(pc);
				
				pc = &this->pProgram->GetProgram()[address];
			}
			break;
		case OPCODE_CALLEXTERNAL:
			{
				uint32 symbolIndex;
				
				symbolIndex = *(uint32 *)pc;
				pc += 4;

				this->CallExtern(this->pProgram->GetSymbol(symbolIndex).data.programOffset, symbolIndex);
			}
			break;
		case OPCODE_PUSHINT:
			{
				int32 value;

				value = *(int32 *)pc;
				pc += 4;

				this->PushInt(value);
			}
			break;
		case OPCODE_PUSHVAR:
			{
				uint32 symbolIndex;
				
				symbolIndex = *(uint32 *)pc;
				pc += 4;

				const SSymbol &refSymbol = this->pProgram->GetSymbol(symbolIndex);
				if(refSymbol.isClassVar)
				{
					this->PushVar(this->pCurrentInstance->GetMemberAddress(refSymbol.offSizeRet, 0));
				}
				else
				{
					if(refSymbol.type == DAEDALUS_TYPE_STRING)
						this->PushVar(refSymbol.data.pData[0].pStr);
					else
						this->PushVar(&refSymbol.data.pData[0].i);
				}
			}
			break;
		case OPCODE_PUSHINSTANCE:
			{
				uint32 symbolIndex;
				
				symbolIndex = *(uint32 *)pc;
				pc += 4;
				
				dataStack.Push(symbolIndex);
			}
			break;
		case OPCODE_ASSIGN_STRING:
			{
				CString *pVar;
				
				pVar = (CString *)this->PopVar();
				*pVar = *this->PopString();
			}
			break;
		case OPCODE_ASSIGN_FUNC:
			{
				int32 *pVar;
				
				pVar = (int32 *)this->PopVar();
				*pVar = this->PopInt();
			}
			break;
		case OPCODE_ASSIGN_FLOAT:
			{
				float32 *pVar;
				
				pVar = (float32 *)this->PopVar();
				ASSERT(0);
				//*pVar = this->PopInt(); //due to UValue union.. this should do the trick...
			}
			break;
		case OPCODE_ASSIGN_INSTANCE:
			{
				SSymbol &refSymbol = this->pProgram->GetSymbol((uint32)dataStack.Pop());
				
				refSymbol.pCurrentInstance = this->pProgram->GetSymbol((uint32)dataStack.Pop()).pCurrentInstance;
			}
			break;
		case OPCODE_JUMP:
			{
				pc = &this->pProgram->GetProgram()[*(uint32 *)pc];
			}
			break;
		case OPCODE_JUMP_IF:
			{
				uint32 address;

				address = *(uint32 *)pc;
				pc += 4;
				
				if(!this->PopInt())
					pc = &this->pProgram->GetProgram()[address];
			}
			break;
		case OPCODE_SET_INSTANCE:
			{
				this->pCurrentInstance = this->pProgram->GetSymbol(*(uint32 *)pc).pCurrentInstance;
				pc += 4;
			}
			break;
		case OPCODE_PUSH_ARRAY_VAR:
			{
				byte dataIndex;
				uint32 symbolIndex;
				
				symbolIndex = *(uint32 *)pc;
				pc += 4;
				dataIndex = *pc++;

				const SSymbol &refSymbol = this->pProgram->GetSymbol(symbolIndex);
				
				if(refSymbol.isClassVar)
				{
					this->PushVar(this->pCurrentInstance->GetMemberAddress(refSymbol.offSizeRet, dataIndex));
				}
				else
				{
					if(refSymbol.type == DAEDALUS_TYPE_STRING)
						this->PushVar(refSymbol.data.pData[dataIndex].pStr);
					else
						this->PushVar(&refSymbol.data.pData[dataIndex].i);
				}
			}
			break;
		default:
			ASSERT(0);
		}
	}
}