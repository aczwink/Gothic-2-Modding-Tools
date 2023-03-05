//Local
#include "ABinaryExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CBitwiseAndExpression : public ABinaryExpression
			{
			private:
				//Methods
				int32 Combine(int32 left, int32 right) const;
				EOpcode GetOpcode() const;
			public:
				//Constructor
				CBitwiseAndExpression(AExpression *pLeft, AExpression *pRight);
				//Methods
				CType GetType() const;
				void Process(SJCLib::CMap<SJCLib::CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler);
			};
		}
	}
}