//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CExprList;
			
			class CCallStatement : public AStatement
			{
			private:
				//Members
				SJCLib::CString functionName;
				CExprList *pArgs;
			public:
				//Constructor
				CCallStatement(const SJCLib::CString &refFunctionName, CExprList *pArgs);
				//Destructor
				~CCallStatement();
				//Methods
				OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}