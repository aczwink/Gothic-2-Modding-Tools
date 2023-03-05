//Class Header
#include "CItemInfo.h"
//Local
#include "CNPC.h"
#include "CNPCInfo.h"

//Constructor
CItemInfo::CItemInfo(CInstance *pInstance)
{
	this->pInstance = pInstance;
	this->pItem = new CItem(pInstance->GetName());
	
	this->requiredStrength = 0;
	this->requiredDexterity = 0;
	this->toDex = 0;
	this->toDexPerm = 0;
	this->toLife = 0;
	this->toMana = 0;
	this->toMaxLife = 0;
	this->toMaxLifePerm = 0;
	this->toMaxMana = 0;
	this->toMaxManaPerm = 0;
	this->toOneHandedMeleeWeaponsTalent = 0;
	this->toOneHandedMeleeWeaponsTalentPerm = 0;
	this->toProtEdge = 0;
	this->toProtFire = 0;
	this->toProtMagic = 0;
	this->toProtPoint = 0;
	this->toStr = 0;
	this->toStrPerm = 0;
	this->toTwoHandedMeleeWeaponsTalent = 0;
	
	for(uint8 i = 0; i < 3; i++)
	{
		switch(this->pItem->GetConditionAttribute(i))
		{
		case ATR_DEXTERITY:
			this->requiredDexterity = this->pItem->GetConditionValue(i);
			break;
		case ATR_STRENGTH:
			this->requiredStrength = this->pItem->GetConditionValue(i);
			break;
		}
	}

	this->toProtEdge = this->pItem->GetProtectionAgainstEdge();
	this->toProtFire = this->pItem->GetProtectionAgainstFire();
	this->toProtMagic = this->pItem->GetProtectionAgainstMagic();
	this->toProtPoint = this->pItem->GetProtectionAgainstPoint();
}

//Destructor
CItemInfo::~CItemInfo()
{
	delete this->pItem;
}

//Private methods
void CItemInfo::GetEquipInfo()
{
	CNPC npcHasNone, npcHadIt, npcHasIt;

	npcHadIt.AddItem(this->pItem);
	npcHadIt.Equip(this->pItem);
	npcHadIt.Unequip(this->pItem);
	npcHadIt.RemoveFromInventory(this->pItem);
	
	npcHasIt.AddItem(this->pItem);
	npcHasIt.Equip(this->pItem);

	this->SetDeltas(npcHasNone, npcHasIt, npcHadIt);
	
	//unequip item so that it does not get deleted
	npcHasIt.Unequip(this->pItem);
	npcHasIt.RemoveFromInventory(this->pItem);
}

void CItemInfo::GetUseInfo()
{
	CItem *pItemCopy;
	CNPC didntTakeIt, tookIt;

	//we need a copy because using the item will destroy it
	pItemCopy = new CItem(this->pInstance->GetName());
	
	//set life points so that we can capture a change
	didntTakeIt.SetLifePoints(INT32_MAX / 2);
	didntTakeIt.SetMaxLifePoints(INT32_MAX);
	tookIt.SetLifePoints(INT32_MAX / 2);
	tookIt.SetMaxLifePoints(INT32_MAX);
	
	tookIt.AddItem(pItemCopy);
	tookIt.Use(pItemCopy);
	
	this->SetDeltas(didntTakeIt, didntTakeIt, tookIt);
}

