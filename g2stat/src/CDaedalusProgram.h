#pragma once
//Local
#include "AVob.h"
#include "CNPC.h"
#include "Daedalus.h"

namespace SJCPBLib
{
	class CDaedalusProgram
	{
	private:
		//Variables
		uint32 nSymbols;
		Daedalus::SSymbol *pSymbols;
		byte *pProgram;
		SJCLib::CMap<SJCLib::CString, uint32> nameToSymbolIndexMap;
		uint32 heroSymbolIndex;
		uint32 otherSymbolIndex;
		uint32 selfSymbolIndex;
	public:
		//Constructor
		CDaedalusProgram(SJCLib::AInputStream &refBinaryInput);
		//Destructor
		~CDaedalusProgram();
		//Functions
		void CallConstructor(Daedalus::AAccessable *pInstance, const SJCLib::CString &refInstanceName);
		void SetGlobalVariable(const SJCLib::CString &refVarName, int32 value);
		//Inline
		inline void ExecuteFunction(uint32 symbolIndex)
		{
			CDaedalusVM vm(this);
			
			vm.Run(this->pSymbols[symbolIndex].data.programOffset);
		}

		inline void ExecuteFunction(const SJCLib::CString &refFunctionName)
		{
			auto &refIt = this->nameToSymbolIndexMap.Find(refFunctionName.ToUppercase());
			
			ASSERT(refIt.IsValid());
			this->ExecuteFunction(refIt.GetValue());
		}
		
		inline uint32 FindSymbol(const SJCLib::CString &refName)
		{
			auto &refIt = this->nameToSymbolIndexMap.Find(refName.ToUppercase());
			if(refIt.IsValid())
				return refIt.GetValue();
			return UINT32_MAX;
		}

		inline const byte *GetProgram() const
		{
			return this->pProgram;
		}

		inline CNPC *GetSelf()
		{
			return (CNPC *)this->GetSymbol(this->selfSymbolIndex).pCurrentInstance;
		}

		inline Daedalus::SSymbol &GetSymbol(uint32 index)
		{
			return this->pSymbols[index];
		}

		inline void SetHero(CNPC *pNpc)
		{
			this->GetSymbol(this->heroSymbolIndex).pCurrentInstance = pNpc;
		}

		inline void SetOther(CNPC *pNpc)
		{
			this->GetSymbol(this->otherSymbolIndex).pCurrentInstance = pNpc;
		}
		
		inline void SetSelf(CNPC *pNpc)
		{
			this->GetSymbol(this->selfSymbolIndex).pCurrentInstance = pNpc;
		}
	};
}

/*#pragma once
//SJCLib
#include <SJCLib.h>
//Local
#include "CConstant.h"
#include "CFunction.h"
#include "CInstance.h"
#include "CPrototype.h"

namespace SJCPBLib
{
	class CDaedalusProgram
	{
		friend class CDaedalusCompiler;
		friend class CDaedalusVM;
		friend class CGame;
	private:
		//Variables
		Daedalus::UValue *pConstants; //optimized constants for program
		SJCLib::CMap<SJCLib::CString, Daedalus::CClass *> classes;
		SJCLib::CArray<Daedalus::CConstant *> constants;
		SJCLib::CMap<SJCLib::CString, Daedalus::CFunction *> functions;
		SJCLib::CMap<SJCLib::CString, Daedalus::CInstance *> instances;
		SJCLib::CMap<SJCLib::CString, Daedalus::CPrototype *> prototypes;
		SJCLib::CFiniteSet<Daedalus::CDaedalusArray *> runtimeArrays;
		SJCLib::CArray<SJCLib::CString *> runtimeStrings;
		//Inline
		inline void RegisterArray(Daedalus::CDaedalusArray *pArray)
		{
			this->runtimeArrays.Insert(pArray);
		}

		inline void RegisterString(SJCLib::CString *pString)
		{
			this->runtimeStrings.Push(pString);
		}
	public:
		//Functions
		Daedalus::CDaedalusArray *CreateObject(SJCLib::CString instanceName);
		void ReleaseRuntimeHeap();
		//Inline
		inline const SJCLib::CMap<SJCLib::CString, Daedalus::CClass *> &GetClasses() const
		{
			return this->classes;
		}
		
		inline const SJCLib::CArray<Daedalus::CConstant *> &GetConstants() const
		{
			return this->constants;
		}

		inline const SJCLib::CMap<SJCLib::CString, Daedalus::CFunction *> &GetFunctions() const
		{
			return this->functions;
		}

		inline const SJCLib::CMap<SJCLib::CString, Daedalus::CInstance *> &GetInstances() const
		{
			return this->instances;
		}

		inline const SJCLib::CMap<SJCLib::CString, Daedalus::CPrototype *> &GetPrototypes() const
		{
			return this->prototypes;
		}
	};
}*/