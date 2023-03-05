#pragma once
//Local
#include "AUnaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CMinusExpression : public AUnaryExpression
			{
			private:
				//Methods
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CMinusExpression(AExpression *pSubExpr);
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				CType GetType() const;
			};
		}
	}
}