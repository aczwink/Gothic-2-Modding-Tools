//Local
#include "AArithmeticBinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CShiftLeftExpression : public AArithmeticBinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CShiftLeftExpression(AExpression *pLeft, AExpression *pRight);
			};
		}
	}
}