#pragma once
//Local
#include "ABinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class AArithmeticBinaryExpression : public ABinaryExpression
			{
			public:
				//Constructor
				AArithmeticBinaryExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				CType GetType() const;
			};
		}
	}
}