void CItemInfo::SetDeltas(const CNPC &refNPCHasNone, const CNPC &refNPCHasIt, const CNPC &refNPCHadIt)
{
	int32 ignore;
	
	//attributes
	this->SetDelta(refNPCHasNone.GetStrength(), refNPCHasIt.GetStrength(), refNPCHadIt.GetStrength(), this->toStr, this->toStrPerm);
	this->SetDelta(refNPCHasNone.GetDexterity(), refNPCHasIt.GetDexterity(), refNPCHadIt.GetDexterity(), this->toDex, this->toDexPerm);
	this->SetDelta(refNPCHasNone.GetLifePoints(), refNPCHasIt.GetLifePoints(), refNPCHadIt.GetLifePoints(), this->toLife, ignore);
	this->SetDelta(refNPCHasNone.GetManaPoints(), refNPCHasIt.GetManaPoints(), refNPCHadIt.GetManaPoints(), this->toMana, ignore);
	this->SetDelta(refNPCHasNone.GetMaxLifePoints(), refNPCHasIt.GetMaxLifePoints(), refNPCHadIt.GetMaxLifePoints(), this->toMaxLife, this->toMaxLifePerm);
	this->SetDelta(refNPCHasNone.GetMaxManaPoints(), refNPCHasIt.GetMaxManaPoints(), refNPCHadIt.GetMaxManaPoints(), this->toMaxMana, this->toMaxManaPerm);
	this->SetDelta(refNPCHasNone.GetProtectionAgainstEdge(), refNPCHasIt.GetProtectionAgainstEdge(), refNPCHadIt.GetProtectionAgainstEdge(), this->toProtEdge, ignore);
	this->SetDelta(refNPCHasNone.GetProtectionAgainstFire(), refNPCHasIt.GetProtectionAgainstFire(), refNPCHadIt.GetProtectionAgainstFire(), this->toProtFire, ignore);
	this->SetDelta(refNPCHasNone.GetProtectionAgainstMagic(), refNPCHasIt.GetProtectionAgainstMagic(), refNPCHadIt.GetProtectionAgainstMagic(), this->toProtMagic, ignore);
	this->SetDelta(refNPCHasNone.GetProtectionAgainstPoint(), refNPCHasIt.GetProtectionAgainstPoint(), refNPCHadIt.GetProtectionAgainstPoint(), this->toProtPoint, ignore);
	//fight talent
	this->SetDelta(refNPCHasNone.GetHitChance(ITEM_HITCHANGE_1H), refNPCHasIt.GetHitChance(ITEM_HITCHANGE_1H), refNPCHadIt.GetHitChance(ITEM_HITCHANGE_1H), this->toOneHandedMeleeWeaponsTalent, this->toOneHandedMeleeWeaponsTalentPerm);
	this->SetDelta(refNPCHasNone.GetHitChance(ITEM_HITCHANGE_2H), refNPCHasIt.GetHitChance(ITEM_HITCHANGE_2H), refNPCHadIt.GetHitChance(ITEM_HITCHANGE_2H), this->toTwoHandedMeleeWeaponsTalent, ignore);
}

void CItemInfo::SetDelta(int32 hasNone, int32 hasIt, int32 hadIt, int32 &refTemp, int32 &refPerm)
{
	refPerm = hadIt - hasNone;
	refTemp = (hasIt - hasNone) - refPerm;
}

//Public methods
void CItemInfo::AddInstance(CWorld *pWorld, CItem *pItem)
{
	this->instances[pWorld].Push(pItem);
}

void CItemInfo::AddSaler(uint8 chapter, const CNPC *pSaler, const CNPCInfo *pSalerInfo)
{
	this->salers[chapter].Insert(pSaler, pSalerInfo);
}

void CItemInfo::GetEventFunctionInfo()
{
	if(this->pItem->IsEquipable())
	{
		this->GetEquipInfo();
	}
	if(this->pItem->IsUseable())
	{
		this->GetUseInfo();
	}
}

uint32 CItemInfo::GetReceivabilityCount() const
{
	uint32 count;

	if(this->pItem->GetInstanceName().ToLowercase() == "itmw_berserkeraxt")
	{
		stdOut << "blu";
	}
	
	count = 0;
	foreach(it, this->instances)
	{
		foreach(it2, it.GetValue())
		{
			count += it2.GetValue()->GetMultiplicity();
		}
	}

	foreach(it, this->holders)
	{
		count += it.GetValue()->GetItemMultiplicity(this->pItem->GetInstanceName());
	}

	foreach(it, this->salers)
	{
		foreach(it2, it.GetValue())
		{
			count += it2.GetValue()->GetNumberOfItemsForTrade(it.GetKey(), this->pItem->GetInstanceName());
		}
	}
	
	return count;
}