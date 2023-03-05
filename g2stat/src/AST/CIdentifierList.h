//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class CIdentifierList : public ANode
			{
			private:
				//Members
				SJCLib::CLinkedList<SJCLib::CString> identifiers;
			public:
				//Constructor
				CIdentifierList(const SJCLib::CString &refIdentifier);
				//Destructor
				~CIdentifierList();
				//Methods

				//Inline
				inline void Add(const SJCLib::CString &refIdentifier)
				{
					this->identifiers.InsertFront(refIdentifier);
				}

				inline const SJCLib::CLinkedList<SJCLib::CString> &GetIdentifiers() const
				{
					return this->identifiers;
				}
			};
		}
	}
}