#pragma once
//Local
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class AVariable;
			class CVariables;
			
			class CClass : public AGlobal
			{
			private:
				//Members
				SJCLib::CString name;
				CVariables *pVariables;
			public:
				//Constructor
				CClass(const SJCLib::CString &refClassName, CVariables *pVariables, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CClass();
				//Methods
				void AddVariableAfter(AVariable *pNew, AVariable *pAfter);
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void RemoveVariable(AVariable *pVariable);

				//Inline			
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}

				inline CVariables *GetVariables()
				{
					return this->pVariables;
				}
			};
		}
	}
}