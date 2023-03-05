//Class Header
#include "CNPC.h"
//Local
#include "CGame.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructor
CNPC::CNPC() : AAccessable(CString())
{
	this->Init();
}

CNPC::CNPC(const CString &refNPCName) : AAccessable(refNPCName)
{
	CNPC *pOldSelf;
	CDaedalusProgram *pProgram;

	CGame &refGame = CGame::GetInstance();

	//Call default constructor
	this->Init();

	pProgram = refGame.GetProgram();
	
	//Call the script constructor
	pOldSelf = pProgram->GetSelf();
	pProgram->SetSelf(this);
	pProgram->CallConstructor(this, refNPCName);
	pProgram->SetSelf(pOldSelf);
}

//Destructor
CNPC::~CNPC()
{
	uint32 i;

	HeapDeleteSafe(this->pArmor);
	HeapDeleteSafe(this->pMeleeWeapon);
	HeapDeleteSafe(this->pRangedWeapon);
	HeapDeleteSafe(this->pAmulet);
	HeapDeleteSafe(this->pBelt);

	for(i = 0; i < NPC_NUMBEROFRINGS; i++)
	{
		if(this->pRings[i])
			delete this->pRings[i];
	}
	
	for(i = 0; i < NPC_NUMBEROFSPELLSINHAND; i++)
	{
		if(this->pSpells[i])
		{
			delete this->pSpells[i];
		}
	}

	this->ClearInventory();
}

//Private Methods
void CNPC::CallScriptFunction(int32 symbolIndex)
{
	CNPC *pOldSelf;
	CDaedalusProgram *pProgram;

	if(symbolIndex == -1)
		return;
	
	CGame &refGame = CGame::GetInstance();
	
	pProgram = refGame.GetProgram();
	
	pOldSelf = pProgram->GetSelf();
	pProgram->SetSelf(this);
	pProgram->ExecuteFunction(symbolIndex);
	pProgram->SetSelf(pOldSelf);
}

void CNPC::EquipItem(CItem *pItem)
{
	/*
	This function should be the equivalent of the EquipItem function in Daedalus Scripts.
	This function should DEFINETELY be private as it behaves very strange.

	-For melee or ranged weapons it behaves as expected. If a weapon is already equipped, it is
	 put into inventory and the new one is selected.
	-For armors you equip the armor even if you have one equipped (you have then two equipped-.-)
	 but the visuals are not updated. Stats are updated!
	-For amulets you get stats but the amulets are not equipped.
	-For scrolls or runes.. they don't get equipped correctly. However if using the function and then unequipping a rune or scroll the game crashes
	-EVERYTHING ELSE UNTESTED!!!
	*/
	
	ASSERT(this->inventory.Contains(pItem));
	
	switch(pItem->GetMainFlag())
	{
	case ITEM_MAINFLAG_MELEE:
	case ITEM_MAINFLAG_RANGED:
		{
			this->Equip(pItem);
		}
		break;
	case ITEM_MAINFLAG_SPELL:
		{
			//nothing...
		}
		break;
	case ITEM_MAINFLAG_MAGIC:
		{
			if(pItem->GetFlags() & ITEM_FLAGS_AMULET)
			{
				//unfortunately nothing is done...
			}
			else
			{
				ASSERT(0);
			}
		}
		break;
	default:
		ASSERT(0);
	}

	//Set protection values...
}

CItem *CNPC::FindInventoryItem(const CString &refItemInstance) const
{
	foreach(it, this->inventory)
	{
		if(it.GetValue()->GetInstanceName() == refItemInstance)
		{
			return it.GetValue();
		}
	}
	
	return NULL;
}

void CNPC::Init()
{
	uint32 i;
	
	static uint32 internalIdCounter = 1;
	
	this->internalId = internalIdCounter++;
	this->pArmor = NULL;
	this->pMeleeWeapon = NULL;
	this->pRangedWeapon = NULL;
	this->pAmulet = NULL;
	this->pBelt = NULL;

	for(i = 0; i < NPC_NUMBEROFRINGS; i++)
	{
		if(this->pRings[i])
			this->pRings[i] = NULL;
	}

	for(i = 0; i < NPC_NUMBEROFSPELLSINHAND; i++)
	{
		if(this->pSpells[i])
		{
			this->pSpells[i] = NULL;
		}
	}

	for(i = 0; i < 100; i++)
		this->aivar[i] = 0;
}

