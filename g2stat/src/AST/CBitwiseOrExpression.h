//Local
#include "AArithmeticBinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CBitwiseOrExpression : public AArithmeticBinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CBitwiseOrExpression(AExpression *pLeft, AExpression *pRight);
			};
		}
	}
}