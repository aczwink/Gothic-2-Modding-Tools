#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "AGlobal.h"
#include "AStatementContainer.h"
#include "../ASymbol.h"
#include "../CProgramBuffer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClass;
			class CPrototype;
			
			class CInstance : public AGlobal, public ASymbol, public AStatementContainer
			{
			private:
				//Members
				CClass *pClass;
				CPrototype *pPrototype;
				uint32 constructorProgramOffset;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CInstance(const SJCLib::CString &refName, CClass *pClass, CPrototype *pPrototype, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram);
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline CClass *GetClass()
				{
					return this->pClass;
				}

				inline void SetClass(CClass *pClass)
				{
					this->pClass = pClass;
				}

				inline void SetPrototype(CPrototype *pPrototype)
				{
					this->pPrototype = pPrototype;
				}
			};
		}
	}
}