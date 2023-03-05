#pragma once
//Local
#include "AAccessable.h"
#include "AVob.h"
//Definitions
#define ITEM_MAINFLAG_MISC 1 //stuff
#define ITEM_MAINFLAG_MELEE 2 //Melee Weapons
#define ITEM_MAINFLAG_RANGED 4 //Ranged Weapons
#define ITEM_MAINFLAG_ARMOR 0x10
#define ITEM_MAINFLAG_FOOD 0x20
#define ITEM_MAINFLAG_DOCS 0x40
#define ITEM_MAINFLAG_POTIONS 0x80
#define ITEM_MAINFLAG_SPELL 0x200 //Runes, Scrolls
#define ITEM_MAINFLAG_MAGIC 0x80000000 //Ringe/Amulette/Guertel

#define ITEM_FLAGS_RINGS        0x800
#define ITEM_FLAGS_SWORD       0x4000
#define ITEM_FLAGS_AXE         0x8000
#define ITEM_FLAGS_2HD_SWORD  0x10000
#define ITEM_FLAGS_2HD_AXE    0x20000
#define ITEM_FLAGS_BOW        0x80000
#define ITEM_FLAGS_CROSSBOW  0x100000
#define ITEM_FLAGS_STACKABLE 0x200000
#define ITEM_FLAGS_AMULET    0x400000
#define ITEM_FLAGS_BELTS    0x1000000

#define ITEM_HITCHANGE_1H 1
#define ITEM_HITCHANGE_2H 2

namespace SJCPBLib
{
	class CItem : public AVob, public Daedalus::AAccessable
	{
	private:
		//Members
		uint32 multiplicity; //multiplicity of this item (for instance 100 arrows are stored with multiplicity instead of 100 objects)
		//Daedalus-Script members
		int32 id;
		SJCLib::CString name;
		int32 hp;
		int32 hpMax;
		int32 mainFlag;
		int32 flags;
		int32 weight;
		int32 value;
		int32 damageType;
		int32 damageTotal;
		int32 wear;
		int32 protection[8];
		int32 conditionAttribute[3];
		int32 conditionValue[3];
		int32 changeValue[3];
		int32 onEquip; //func
		int32 onUnequip; //func
		int32 onState[4]; //func
		int32 owner; //func
		SJCLib::CString visual;
		SJCLib::CString visualChange;
		SJCLib::CString effect;
		int32 visualSkin;
		SJCLib::CString scemeName;
		int32 material;
		int32 munition;
		int32 spell;
		int32 range;
		int32 magCircle;
		SJCLib::CString description;
		SJCLib::CString text[6];
		int32 count[6];
		int32 invZBias;
		int32 invRotX;
		int32 invRotY;
		int32 invRotZ;
		//Methods
		void CallScriptConstructor();
		void Init();
	public:
		//Constructors
		CItem();
		CItem(const SJCLib::CString &refItemName);
		//Destructor
		~CItem();
		//Functions
		void *GetMemberAddress(uint32 offset, uint8 arrayIdx);
		bool IsEquipable() const;
		bool IsUseable() const;
		bool SetInt(const SJCLib::CString &refMember, int32 value);
		bool SetString(const SJCLib::CString &refMember, const SJCLib::CString &refValue);
		
		//Inline
		inline int32 GetConditionAttribute(uint8 index) const
		{
			return this->conditionAttribute[index];
		}

		inline int32 GetConditionValue(uint8 index) const
		{
			return this->conditionValue[index];
		}

		inline int32 GetCount(uint8 index) const
		{
			return this->count[index];
		}

		inline int32 GetDamageTotal() const
		{
			return this->damageTotal;
		}

		inline const SJCLib::CString &GetDescription() const
		{
			return this->description;
		}

		inline int32 GetFlags() const
		{
			return this->flags;
		}

		inline int32 GetMagicalCircle() const
		{
			return this->magCircle;
		}

		inline int32 GetMainFlag() const
		{
			return this->mainFlag;
		}

		inline uint32 GetMultiplicity() const
		{
			return this->multiplicity;
		}

		inline const SJCLib::CString &GetName() const
		{
			return this->name;
		}

		inline int32 GetOnEquip() const
		{
			return this->onEquip;
		}

		inline int32 GetOnState(uint8 index) const
		{
			return this->onState[index];
		}

		inline int32 GetOnUnequip() const
		{
			return this->onUnequip;
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

		inline int32 GetRange() const
		{
			return this->range;
		}

		inline const SJCLib::CString &GetText(uint8 index) const
		{
			return this->text[index];
		}

		inline uint32 GetValue() const
		{
			return this->value;
		}

		inline void SetMultiplicity(uint32 multiplicity)
		{
			this->multiplicity = multiplicity;
		}
	};
}