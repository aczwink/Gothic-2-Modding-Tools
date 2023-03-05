#pragma once
//Local
#include "CItem.h"
#include "CNPC.h"

namespace SJCPBLib
{
	//Forward Declarations
	class AVob;
	class CDaedalusProgram;
	
	class CDaedalusVM
	{
		friend class CDaedalusProgram;
	private:
		//Variables
		CDaedalusProgram *pProgram;
		SJCLib::CArray<uint64> dataStack;
		Daedalus::AAccessable *pCurrentInstance;
		uint32 selfSymbolIndex;
		uint32 instance_helpSymbolIndex;
		SJCLib::CString stringExternalResult;
		//Functions
		void CallConstructor(Daedalus::AAccessable *pInstance, uint32 instanceSymbolIndex);
		void CallExtern(uint32 callOffset, uint32 symbolIndex);
		int32 PopInt();
		SJCLib::CString *PopString();
		void *PopVar();
		void PushInt(int32 value);
		void PushVar(void *pVar);
	public:
		//Constructor
		CDaedalusVM(CDaedalusProgram *pProgram);
		//Destructor
		~CDaedalusVM();
		//Functions
		void Run(uint32 offset);
	};
}