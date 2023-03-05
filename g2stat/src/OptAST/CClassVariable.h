#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "../ASymbol.h"
#include "../CType.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClass;
			
			class CClassVariable : public ASymbol
			{
			private:
				//Members
				CType type;
				SJCLib::CString name;
				CClass &refClass;
			protected:
				//Methods
				using ASymbol::WriteSymbol;
			public:
				//Constructor
				CClassVariable(const CType &refType, const SJCLib::CString &refName, CClass &refClass);
				//Destructor
				~CClassVariable();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				uint32 GetOffset() const;
				void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const;
				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}

				inline uint32 GetSize() const
				{
					return this->type.GetSize();
				}

				inline const CType &GetType() const
				{
					return this->type;
				}
			};
		}
	}
}