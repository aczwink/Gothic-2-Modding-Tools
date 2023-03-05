#pragma once
//Local
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class AValueExpression : public AExpression
			{
			public:
				//Constructor
				AValueExpression(const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void SetCastTo(const CType &refType);
			};
		}
	}
}