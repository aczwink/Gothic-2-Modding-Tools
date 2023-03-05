//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClassVariable;
		}

		namespace AST
		{
			class CAttributeExpression : public AValueExpression
			{
			private:
				//Members
				OptAST::CClassVariable *pAttribute;
				bool hasIndex;
				uint8 index;
			public:
				//Constructor
				CAttributeExpression(OptAST::CClassVariable *pAttribute, const SJCLib::CWString &refFileName, uint32 lineNumber);
				CAttributeExpression(OptAST::CClassVariable *pAttribute, uint8 index, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
			};
		}
	}
}