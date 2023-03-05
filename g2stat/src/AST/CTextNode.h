//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CTextNode : public ANode
			{
			private:
				//Members
				SJCLib::CString string;
			public:
				//Constructor
				CTextNode(const SJCLib::CString &refString, uint32 lineNumber);

				//Inline
				inline const SJCLib::CString &GetText() const
				{
					return this->string;
				}
			};
		}
	}
}