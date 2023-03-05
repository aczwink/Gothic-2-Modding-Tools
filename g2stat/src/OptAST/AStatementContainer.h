#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class AStatementContainer
			{
			protected:
				//Members
				SJCLib::CLinkedList<AStatement *> statements;
			public:
				//Destructor
				~AStatementContainer();
				//Inline
				inline void AddStatement(AStatement *pStatement)
				{
					this->statements.InsertTail(pStatement);
				}

				inline const SJCLib::CLinkedList<AStatement *> &GetStatements() const
				{
					return this->statements;
				}
			};
		}
	}
}