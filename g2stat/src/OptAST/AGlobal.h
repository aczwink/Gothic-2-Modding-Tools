#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../AST/ANode.h"
#include "../AReferenceable.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class AGlobal : public AST::ANode, public AReferenceable
			{
			private:
				//Members
				SJCLib::CString name;
			public:
				//Constructor
				AGlobal(const SJCLib::CString &refName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Abstract
				virtual void CollectSymbols(CCompiler &refCompiler) = NULL;
				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}
			};
		}
	}
}