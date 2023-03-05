#pragma once
//Local
#include "CLeftValueMember.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CArrayIndex;
			
			class CLeftValueMemberArray : public CLeftValueMember
			{
			private:
				//Members
				CArrayIndex *pArrayIndex;
			public:
				//Constructor
				CLeftValueMemberArray(const SJCLib::CString &refIdentifier, const SJCLib::CString &refMemberName, CArrayIndex *pArrayIndex, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CLeftValueMemberArray();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}