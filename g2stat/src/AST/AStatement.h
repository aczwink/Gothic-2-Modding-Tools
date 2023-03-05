#pragma once
//Local
#include "../OptAST/AStatementContainer.h"
#include "../ICompilerCallback.h"
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AStatement;
			class CClass;
			class CInstance;
			class CLocalVariable;
		}
		
		namespace AST
		{
			//Forward declarations
			class AVariable;
			class CClass;
			
			class AStatement : public ANode
			{
			public:
				//Constructor
				AStatement();
				//Methods
				virtual OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback) = NULL;
			};
		}
	}
}