//Public Functions
void CNPC::ClearInventory()
{
	foreach(it, this->inventory)
	{
		delete it.GetValue();
	}
	this->inventory.Release();
}

void CNPC::EquipArmor(CItem *pItem)
{
	/*
	This function should be the equivalent of the AI_EquipArmor function in Daedalus Scripts.

	This function does nothing if the item is not in inventory.
	If it is, the old armor is unequipped (if there was one) and the new armor is worn.
	For some reason this function does only work in a dialog (at least not in instance constructor!!!).
	*/

	if(this->inventory.Contains(pItem))
	{
		if(this->pArmor)
		{
			this->inventory.Insert(this->pArmor);
		}
		this->pArmor = pItem;
		this->inventory.Delete(pItem);
	}
}

void CNPC::Equip(CItem *pItem)
{
	bool foundFreeSlot;
	uint8 i;
	ASSERT(this->inventory.Contains(pItem));
	
	switch(pItem->GetMainFlag())
	{
	case ITEM_MAINFLAG_MELEE:
		{
			this->Unequip(this->pMeleeWeapon);
			this->pMeleeWeapon = pItem;
		}
		break;
	case ITEM_MAINFLAG_RANGED:
		{
			this->Unequip(this->pRangedWeapon);
			this->pRangedWeapon = pItem;
		}
		break;
	case ITEM_MAINFLAG_ARMOR:
		{
			this->Unequip(this->pArmor);
			this->pArmor = pItem;
		}
		break;
	case ITEM_MAINFLAG_MAGIC:
		{
			if(pItem->GetFlags() & ITEM_FLAGS_RINGS)
			{
				for(i = 0; i < NPC_NUMBEROFRINGS; i++)
				{
					if(!this->pRings[i])
					{
						foundFreeSlot = true;
						break;
					}
				}
				if(!foundFreeSlot)
				{
					i = 0;
					this->Unequip(this->pRings[0]);
				}
				this->pRings[i] = pItem;
			}
			else if(pItem->GetFlags() & ITEM_FLAGS_AMULET)
			{
				this->Unequip(this->pAmulet);
				this->pAmulet = pItem;
			}
			else if(pItem->GetFlags() & ITEM_FLAGS_BELTS)
			{
				this->Unequip(this->pBelt);
				this->pBelt = pItem;
			}
			else
			{
				ASSERTMSG(0, CString(pItem->GetFlags()));
			}
		}
		break;
	default:
		ASSERTMSG(0, CString(pItem->GetMainFlag()));
	}
	
	this->inventory.Delete(pItem);
	
	//Call the onequip function
	if(pItem->GetOnEquip() != -1)
	{
		CDaedalusProgram *pProgram;
		CNPC *pOldSelf;

		CGame &refGame = CGame::GetInstance();
		
		pProgram = refGame.GetProgram();
		pOldSelf = pProgram->GetSelf();
		pProgram->SetSelf(this);
		pProgram->ExecuteFunction(pItem->GetOnEquip());
		pProgram->SetSelf(pOldSelf);
	}
}

uint32 CNPC::GetItemMultiplicity(const CString &refItemInstance) const
{
	CItem *pItem;

	pItem = this->FindInventoryItem(refItemInstance);
	if(pItem)
	{
		return pItem->GetMultiplicity();
	}

	return 0;
}

