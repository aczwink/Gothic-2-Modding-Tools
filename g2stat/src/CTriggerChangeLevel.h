//Local
#include "ATrigger.h"

namespace SJCPBLib
{
	class CTriggerChangeLevel : public ATrigger
	{
	private:
		//Members
		SJCLib::CString levelName;
	public:
		//Methods
		bool SetString(const SJCLib::CString &refMember, const SJCLib::CString &refValue);
		//Inline
		inline const SJCLib::CString &GetLevelName() const
		{
			return this->levelName;
		}
	};
}