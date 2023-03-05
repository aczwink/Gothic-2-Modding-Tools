#pragma once
//Libs
#include <SJCLib.h>

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CCompiler;
		
		namespace AST
		{
			class ANode
			{
			private:
				//Members
				SJCLib::CWString fileName;
				uint32 lineNumber;
			public:
				//Constructor
				ANode(const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				virtual ~ANode()
				{
				}

				//Inline
				inline const SJCLib::CWString &GetFileName() const
				{
					return this->fileName;
				}

				inline uint32 GetLineNumber() const
				{
					return this->lineNumber;
				}
			};
		}
	}
}