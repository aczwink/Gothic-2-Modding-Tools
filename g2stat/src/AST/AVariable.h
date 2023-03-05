#pragma once
//Local
#include "AGlobal.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClass;
		}
		
		//Forward declarations
		class CType;

		namespace AST
		{
			//Forward declarations
			class CClass;
			
			class AVariable : public AGlobal
			{
			protected:
				//Members
				CType *pType;
			public:
				//Constructor
				AVariable(CType *pType, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~AVariable();
				//Abstract
				virtual uint32 GetSize() const = NULL;
				using AGlobal::Process;
				virtual bool Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass) = NULL;
				virtual void Unfold(CCompiler &refCompiler) = NULL;
				//Inline
				inline const CType &GetType() const
				{
					return *this->pType;
				}
			};
		}
	}
}