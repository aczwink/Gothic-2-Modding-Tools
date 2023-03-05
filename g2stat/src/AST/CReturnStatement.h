//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class AExpression;

			class CReturnStatement : public AStatement
			{
			private:
				//Members
				AExpression *pExpr;
			public:
				//Constructor
				CReturnStatement(AExpression *pExpr);
				//Destructor
				~CReturnStatement();
				//Methods
				OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}