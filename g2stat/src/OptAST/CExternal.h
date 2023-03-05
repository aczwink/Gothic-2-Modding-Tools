#pragma once
//Local
#include "CFunction.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CExternal : public CFunction
			{
			private:
				//Members
				uint32 externalProgramOffset;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type, const CType &refParam7Type);
				CExternal(const CType &refRetType, const SJCLib::CString &refName, uint32 externalProgramOffset, const CType &refParam1Type, const CType &refParam2Type, const CType &refParam3Type, const CType &refParam4Type, const CType &refParam5Type, const CType &refParam6Type, const CType &refParam7Type, const CType &refParam8Type);
				//Destructor
				~CExternal();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram);
				void CompileCallTo(CProgramBuffer &refProgram);
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
			};
		}
	}
}