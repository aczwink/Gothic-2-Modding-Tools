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
			class CClass;
			class CIfStatement;
			class CInstance;
			class CLocalVariable;
		}

		namespace AST
		{
			//Forward declarations
			class AExpression;
			class CStatements;

			class CElseIfs : public ANode
			{
				struct SIfEntry
				{
					AExpression *pConditionExpr;
					CStatements *pNestedStatements;
				};
			private:
				//Members
				SJCLib::CLinkedList<SIfEntry> ifChain;
			public:
				//Constructor
				CElseIfs();
				CElseIfs(AExpression *pConditionExpr, CStatements *pNestedStatements);
				//Destructor
				~CElseIfs();
				//Methods
				void AddFront(AExpression *pConditionExpr, CStatements *pNestedStatements);
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::CIfStatement *pIfChainContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}