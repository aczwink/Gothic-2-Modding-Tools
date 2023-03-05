//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CFloatExpression : public AValueExpression
			{
			private:
				//Members
				float32 value;
			public:
				//Constructor
				CFloatExpression(float32 value, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				//Inline
				inline float32 GetValue() const
				{
					return this->value;
				}
			};
		}
	}
}