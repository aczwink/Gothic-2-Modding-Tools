#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../ASymbol.h"
#include "../CProgramBuffer.h"
#include "AGlobal.h"
#include "AStatementContainer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClass;
			
			class CPrototype : public AGlobal, public ASymbol, public AStatementContainer
			{
			private:
				//Members
				bool isCompiled;
				CClass *pClass;
				uint32 constructorProgramOffset;
				SJCLib::CArray<uint32> callProgramOffsets; //offsets where to insert constructor program offset
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CPrototype(const SJCLib::CString &refName, CClass *pClass, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram);
				void CompileCallTo(CProgramBuffer &refProgram);
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline CClass *GetClass()
				{
					return this->pClass;
				}
			};
		}
	}
}