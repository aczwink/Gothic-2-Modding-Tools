#pragma once
//Local
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;
		
		namespace AST
		{
			//Forward declarations
			class AExpression;
			
			class AConstant : public AGlobal
			{
			private:
				//Members
				SJCLib::CString name;
			protected:
				//Members
				CType *pType;
			public:
				//Constructor
				AConstant(CType *pType, const SJCLib::CString &refName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~AConstant();

				//Inline
				inline const SJCLib::CString &GetName() const
				{
					return this->name;
				}
			};
		}
	}
}