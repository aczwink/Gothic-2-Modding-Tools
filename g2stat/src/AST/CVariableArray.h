//Local
#include "CVariable.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CArrayIndex;
			
			class CVariableArray : public CVariable
			{
			private:
				//Members
				CArrayIndex *pArraySize;
			public:
				//Constructor
				CVariableArray(CType *pType, const SJCLib::CString &refIdentifier, CArrayIndex *pArraySize);
				//Destructor
				~CVariableArray();
				//Methods
				uint32 GetSize() const;
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				bool Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass);
			};
		}
	}
}