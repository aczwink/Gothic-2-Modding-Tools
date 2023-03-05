//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CFuncExpression : public AValueExpression
			{
			private:
				//Members
				SJCLib::CString functionName;
			public:
				//Constructor
				CFuncExpression(const SJCLib::CString &refFunctionName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
			};
		}
	}
}