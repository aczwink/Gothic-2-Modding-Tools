//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CElseIfs;
			
			class CIfStatement : public AStatement
			{
			private:
				//Members
				CElseIfs *pIfChain;
			public:
				//Constructor
				CIfStatement(CElseIfs *pIfChain);
				//Destructor
				~CIfStatement();
				//Methods
				OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}