void *CNPC::GetMemberAddress(uint32 offset, uint8 arrayIdx)
{
	switch(offset)
	{
	case 288:
		return &this->id;
	case 292:
		return &this->name[arrayIdx];
	case 412:
		return &this->effect;
	case 432:
		return &this->npcType;
	case 436:
		return &this->flags;
	case 440:
		return &this->attribute[arrayIdx];
	case 472:
		return &this->hitChance[arrayIdx];
	case 492:
		return &this->protection[arrayIdx]; //is 8 correct???
	case 524:
		return &this->damage[arrayIdx];
	case 556:
		return &this->damageType;
	case 560:
		return &this->guild;
	case 564:
		return &this->level;
	case 588:
		return &this->fightTactic;
	case 596:
		return &this->voice;
	case 608:
		return &this->dailyRoutine;
	case 612:
		return &this->startAIState;
	case 640:
		return &this->senses;
	case 644:
		return &this->sensesRange;
	case 648:
		return &this->aivar[arrayIdx];
	case 1068:
		return &this->exp;
	case 1072:
		return &this->expNext;
	case 1076:
		return &this->lp;
	case 1080:
		return &this->bodyStateInterruptableOverride;
	case 1084:
		return &this->noFocus;
	}
	
	stdOut << offset << endl;
	ASSERT(0);
	return NULL;
}

void CNPC::RemoveItems(const CString &refItemInstance, uint32 amount)
{
	CItem *pItem;
	
	pItem = this->FindInventoryItem(refItemInstance);
	if(pItem)
	{
		if(pItem->GetMultiplicity() > amount)
		{
			pItem->SetMultiplicity(pItem->GetMultiplicity() - amount);
		}
		else
		{
			this->inventory.Delete(pItem);
			delete pItem;
		}
	}
}

bool CNPC::SetInt(const CString &refMember, int32 value)
{
	ASSERT(0);
	return false;
}

bool CNPC::SetString(const SJCLib::CString &refMember, const SJCLib::CString &refValue)
{
	ASSERT(0);
	return false;
}

void CNPC::Unequip(CItem *pItem)
{
	bool isEquipped;
	uint8 i;

	if(!pItem)
		return;
	
	isEquipped = false;
	if(this->pArmor == pItem)
	{
		this->inventory.Insert(this->pArmor);
		this->pArmor = NULL;
		isEquipped = true;
	}
	else if(this->pMeleeWeapon == pItem)
	{
		this->inventory.Insert(this->pMeleeWeapon);
		this->pMeleeWeapon = NULL;
		isEquipped = true;
	}
	else if(this->pRangedWeapon == pItem)
	{
		this->inventory.Insert(this->pRangedWeapon);
		this->pRangedWeapon = NULL;
		isEquipped = true;
	}
	else if(this->pAmulet == pItem)
	{
		this->inventory.Insert(this->pAmulet);
		this->pAmulet = NULL;
		isEquipped = true;
	}
	else if(this->pBelt == pItem)
	{
		this->inventory.Insert(this->pBelt);
		this->pBelt = NULL;
		isEquipped = true;
	}
	else
	{
		for(i = 0; i < NPC_NUMBEROFRINGS; i++)
		{
			if(this->pRings[i] == pItem)
			{
				this->inventory.Insert(this->pRings[i]);
				this->pRings[i] = NULL;
				isEquipped = true;
				break;
			}
		}
		
		if(!isEquipped)
		{
			for(i = 0; i < NPC_NUMBEROFSPELLSINHAND; i++)
			{
				if(this->pSpells[i] == pItem)
				{
					ASSERT(0);
				}
			}
		}
	}

	if(!isEquipped)
	{
		//item not weared
		return;
	}
	
	//Call the unequip function
	if(pItem->GetOnUnequip() != -1)
	{
		CDaedalusProgram *pProgram;
		CNPC *pOldSelf;

		CGame &refGame = CGame::GetInstance();
		
		pProgram = refGame.GetProgram();
		pOldSelf = pProgram->GetSelf();
		pProgram->SetSelf(this);
		pProgram->ExecuteFunction(pItem->GetOnUnequip());
		pProgram->SetSelf(pOldSelf);
	}
}

void CNPC::Use(CItem *pItem)
{
	ASSERT(this->inventory.Contains(pItem));

	for(uint8 i = 0; i < 4; i++)
	{
		this->CallScriptFunction(pItem->GetOnState(i));
	}
	
	if(pItem->GetMultiplicity() > 1)
	{
		pItem->SetMultiplicity(pItem->GetMultiplicity() - 1);
	}
	else
	{
		this->inventory.Delete(pItem);
		delete pItem;
	}
}