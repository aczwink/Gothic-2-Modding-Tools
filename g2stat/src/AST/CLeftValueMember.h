#pragma once
//Local
#include "CLeftValueIdentifier.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClassVariable;
		}

		namespace AST
		{
			class CLeftValueMember : public CLeftValueIdentifier
			{
			protected:
				//Members
				SJCLib::CString memberName;
				OptAST::CClassVariable *pAttribute;
			public:
				//Constructor
				CLeftValueMember(const SJCLib::CString &refIdentifier, const SJCLib::CString &refMemberName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CLeftValueMember();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}