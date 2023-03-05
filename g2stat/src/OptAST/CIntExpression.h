#pragma once
//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CIntExpression : public AValueExpression
			{
			private:
				//Members
				int32 value;
			public:
				//Constructor
				CIntExpression(int32 value);
				//Methods
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
				//Inline
				inline int32 GetValue() const
				{
					return this->value;
				}
			};
		}
	}
}