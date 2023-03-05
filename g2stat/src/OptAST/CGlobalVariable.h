#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../ASymbol.h"
#include "../CType.h"
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			class CGlobalVariable : public AGlobal, public ASymbol
			{
			private:
				//Members
				CType type;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CGlobalVariable(const CType &refType, const SJCLib::CString &refName);
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline const CType &GetType() const
				{
					return this->type;
				}
			};
		}
	}
}