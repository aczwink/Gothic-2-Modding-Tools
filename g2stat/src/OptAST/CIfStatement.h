#pragma once
//Local
#include "AStatement.h"
#include "AStatementContainer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CIfAlternative;
			
			class CIfStatement : public AStatement, public AStatementContainer
			{
			private:
				//Members
				SJCLib::CLinkedList<CIfAlternative *> alternatives;
			public:
				//Destructor
				~CIfStatement();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
				//Inline
				inline void AddAlternative(CIfAlternative *pAlternative)
				{
					this->alternatives.InsertFront(pAlternative);
				}
			};
		}
	}
}