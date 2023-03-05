#pragma once
//Local
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CFloatExpression : public AValueExpression
			{
			private:
				//Members
				float32 value;
			public:
				//Constructor
				CFloatExpression(float32 value);
				//Methods
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
				//Inline
				inline float32 GetValue() const
				{
					return this->value;
				}
			};
		}
	}
}