#pragma once
//Local
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CCompiler;
		namespace OptAST
		{
			class AValueExpression : public AExpression
			{
			public:
				//Abstract
				virtual AValueExpression *Copy() const = NULL;
				//Overwriteable
				virtual void CollectSymbols(CCompiler &refCompiler);
			};
		}
	}
}