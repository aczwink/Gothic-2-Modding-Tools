#pragma once
//Local
#include "AGlobal.h"
#include "../CType.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class AValueExpression;
			
			class CConstant : public AGlobal
			{
			private:
				//Members
				CType type;
				AValueExpression *pValue;
			public:
				//Constructor
				CConstant(const CType &refType, const SJCLib::CString &refName, AValueExpression *pValue, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CConstant();
				//Methods
				void CollectSymbols(CCompiler &refCompiler);
				//Inline
				inline const CType &GetType() const
				{
					return this->type;
				}
				
				inline AValueExpression *GetValue()
				{
					return this->pValue;
				}
			};
		}
	}
}