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
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}