#pragma once
//Local
#include "CLeftValueIdentifier.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CArrayIndex;

			class CLeftValueArray : public CLeftValueIdentifier
			{
			private:
				//Members
				CArrayIndex *pArrayIndex;
			public:
				//Constructor
				CLeftValueArray(const SJCLib::CString &refIdentifier, CArrayIndex *pArrayIndex, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CLeftValueArray();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}