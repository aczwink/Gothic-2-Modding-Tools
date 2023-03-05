//Class Header
#include "AVob.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;

//Public methods
bool AVob::SetInt(const CString &refMember, int32 value)
{
	if(refMember == "pack")
		return true;
	
	return false;
}

bool AVob::SetString(const CString &refMember, const CString &refValue)
{
	if(refMember == "triggerTarget")
		return true;
	else if(refMember == "vobName")
		return true;
	
	return false;
}