#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "Daedalus.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class AAccessable //Accessable through Daedalus script
		{
		protected:
			//Members
			SJCLib::CString instanceName;
		public:
			//Constructor
			inline AAccessable(const SJCLib::CString &refInstanceName)
			{
				this->instanceName = refInstanceName;
			}

			//Abstract
			virtual void *GetMemberAddress(uint32 offset, uint8 arrayIdx) = NULL;

			//Inline
			inline const SJCLib::CString &GetInstanceName() const
			{
				return this->instanceName;
			}
		};
	}
}