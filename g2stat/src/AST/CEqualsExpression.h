//Local
#include "ABinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CEqualsExpression : public ABinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CEqualsExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				CType GetType() const;
			};
		}
	}
}