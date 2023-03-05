//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CIntExpression : public AValueExpression
			{
			private:
				//Members
				int32 value;
			public:
				//Constructor
				CIntExpression(int32 value, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				//Inline
				inline int32 GetValue() const
				{
					return this->value;
				}
			};
		}
	}
}