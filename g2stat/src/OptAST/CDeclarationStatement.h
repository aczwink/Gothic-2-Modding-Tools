#pragma once
//Local
#include "AStatement.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CLocalVariable;
			
			class CDeclarationStatement : public AStatement
			{
			private:
				//Members
				CLocalVariable *pVariable;
			public:
				//Constructor
				CDeclarationStatement(CLocalVariable *pVariable);
				//Destructor
				~CDeclarationStatement();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void Compile(CProgramBuffer &refProgram) const;
			};
		}
	}
}