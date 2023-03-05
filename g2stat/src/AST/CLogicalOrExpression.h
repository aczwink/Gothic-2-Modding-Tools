//Local
#include "ALogicalBinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CLogicalOrExpression : public ALogicalBinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CLogicalOrExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				void Process(SJCLib::CMap<SJCLib::CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler);
			};
		}
	}
}