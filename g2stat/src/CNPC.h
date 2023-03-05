#pragma once
//Local
#include "AAccessable.h"
#include "AVob.h"
#include "CItem.h"
#include "CDaedalusVM.h"
//Definitions
#define ATR_HITPOINTS 0
#define ATR_HITPOINTS_MAX 1
#define ATR_MANA 2
#define ATR_MANA_MAX 3
#define ATR_STRENGTH 4
#define ATR_DEXTERITY 5
#define NPC_TALENT_1H 1
#define NPC_TALENT_2H 2
#define NPC_TALENT_BOW 3
#define NPC_TALENT_CROSSBOW 4
#define NPC_NUMBEROFRINGS 2
#define NPC_NUMBEROFSPELLSINHAND 7

namespace SJCPBLib
{
	class CNPC : public AVob, public Daedalus::AAccessable
	{
		friend class CDaedalusVM;
	private:
		//Members
		uint32 internalId;
		CItem *pArmor; //worn armor
		CItem *pMeleeWeapon; //item which is hold in hand
		CItem *pRangedWeapon;
		CItem *pAmulet;
		CItem *pBelt;
		CItem *pRings[NPC_NUMBEROFRINGS]; //one per hand
		CItem *pSpells[NPC_NUMBEROFSPELLSINHAND]; //runes or scrolls on positions 4,5,6,7,8,9,0
		SJCLib::CFiniteSet<CItem *> inventory;
		//Script-Variables
		int32 id;
		SJCLib::CString name[5];
		SJCLib::CString effect;
		int32 npcType;
		int32 flags;
		int32 attribute[8];
		int32 hitChance[5];
		int32 protection[8];
		int32 damage[8];
		int32 damageType;
		int32 guild;
		int32 level;
		int32 fightTactic;
		int32 voice;
		int32 dailyRoutine; //func
		int32 startAIState; //func
		int32 senses;
		int32 sensesRange;
		int32 aivar[100];
		int32 exp;
		int32 expNext;
		int32 lp;
		int32 bodyStateInterruptableOverride;
		int32 noFocus;
		//Methods
		void CallScriptFunction(int32 symbolIndex);
		void EquipItem(CItem *pItem);
		CItem *FindInventoryItem(const SJCLib::CString &refItemInstance) const;
		void Init();
	public:
		//Constructors
		CNPC();
		CNPC(const SJCLib::CString &refNPCName);
		//Destructor
		~CNPC();
		//Functions
		void ClearInventory();
		void EquipArmor(CItem *pItem);
		void Equip(CItem *pItem);
		uint32 GetItemMultiplicity(const SJCLib::CString &refItemInstance) const; //0 if item not in inventory
		void *GetMemberAddress(uint32 offset, uint8 arrayIdx);
		void RemoveItems(const SJCLib::CString &refItemInstance, uint32 amount);
		bool SetInt(const SJCLib::CString &refMember, int32 value);
		bool SetString(const SJCLib::CString &refMember, const SJCLib::CString &refValue);
		void Unequip(CItem *pItem);
		void Use(CItem *pItem);

		//Inline
		inline void AddItem(CItem *pItem)
		{
			this->inventory.Insert(pItem);
		}

		inline void EmptyInventory()
		{
			this->inventory.Release();
		}

		inline const CItem *GetAmulet() const
		{
			return this->pAmulet;
		}

		inline const CItem *GetArmor() const
		{
			return this->pArmor;
		}

		inline int32 GetAttribute(uint8 attributeIndex) const
		{
			return this->attribute[attributeIndex];
		}

		inline int32 GetDexterity() const
		{
			return this->attribute[ATR_DEXTERITY];
		}

		inline int32 GetHitChance(uint8 hitchangeIndex) const
		{
			return this->hitChance[hitchangeIndex];
		}

		inline uint32 GetInternalId() const
		{
			return this->internalId;
		}
		
		inline const SJCLib::CFiniteSet<CItem *> &GetInventory() const
		{
			return this->inventory;
		}

		inline int32 GetLevel() const
		{
			return this->level;
		}

		inline int32 GetLifePoints() const
		{
			return this->attribute[ATR_HITPOINTS];
		}

		inline int32 GetManaPoints() const
		{
			return this->attribute[ATR_MANA];
		}

		inline int32 GetMaxLifePoints() const
		{
			return this->attribute[ATR_HITPOINTS_MAX];
		}

		inline int32 GetMaxManaPoints() const
		{
			return this->attribute[ATR_MANA_MAX];
		}

		inline const CItem *GetMeleeWeapon() const
		{
			return this->pMeleeWeapon;
		}
		
		inline const SJCLib::CString &GetName() const
		{
			return this->name[0];
		}

		inline int32 GetProtectionAgainstEdge() const
		{
			return this->protection[2];
		}

		inline int32 GetProtectionAgainstFire() const
		{
			return this->protection[3];
		}

		inline int32 GetProtectionAgainstMagic() const
		{
			return this->protection[5];
		}

		inline int32 GetProtectionAgainstPoint() const
		{
			return this->protection[6];
		}

		inline const CItem *GetRangedWeapon() const
		{
			return this->pRangedWeapon;
		}

		inline int32 GetStrength() const
		{
			return this->attribute[ATR_STRENGTH];
		}

		inline void RemoveFromInventory(CItem *pItem)
		{
			this->inventory.Delete(pItem);
		}

		inline void SetAttribute(uint8 attributeIdx, int32 value)
		{
			this->attribute[attributeIdx] = value;
		}

		inline void SetMaxLifePoints(uint32 lifePoints)
		{
			this->attribute[ATR_HITPOINTS_MAX] = lifePoints;
		}
		
		inline void SetLifePoints(uint32 lifePoints)
		{
			this->attribute[ATR_HITPOINTS] = lifePoints;
		}
	};
}