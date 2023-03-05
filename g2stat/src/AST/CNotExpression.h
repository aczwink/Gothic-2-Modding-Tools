#pragma once
//Local
#include "AUnaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CNotExpression : public AUnaryExpression
			{
			private:
				//Methods
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CNotExpression(AExpression *pSubExpr);
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				CType GetType() const;
			};
		}
	}
}