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
			class CStatements;
			
			class CPrototype : public AGlobal
			{
			private:
				//Members
				SJCLib::CString name;
				SJCLib::CString className;
				CStatements *pConstructorStatements;
			public:
				//Constructor
				CPrototype(const SJCLib::CString &refName, const SJCLib::CString &refClassName, CStatements *pConstructorStatements, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CPrototype();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				//Inline
				inline const SJCLib::CString &GetClassName() const
				{
					return this->className;
				}

				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}
			};
		}
	}
}