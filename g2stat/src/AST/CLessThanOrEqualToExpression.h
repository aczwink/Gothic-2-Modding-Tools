//Local
#include "ALogicalBinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CLessThanOrEqualToExpression : public ALogicalBinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CLessThanOrEqualToExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				void Process(SJCLib::CMap<SJCLib::CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler);
			};
		}
	}
}