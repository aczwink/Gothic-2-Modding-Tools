//Class Header
#include "CItem.h"
//Local
#include "CGame.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructors
CItem::CItem() : AAccessable(CString())
{
	this->Init();
}

CItem::CItem(const CString &refItemName) : AAccessable(refItemName)
{
	this->Init();
	this->CallScriptConstructor();
}

//Private methods
void CItem::CallScriptConstructor()
{
	CGame::GetInstance().GetProgram()->CallConstructor(this, this->instanceName);
}

void CItem::Init()
{
	uint32 i;

	this->multiplicity = 1;
	
	this->id = 0;
	this->hp = 0;
	this->hpMax = 0;
	this->mainFlag = 0;
	this->flags = 0;
	this->weight = 0;
	this->value = 0;
	this->damageType = 0;
	this->damageTotal = 0;
	this->wear = 0;
	for(i = 0; i < 8; i++)
	{
		this->protection[i] = 0;
	}
	for(i = 0; i < 3; i++)
	{
		this->conditionAttribute[i] = 0;
		this->conditionValue[i] = 0;
		this->changeValue[i] = 0;
	}
	this->onEquip = -1;
	this->onUnequip = -1;
	for(i = 0; i < sizeof(this->onState)/sizeof(this->onState[0]); i++)
	{
		this->onState[i] = -1;
	}
	//GO ON HERE
	
	for(i = 0; i < 6; i++)
	{
		this->count[i] = -1;
	}
}

//Destructor
CItem::~CItem()
{
}

//Public Methods
void *CItem::GetMemberAddress(uint32 offset, uint8 arrayIdx)
{
	switch(offset)
	{
	case 288:
		return &this->id;
	case 292:
		return &this->name;
	case 332:
		return &this->hp;
	case 336:
		return &this->hpMax;
	case 340:
		return &this->mainFlag;
	case 344:
		return &this->flags;
	case 348:
		return &this->weight;
	case 352:
		return &this->value;
	case 356:
		return &this->damageType;
	case 360:
		return &this->damageTotal;
	case 396:
		return &this->wear;
	case 400:
		return &this->protection[arrayIdx]; //is this really 8?
	case 436:
		return &this->conditionAttribute[arrayIdx];
	case 448:
		return &this->conditionValue[arrayIdx];
	case 472:
		return &this->changeValue[arrayIdx];
	case 488:
		return &this->onEquip;
	case 492:
		return &this->onUnequip;
	case 496:
		return &this->onState[arrayIdx];
	case 512:
		return &this->owner;
	case 524:
		return &this->visual;
	case 544:
		return &this->visualChange;
	case 564:
		return &this->effect;
	case 584:
		return &this->visualSkin;
	case 588:
		return &this->scemeName;
	case 608:
		return &this->material;
	case 612:
		return &this->munition;
	case 616:
		return &this->spell;
	case 620:
		return &this->range;
	case 624:
		return &this->magCircle;
	case 628:
		return &this->description;
	case 648:
		return &this->text[arrayIdx];
	case 768:
		return &this->count[arrayIdx];
	case 792:
		return &this->invZBias;
	case 796:
		return &this->invRotX;
	case 800:
		return &this->invRotY;
	case 804:
		return &this->invRotZ;
	}

	ASSERTMSG(0, CString("Illegal offset:") + offset);
	return NULL;
}

bool CItem::IsEquipable() const
{
	switch(this->mainFlag)
	{
	case ITEM_MAINFLAG_MELEE:
		//all melee weapons can be equipped
	case ITEM_MAINFLAG_MAGIC:
		//amulets, rings and belts can be equipped
		return true;
	}

	return false;
}

bool CItem::IsUseable() const
{
	for(uint8 i = 0; i < sizeof(this->onState)/sizeof(this->onState[0]); i++)
	{
		if(this->onState[i] != -1)
			return true;
	}

	return false;
}

bool CItem::SetInt(const CString &refMember, int32 value)
{
	if(AVob::SetInt(refMember, value))
		return true;
	
	ASSERT(0);
	return false;
}

bool CItem::SetString(const CString &refMember, const CString &refValue)
{
	if(AVob::SetString(refMember, refValue))
		return true;

	if(refMember == "itemInstance")
	{
		this->instanceName = refValue;
		this->CallScriptConstructor();
		
		return true;
	}
	
	ASSERT(0);
	return false;
}