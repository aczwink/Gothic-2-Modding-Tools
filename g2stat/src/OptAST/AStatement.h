#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../CProgramBuffer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CCompiler;

		namespace OptAST
		{
			class AStatement
			{
			public:
				//Destructor
				virtual ~AStatement(){}
				//Methods
				virtual void CollectSymbols(CCompiler &refCompiler) = NULL;
				virtual void Compile(CProgramBuffer &refProgram) const = NULL;
			};
		}
	}
}