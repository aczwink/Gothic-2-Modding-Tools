#pragma once
//Local
#include "AValueExpression.h"
#include "../ASymbol.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CStringExpression : public AValueExpression, public ASymbol
			{
			private:
				//Members
				SJCLib::CString literal;
				//Methods
				const SJCLib::CString &GetData(uint16 index) const;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CStringExpression(const SJCLib::CString &refLiteral);
				//Destructor
				~CStringExpression();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline const SJCLib::CString &GetValue() const
				{
					return this->literal;
				}
			};
		}
	}
}