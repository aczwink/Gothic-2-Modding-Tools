//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CArrayIndex : public ANode
			{
			private:
				//Members
				uint32 index;
				SJCLib::CString identifier;
				bool isIdentifierSet;
				//Methods
				void Eval(CCompiler &refCompiler);
			public:
				//Constructor
				CArrayIndex(uint32 index, const SJCLib::CWString &refFileName, uint32 lineNumber);
				CArrayIndex(const SJCLib::CString &refIdentifier, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CArrayIndex();
				//Methods
				void Process(CCompiler &refCompiler);

				//Inline
				inline uint32 GetIndex() const
				{
					return this->index;
				}
			};
		}
	}
}