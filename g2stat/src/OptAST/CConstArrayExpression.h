#pragma once
//Local
#include "../CType.h"
#include "AValueExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CConstArrayExpression : public AValueExpression
			{
			private:
				//Members
				SJCLib::CLinkedList<AValueExpression *> constValues;
			public:
				//Constructor
				CConstArrayExpression();
				//Destructor
				~CConstArrayExpression();
				//Methods
				void Compile(CProgramBuffer &refProgram) const;
				AValueExpression *Copy() const;
				//Inline
				inline void Add(AValueExpression *pExpr)
				{
					this->constValues.InsertTail(pExpr);
				}
			};
		}
	}
}