#pragma once
//Local
#include "../Opcodes.h"
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CBinaryExpression : public AExpression
			{
			private:
				//Members
				EOpcode op;
				AExpression *pLeft;
				AExpression *pRight;
			public:
				//Constructor
				CBinaryExpression(EOpcode op, AExpression *pLeft, AExpression *pRight);
				//Destructor
				~CBinaryExpression();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}