#pragma once
//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AExpression;

			class CExprStatement : public AStatement
			{
			private:
				//Members
				AExpression *pExpr;
			public:
				//Constructor
				CExprStatement(AExpression *pExpr);
				//Destructor
				~CExprStatement();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}