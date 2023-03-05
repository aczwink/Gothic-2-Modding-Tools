//Class Header
#include "CDaedalusProgram.h"
//Global
#include <iostream>
//Local
#include "CDaedalusVM.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
//Definitions
#define ALLOCVALUES(n) ((UValue *)malloc(sizeof(UValue) * n))

//Constructor
CDaedalusProgram::CDaedalusProgram(AInputStream &refBinaryInput)
{
	uint8 type, flags;
	uint16 tmp16;
	uint32 i, hasName, j, classOffset, programOffset, parentIdx, programSize;
	CString name;
	
	ASSERT(refBinaryInput.ReadByte() == 0x32); //version
	
	refBinaryInput.ReadUInt32(this->nSymbols);
	refBinaryInput.Skip(this->nSymbols * 4); //sortTable... whatever that is...
	
	this->pSymbols = new SSymbol[this->nSymbols];
	
	for(i = 0; i < this->nSymbols; i++)
	{
		refBinaryInput.ReadUInt32(hasName);
		if(hasName)
		{
			name = refBinaryInput.ReadString('\n');
			
			this->nameToSymbolIndexMap.Insert(name, i);
			this->pSymbols[i].name = name;
		}
		
		refBinaryInput.ReadUInt32(this->pSymbols[i].offSizeRet);
		refBinaryInput.ReadUInt16(tmp16);
		this->pSymbols[i].nEntries = tmp16 & 0xFFF;
		type = tmp16 >> 12;
		flags = refBinaryInput.ReadByte() & 0x3F;
		refBinaryInput.Skip(1); //reserved
		refBinaryInput.Skip(4); //fileIndex
		refBinaryInput.Skip(4); //lineStart
		refBinaryInput.Skip(4); //lineCount
		refBinaryInput.Skip(4); //charStart
		refBinaryInput.Skip(4); //charCount

		if(!(flags & DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR))
		{
			this->pSymbols[i].isClassVar = false;
			
			switch(type)
			{
			case DAEDALUS_TYPE_FLOAT:
				{
					this->pSymbols[i].type = DAEDALUS_TYPE_FLOAT;
					this->pSymbols[i].data.pData = ALLOCVALUES(this->pSymbols[i].nEntries);
					for(j = 0; j < this->pSymbols[i].nEntries; j++)
					{
						refBinaryInput.ReadFloat32(this->pSymbols[i].data.pData[j].f);
					}
				}
				break;
			case DAEDALUS_TYPE_INT:
				{
					this->pSymbols[i].type = DAEDALUS_TYPE_INT;
					this->pSymbols[i].data.pData = ALLOCVALUES(this->pSymbols[i].nEntries);
					for(j = 0; j < this->pSymbols[i].nEntries; j++)
					{
						refBinaryInput.ReadInt32(this->pSymbols[i].data.pData[j].i);
					}
				}
				break;
			case DAEDALUS_TYPE_STRING:
				{
					this->pSymbols[i].type = DAEDALUS_TYPE_STRING;
					this->pSymbols[i].data.pData = ALLOCVALUES(this->pSymbols[i].nEntries);
					for(j = 0; j < this->pSymbols[i].nEntries; j++)
					{
						this->pSymbols[i].data.pData[j].pStr = new CString;
						*this->pSymbols[i].data.pData[j].pStr = refBinaryInput.ReadString('\n');
					}
				}
				break;
			case DAEDALUS_TYPE_CLASS:
				{
					refBinaryInput.ReadUInt32(classOffset);
					
					this->pSymbols[i].type = DAEDALUS_TYPE_CLASS;
					this->pSymbols[i].data.classOffset = classOffset;
				}
				break;
			case DAEDALUS_TYPE_FUNC:
				{
					refBinaryInput.ReadUInt32(programOffset);
					
					this->pSymbols[i].type = DAEDALUS_TYPE_FUNC;
					this->pSymbols[i].data.programOffset = programOffset;
				}
				break;
			case DAEDALUS_TYPE_PROTOTYPE:
				{
					refBinaryInput.ReadUInt32(programOffset);
					
					this->pSymbols[i].type = DAEDALUS_TYPE_PROTOTYPE;
					this->pSymbols[i].data.programOffset = programOffset;
				}
				break;
			case DAEDALUS_TYPE_INSTANCE:
				{
					refBinaryInput.ReadUInt32(programOffset);
					
					this->pSymbols[i].type = DAEDALUS_TYPE_INSTANCE;
					this->pSymbols[i].data.programOffset = programOffset;
					this->pSymbols[i].pCurrentInstance = NULL;
				}
				break;
			}
		}
		else
		{
			this->pSymbols[i].isClassVar = true;
		}
		
		refBinaryInput.ReadUInt32(parentIdx);
	}
	
	refBinaryInput.ReadUInt32(programSize);
	ASSERT(refBinaryInput.GetRemainingBytes() == programSize);
	this->pProgram = (byte *)malloc(programSize);
	refBinaryInput.ReadBytes(this->pProgram, programSize);
	ASSERT(refBinaryInput.GetRemainingBytes() == 0 && !refBinaryInput.HitEnd());

	this->heroSymbolIndex = this->FindSymbol("hero");
	this->otherSymbolIndex = this->FindSymbol("other");
	this->selfSymbolIndex = this->FindSymbol("self");
}

