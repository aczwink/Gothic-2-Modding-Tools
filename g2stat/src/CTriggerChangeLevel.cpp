//Class Header
#include "CTriggerChangeLevel.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;

//Public methods
bool CTriggerChangeLevel::SetString(const CString &refMember, const CString &refValue)
{
	if(AVob::SetString(refMember, refValue))
		return true;

	if(refMember == "levelName")
	{
		this->levelName = refValue;
		return true;
	}
	else if(refMember == "respondToVobName")
		return true;
	else if(refMember == "startVobName")
		return true;
	
	ASSERT(0);
	return false;
}