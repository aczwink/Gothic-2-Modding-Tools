//Local
#include "AVariable.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class CIdentifierList;
			
			class CVariableDefList : public AVariable
			{
			private:
				//Members
				CIdentifierList *pNames;
			public:
				//Constructor
				CVariableDefList(CType *pType, CIdentifierList *pNames);
				//Destructor
				~CVariableDefList();
				//Methods
				uint32 GetSize() const;
				bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback);
				bool Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass);
				void Unfold(CCompiler &refCompiler);
			};
		}
	}
}