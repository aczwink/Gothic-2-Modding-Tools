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
			class CSymbolExpression : public AValueExpression
			{
			private:
				//Members
				const ASymbol *pSymbol;
				bool hasIndex;
				uint8 index;
			public:
				//Constructor
				CSymbolExpression(const ASymbol *pSymbol);
				CSymbolExpression(const ASymbol *pSymbol, uint8 index);
				//Methods
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
			};
		}
	}
}