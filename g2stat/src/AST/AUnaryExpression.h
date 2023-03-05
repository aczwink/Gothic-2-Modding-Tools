#pragma once
//Local
#include "AExpression.h"
#include "../Opcodes.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class AUnaryExpression : public AExpression
			{
			private:
				//Methods
				virtual EOpcode GetOpcode() const = NULL;
			protected:
				//Members
				AExpression *pSubExpression;
			public:
				//Constructor
				AUnaryExpression(AExpression *pSubExpression);
				//Destructor
				~AUnaryExpression();
				//Methods
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void SetCastTo(const CType &refType);
			};
		}
	}
}