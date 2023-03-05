#pragma once
//Local
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CFunction;
			
			class CCallExpression : public AExpression
			{
			private:
				//Members
				CFunction *pFunction;
				SJCLib::CLinkedList<AExpression *> callArgs;
			public:
				//Constructor
				CCallExpression(CFunction *pFunction);
				//Destructor
				~CCallExpression();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
				//Inline
				inline void Add(AExpression *pExpr)
				{
					this->callArgs.InsertTail(pExpr);
				}
			};
		}
	}
}