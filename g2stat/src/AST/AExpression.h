#pragma once
//Local
#include "../CType.h"
#include "../ICompilerCallback.h"
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AExpression;
			class CClass;
			class CInstance;
			class CLocalVariable;
		}

		namespace AST
		{
			//Forward declarations
			class AVariable;
			class CClass;
			
			class AExpression : public ANode
			{
			public:
				//Constructor
				AExpression(const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Abstract
				virtual AExpression *GetOptimizedExpression(CCompiler &refCompiler) = NULL;
				virtual OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const = NULL;
				virtual CType GetType() const = NULL;
				virtual bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback) = NULL;
				virtual void SetCastTo(const CType &refType) = NULL;
			};
		}
	}
}