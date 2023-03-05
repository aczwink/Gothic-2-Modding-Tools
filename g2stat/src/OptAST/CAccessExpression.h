#pragma once
//Local
#include "../ASymbol.h"
#include "../Opcodes.h"
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CAccessExpression : public AExpression
			{
			private:
				//Members
				const ASymbol *pAccessor;
				AExpression *pSubExpr;
			public:
				//Constructor
				CAccessExpression(const ASymbol *pAccessor, AExpression *pAccessExpr);
				//Destructor
				~CAccessExpression();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}