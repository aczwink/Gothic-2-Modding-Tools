#pragma once
//Local
#include "../CType.h"
#include "../Opcodes.h"
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AExpression;

			class CAssignStatement : public AStatement
			{
			private:
				//Members
				EType assignType;
				AExpression *pLeftValue;
				AExpression *pExpr;
				bool hasOp;
				EOpcode op;
			public:
				//Constructor
				CAssignStatement(EType assignType, AExpression *pLeftValue, AExpression *pExpr);
				CAssignStatement(EType assignType, EOpcode op, AExpression *pLeftValue, AExpression *pExpr);
				//Destructor
				~CAssignStatement();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
				//Inline
				inline EOpcode GetOpcode() const
				{
					return this->op;
				}

				inline bool HasOp() const
				{
					return this->hasOp;
				}
			};
		}
	}
}