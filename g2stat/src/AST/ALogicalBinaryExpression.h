#pragma once
//Local
#include "ABinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class ALogicalBinaryExpression : public ABinaryExpression
			{
			public:
				//Constructor
				ALogicalBinaryExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				CType GetType() const;
			};
		}
	}
}