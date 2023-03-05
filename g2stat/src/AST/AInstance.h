#pragma once
//Local
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace AST
		{
			class AInstance : public AGlobal
			{
			protected:
				//Members
				SJCLib::CString className;
			public:
				//Constructor
				AInstance(const SJCLib::CString &refClassName, const SJCLib::CWString &refFileName, uint32 lineNumber);
				
				//Inline
				inline const SJCLib::CString &GetClassName() const
				{
					return this->className;
				}
			};
		}
	}
}