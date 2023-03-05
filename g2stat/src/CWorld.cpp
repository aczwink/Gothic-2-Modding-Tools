//Class Header
#include "CWorld.h"
//Local
#include "ZEN.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;

//Constructor
CWorld::CWorld(const CString &refWorldName)
{
	this->name = refWorldName;
}

//Destructor
CWorld::~CWorld()
{
	//Delete all vobs
	foreach(it, this->vobs)
	{
		delete it.GetValue();
	}
}

//Public Functions
void CWorld::InsertVob(AVob *pVob)
{
	this->vobs.Push(pVob);
}