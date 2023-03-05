//Local
#include "AConstant.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CConstant : public AConstant
			{
			private:
				//Members
				AExpression *pValue;
			public:
				//Constructor
				CConstant(CType *pType, const SJCLib::CString &refName, AExpression *pValue, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CConstant();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				//Inline
				inline const AExpression *GetValue() const
				{
					return this->pValue;
				}
			};
		}
	}
}