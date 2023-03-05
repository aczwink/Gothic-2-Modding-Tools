#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "Daedalus.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class CLexer : public SJCLib::CLexer<EToken>
		{
		private:
			//Variables
			uint32 lineNumber;
			//Functions
			bool OnNextToken(const EToken &refParsedToken);
		public:
			//Constructor
			CLexer();
			
			//Inline
			inline uint32 GetLineNumber() const
			{
				return this->lineNumber;
			}
			
			inline void Init(const byte *pInput)
			{
				this->lineNumber = 1;
				SJCLib::CLexer<Daedalus::EToken>::SetInput(pInput);
			}
		};
	};
}