//Destructor
CDaedalusProgram::~CDaedalusProgram()
{
	uint32 i, j;
	
	for(i = 0; i < this->nSymbols; i++)
	{
		if(this->pSymbols[i].isClassVar)
			continue;
		
		switch(this->pSymbols[i].type)
		{
		case DAEDALUS_TYPE_FLOAT:
		case DAEDALUS_TYPE_INT:
			{
				free(this->pSymbols[i].data.pData);
			}
			break;
		case DAEDALUS_TYPE_STRING:
			{
				for(j = 0; j < this->pSymbols[i].nEntries; j++)
				{
					delete this->pSymbols[i].data.pData[j].pStr;
				}
				free(this->pSymbols[i].data.pData);
			}
			break;
		}
	}

	HeapDeleteArraySafe(this->pSymbols);
	free(this->pProgram);
}

//Public Functions
void CDaedalusProgram::CallConstructor(AAccessable *pInstance, const CString &refInstanceName)
{
	CDaedalusVM vm(this);
	
	auto &refIt = this->nameToSymbolIndexMap.Find(refInstanceName.ToUppercase());

	if(!refIt.IsValid())
	{
		ASSERTMSG(0, "inst:" + refInstanceName);
	}
	vm.CallConstructor(pInstance, refIt.GetValue());
}

void CDaedalusProgram::SetGlobalVariable(const CString &refVarName, int32 value)
{
	CDaedalusVM vm(this);
	
	auto &refIt = this->nameToSymbolIndexMap.Find(refVarName.ToUppercase());
	
	ASSERT(refIt.IsValid());
	this->pSymbols[refIt.GetValue()].data.pData[0].i = value;
}

/*
#include "CDaedalusVM.h"

//Destructor
CDaedalusProgram::~CDaedalusProgram()
{
	this->Release();
}

CDaedalusArray *CDaedalusProgram::CreateObject(SJCLib::CString instanceName)
{
	CDaedalusVM vm(this);
	
	auto &refIt = this->instances.Find(instanceName.ToLowercase());
	
	ASSERT(refIt.IsValid());
	vm.Run(refIt.GetValue()->programOffset);

	return NULL;
}

void CDaedalusProgram::Release()
{
	uint32 i;
	
	this->ReleaseRuntimeHeap();
	
	memfreesafe(this->pProgram);

	for(i = 0; i < nSymbols; i++)
	{
		//release symbols
		ASSERT(0);
	}
	
	memfreesafe(this->pConstants);

	foreach(it, this->classes)
	{
		delete it.GetValue();
	}
	this->classes.Release();
	
	foreach(it, this->constants)
	{
		delete it.GetValue();
	}
	this->constants.Release();

	foreach(it, this->functions)
	{
		delete it.GetValue();
	}
	this->functions.Release();
	
	foreach(it, this->instances)
	{
		delete it.GetValue();
	}
	this->instances.Release();

	foreach(it, this->prototypes)
	{
		delete it.GetValue();
	}
	this->prototypes.Release();
}

void CDaedalusProgram::ReleaseRuntimeHeap()
{
	/*foreach(it, this->runtimeArrays)
	{
		delete it.GetValue();
	}
	this->runtimeArrays.Release();

	foreach(it, this->runtimeStrings)
	{
		delete it.GetValue();
	}
	this->runtimeStrings.Release();*/
//}

//Public Functions
/*CInstance CDaedalusProgram::CreateInstance(CString instanceName)
{
	CInstance instance;

	if(!)
		ASSERT(0);

	SInstanceData &refData = this->instances[instanceName];
	instance.pData = vm.stack.Pop().pArray;
	instance.pClass = this->classes[refData.className];
	
	return instance;
}*/