//Local
#include "ALogicalBinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CLessThanExpression : public ALogicalBinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CLessThanExpression(AExpression *pLeft, AExpression *pRight);
			};
		}
	}
}