#pragma once
//Local
#include "Daedalus.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class ASymbol
		{
		private:
			//Overwriteable
			virtual const SJCLib::CString &GetData(uint16 index) const;
		protected:
			//Members
			uint32 symbolIndex;
			//Methods
			void WriteSymbol(SJCLib::AOutputStream &refOutputStream, const SJCLib::CString &refName, uint32 offSizeRet, uint16 nEntries, EType type, uint8 flags, uint32 programOffset, uint32 parentSymbolIndex) const;
		public:
			//Abstract
			virtual void WriteSymbol(SJCLib::AOutputStream &refOutputStream) const = NULL;
			//Inline
			inline uint32 GetSymbolIndex() const
			{
				return this->symbolIndex;
			}
		};
	}
}