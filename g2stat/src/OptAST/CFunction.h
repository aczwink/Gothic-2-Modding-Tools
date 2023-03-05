#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../AReferenceable.h"
#include "../ASymbol.h"
#include "../CType.h"
#include "AGlobal.h"
#include "AStatementContainer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AValueExpression;
			class CLocalVariable;
			
			class CFunction : public AGlobal, public ASymbol, public AStatementContainer
			{
			private:
				//Members
				uint32 programOffset;
				SJCLib::CLinkedList<CLocalVariable *> arguments;
				bool isCompiled;
				SJCLib::CArray<uint32> callProgramOffsets; //offsets where to insert call program offset
			protected:
				//Members
				CType retType;
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CFunction(const CType &refRetType, const SJCLib::CString &refName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CFunction();
				//Overrideable
				virtual void CollectSymbols(CCompiler &refCompiler);
				virtual void Compile(CProgramBuffer &refProgram);
				virtual void CompileCallTo(CProgramBuffer &refProgram);
				virtual void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline void AddArgument(CLocalVariable *pArgument)
				{
					this->arguments.InsertTail(pArgument);
				}

				inline const SJCLib::CLinkedList<CLocalVariable *> &GetFormalParameters() const
				{
					return this->arguments;
				}

				inline const CType &GetReturnType() const
				{
					return this->retType;
				}
			};
		}
	}
}