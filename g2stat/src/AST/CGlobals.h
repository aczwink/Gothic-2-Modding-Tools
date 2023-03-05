#pragma once
//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			//Forward declarations
			class AGlobal;

			class CGlobals : public ANode
			{
			private:
				//Members
				SJCLib::CArray<AGlobal *> globals;
			public:
				//Constructor
				CGlobals();
				//Methods
				void Preprocess();

				//Inline
				inline void Add(AGlobal *pGlobal)
				{
					this->globals.Push(pGlobal);
				}

				inline const SJCLib::CArray<AGlobal *> &GetGlobals() const
				{
					return this->globals;
				}
			};
		}
	}
}