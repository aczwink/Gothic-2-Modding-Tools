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

			class CInstance : public AInstance
			{
			private:
				//Members
				SJCLib::CString name;
				SJCLib::CString prototypeName;
				CStatements *pStatements;
				SJCLib::CString programSiblingName;
				uint32 constructorProgramOffset;
			public:
				//Constructor
				CInstance(const SJCLib::CString &refName, const SJCLib::CString &refClassName, CStatements *pStatements, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CInstance();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}

				inline void SetProgramSibling(const SJCLib::CString &refSiblingName)
				{
					this->programSiblingName = refSiblingName;
				}
			};
		}
	}
}