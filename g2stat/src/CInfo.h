#pragma once
//Local
#include "AAccessable.h"

namespace SJCPBLib
{
	class CInfo : public Daedalus::AAccessable
	{
	private:
		//Members
		int32 npc;
		int32 nr;
		int32 important;
		int32 condition; //func
		int32 information; //func
		SJCLib::CString description;
		int32 trade;
		int32 permanent;
	public:
		//Constructor
		CInfo(const SJCLib::CString &refInfoName);
		//Destructor
		~CInfo();
		//Methods
		void *GetMemberAddress(uint32 offset, uint8 arrayIdx);
		//Inline
		inline const SJCLib::CString &GetDescription() const
		{
			return this->description;
		}

		inline int32 GetInformationSymbolIndex() const
		{
			return this->information;
		}

		inline int32 GetNPCSymbolIndex() const
		{
			return this->npc;
		}

		inline uint32 GetNumber() const
		{
			return this->nr;
		}

		inline bool IsImportant() const
		{
			return this->important != 0;
		}

		inline bool IsPermanent() const
		{
			return this->permanent != 0;
		}
		
		inline bool IsTrade() const
		{
			return this->trade != 0;
		}
	};
}