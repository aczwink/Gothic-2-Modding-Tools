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
			class ABinaryExpression : public AExpression
			{
			protected:
				//Members
				AExpression *pLeft;
				AExpression *pRight;
				//Abstract
				virtual int32 Combine(int32 left, int32 right) const = NULL;
				virtual EOpcode GetOpcode() const = NULL;
			public:
				//Constructor
				ABinaryExpression(AExpression *pLeft, AExpression *pRight);
				//Destructor
				~ABinaryExpression();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void SetCastTo(const CType &refType);
			};
		}
	}
}