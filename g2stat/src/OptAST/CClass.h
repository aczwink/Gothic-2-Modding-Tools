#pragma once
//Local
#include "../ASymbol.h"
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;
		
		namespace OptAST
		{
			//Forward declarations
			class CClassVariable;
			
			class CClass : public AGlobal, public ASymbol
			{
			private:
				//Members
				SJCLib::CLinkedList<CClassVariable *> variables;
				//Methods
				uint32 GetBaseSize() const;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CClass(const SJCLib::CString &refName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CClass();
				//Methods
				void AddVariable(const CType &refType, const SJCLib::CString &refName);
				void CollectSymbols(CCompiler &refCompiler);
				CClassVariable *FindVariable(const SJCLib::CString &refName) const;
				uint32 GetOffset(const CClassVariable *pVariable) const;
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline const SJCLib::CLinkedList<CClassVariable *> &GetVariables() const
				{
					return this->variables;
				}

				inline uint32 GetSize() const
				{
					return this->GetOffset(NULL);
				}
			};
		}
	}
}