//Local
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;

		namespace OptAST
		{
			//Forward declarations
			class CFunction;
		}

		namespace AST
		{
			//Forward declarations
			class CExprList;

			class CCallExpression : public AExpression
			{
			private:
				//Members
				SJCLib::CString functionName;
				OptAST::CFunction *pFunction;
				CExprList *pArgs;
			public:
				//Constructor
				CCallExpression(const SJCLib::CString &refFunctionName, CExprList *pArgs);
				//Destructor
				~CCallExpression();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void SetCastTo(const CType &refType);
			};
		}
	}
}