//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;
		
		namespace AST
		{			
			class CDeclarationStatement : public AStatement
			{
			private:
				//Members
				CType *pType;
				SJCLib::CString varName;
			public:
				//Constructor
				CDeclarationStatement(CType *pType, const SJCLib::CString &refVarName);
				//Destructor
				~CDeclarationStatement();
				//Methods
				OptAST::AStatement *Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, OptAST::AStatementContainer *pStmContainer, CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}