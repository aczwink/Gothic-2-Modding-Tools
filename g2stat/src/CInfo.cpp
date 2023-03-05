//Class Header
#include "CInfo.h"
//Local
#include "CGame.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructor
CInfo::CInfo(const CString &refInfoName) : AAccessable(refInfoName)
{
	this->npc = -1;
	this->nr = -1;
	this->important = 0;
	this->condition = -1;
	this->information = -1;
	this->trade = 0;
	this->permanent = 0;
	
	//Call the script constructor
	CGame::GetInstance().GetProgram()->CallConstructor(this, refInfoName);
}

//Destructor
CInfo::~CInfo()
{
}

//Public methods
void *CInfo::GetMemberAddress(uint32 offset, uint8 arrayIdx)
{
	switch(offset)
	{
	case 0:
		return &this->npc;
	case 4:
		return &this->nr;
	case 8:
		return &this->important;
	case 12:
		return &this->condition;
	case 16:
		return &this->information;
	case 20:
		return &this->description;
	case 40:
		return &this->trade;
	case 44:
		return &this->permanent;
	}

	ASSERT(0);
	return NULL;
}