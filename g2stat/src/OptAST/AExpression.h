#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../CProgramBuffer.h"
#include "../CType.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class AExpression
			{
			public:
				//Destructor
				virtual ~AExpression(){}
				//Methods
				virtual void CollectSymbols(CCompiler &refCompiler) = NULL;
				virtual void Compile(CProgramBuffer &refProgram) const = NULL;
			};
		}
	}
}