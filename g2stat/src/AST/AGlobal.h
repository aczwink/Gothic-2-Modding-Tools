#pragma once
//Local
#include "../ICompilerCallback.h"
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CCompiler;

		namespace AST
		{
			class AGlobal : public ANode
			{
			public:
				//Constructor
				AGlobal(const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Methods
				virtual bool Process(CCompiler &refCompiler, const ICompilerCallback &refCallback) = NULL;
			};
		}
	}
}