#pragma once
//Local
#include "AVariable.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CVariable : public AVariable
			{
			private:
				//Members
				SJCLib::CString name;
			public:
				//Constructor
				CVariable(CType *pType, const SJCLib::CString &refName);
				//Destructor
				~CVariable();
				//Methods
				uint32 GetSize() const;
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				bool Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass);
				void Unfold(CCompiler &refCompiler);
				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}
			};
		}
	}
}