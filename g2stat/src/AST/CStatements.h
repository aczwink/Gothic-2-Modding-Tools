//Local
#include "../ICompilerCallback.h"
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AStatementContainer;
			class CClass;
			class CInstance;
			class CLocalVariable;
		}

		namespace AST
		{
			//Forward declarations
			class AVariable;
			class AStatement;

			class CStatements : public ANode
			{
			private:
				//Members
				SJCLib::CLinkedList<AStatement *> statements;
			public:
				//Constructor
				CStatements();
				//Destructor
				~CStatements();
				//Methods
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, OptAST::AStatementContainer *pStmContainer, const ICompilerCallback &refCallback);
				//Inline
				inline void Add(AStatement *pStatement)
				{
					this->statements.InsertFront(pStatement);
				}
			};
		}
	}
}