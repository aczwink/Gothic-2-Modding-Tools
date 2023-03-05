#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "AStatementContainer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AExpression;
			
			class CIfAlternative : public AStatementContainer
			{
			private:
				//Members
				AExpression *pCondition;
			public:
				//Constructor
				CIfAlternative(AExpression *pCondition);
				//Destructor
				~CIfAlternative();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram, SJCLib::CArray<uint32> &refEndOfChainInsertOffsets);
			};
		}
	}
}