#pragma once
//Local
#include "../ASymbol.h"
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CInstance;
			
			class CFuncExpression : public AValueExpression
			{
			private:
				//Members
				const ASymbol *pSymbol;
			public:
				//Constructor
				CFuncExpression(const ASymbol *pSymbol);
				//Methods
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
			};
		}
	}
}