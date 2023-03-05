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
			class CCallExpression;
			class CClass;
			class CConstArrayExpression;
			class CFunction;
			class CInstance;
			class CLocalVariable;
		}
		
		namespace AST
		{
			//Forward declarations
			class AExpression;

			class CExprList : public ANode
			{
			private:
				//Members
				SJCLib::CLinkedList<AExpression *> expressions;
			public:
				//Constructor
				CExprList();
				CExprList(AExpression *pExpr);
				//Destructor
				~CExprList();
				//Methods
				bool CheckCallTypes(OptAST::CFunction *pFunction, const ICompilerCallback &refCallback);
				OptAST::CConstArrayExpression *GetTranslatedExpression(CCompiler &refCompiler);
				bool Optimize(CCompiler &refCompiler);
				void PutTranslatedExpressions(OptAST::CCallExpression *pCallExpr, CCompiler &refCompiler);
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				//Inline
				inline void Add(AExpression *pExpr)
				{
					this->expressions.InsertTail(pExpr);
				}
				inline void AddFront(AExpression *pExpr)
				{
					this->expressions.InsertFront(pExpr);
				}
			};
		}
	}
}