#pragma once
//Local
#include "AInstance.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CIdentifierList;
			class CStatements;

			class CInstanceList : public AInstance
			{
			private:
				//Members
				CIdentifierList *pNames;
				CStatements *pStatements;
			public:
				//Constructor
				CInstanceList(CIdentifierList *pNames, const SJCLib::CString &refClassName, CStatements *pStatements, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CInstanceList();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void Unfold(CCompiler &refCompiler);
			};
		}
	}
}