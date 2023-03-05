#pragma once
//Local
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;

		namespace AST
		{
			//Forward declarations
			class CArguments;
			class CStatements;
			
			class CFunction : public AGlobal
			{
			private:
				//Members
				CType *pRetType;
				SJCLib::CString name;
				CArguments *pArgs;
				CStatements *pStatements;
			public:
				//Constructor
				CFunction(CType *pRetType, const SJCLib::CString &refName, CArguments *pArgs, CStatements *pStatements, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CFunction();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}
			};
		}
	}
}