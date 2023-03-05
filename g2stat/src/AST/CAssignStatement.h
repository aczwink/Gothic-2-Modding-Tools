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
			class CLeftValueIdentifier;
			
			class CAssignStatement : public AStatement
			{
			private:
				//Members
				CLeftValueIdentifier *pLeftValue;
				AExpression *pExpression;
			public:
				//Constructor
				CAssignStatement(CLeftValueIdentifier *pLeftValue, AExpression *pExpression);
				//Destructor
				~CAssignStatement();
				//Methods
				OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}