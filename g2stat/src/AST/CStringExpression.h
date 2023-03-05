//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CStringExpression : public AValueExpression
			{
			private:
				//Members
				SJCLib::CString literal;
			public:
				//Constructor
				CStringExpression(const SJCLib::CString &refLiteral, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructpr
				~CStringExpression();
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				//Inline
				inline const SJCLib::CString &GetValue() const
				{
					return this->literal;
				}
			};
		}
	}
}