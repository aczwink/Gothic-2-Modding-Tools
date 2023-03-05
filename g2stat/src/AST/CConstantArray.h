//Local
#include "AConstant.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;
		
		namespace AST
		{
			//Forward declarations
			class CArrayIndex;
			class CExprList;
			
			class CConstantArray : public AConstant
			{
			private:
				//Members
				CArrayIndex *pArraySize;
				CExprList *pValues;
			public:
				//Constructor
				CConstantArray(CType *pType, const SJCLib::CString &refName, CArrayIndex *pArraySize, CExprList *pValues, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CConstantArray();
				//Methods
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
			};
		}
	}
}