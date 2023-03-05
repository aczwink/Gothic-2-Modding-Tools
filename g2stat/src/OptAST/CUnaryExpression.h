#pragma once
//Local
#include "../Opcodes.h"
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CUnaryExpression : public AExpression
			{
			private:
				//Members
				EOpcode op;
				AExpression *pSubExpr;
			public:
				//Constructor
				CUnaryExpression(EOpcode op, AExpression *pSubExpr);
				//Destructor
				~CUnaryExpression();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}