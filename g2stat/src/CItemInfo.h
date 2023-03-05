//Local
#include "OptAST/CInstance.h"
#include "CItem.h"
#include "CWorld.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

class CNPCInfo;

class CItemInfo
{
private:
	//Members
	CInstance *pInstance;
	CItem *pItem;
	CMap<CWorld *, CArray<CItem *>> instances;
	CFiniteSet<const CNPC *> holders;
	CMap<uint8, CMap<const CNPC *, const CNPCInfo *>> salers;
	int32 toStr; //str change as long as item is equipped
	int32 toStrPerm; //permanent str change
	int32 toDex;
	int32 toDexPerm;
	int32 toLife;
	int32 toMaxLife;
	int32 toMaxLifePerm;
	int32 toMana;
	int32 toMaxMana;
	int32 toMaxManaPerm;
	int32 toOneHandedMeleeWeaponsTalent;
	int32 toOneHandedMeleeWeaponsTalentPerm;
	int32 toTwoHandedMeleeWeaponsTalent;
	int32 toProtEdge; //as long as item is equipped
	int32 toProtFire; //as long as item is equipped
	int32 toProtMagic; //as long as item is equipped
	int32 toProtPoint; //as long as item is equipped
	int32 requiredStrength;
	int32 requiredDexterity;
	//Methods
	void GetEquipInfo();
	void GetUseInfo();
	void SetDelta(int32 hasNone, int32 hasIt, int32 hadIt, int32 &refTemp, int32 &refPerm);
	void SetDeltas(const CNPC &refNPCHasNone, const CNPC &refNPCHasIt, const CNPC &refNPCHadIt);
public:
	//Constructor
	CItemInfo(CInstance *pInstance);
	//Destructor
	~CItemInfo();
	//Methods
	void AddInstance(CWorld *pWorld, CItem *pItem);
	void AddSaler(uint8 chapter, const CNPC *pSaler, const CNPCInfo *pSalerInfo);
	void GetEventFunctionInfo();
	uint32 GetReceivabilityCount() const;
	//Inline
	inline void AddHolder(const CNPC *pNPC)
	{
		this->holders.Insert(pNPC);
	}

	inline int32 GetDexterityChange() const
	{
		return this->toDex;
	}

	inline const CFiniteSet<const CNPC *> &GetHolders() const
	{
		return this->holders;
	}
	
	inline const CInstance *GetInstance() const
	{
		return this->pInstance;
	}

	inline const CMap<CWorld *, CArray<CItem *>> &GetInstances() const
	{
		return this->instances;
	}
	
	inline const CItem *GetItem() const
	{
		return this->pItem;
	}

	inline int32 GetLifePointsChange() const
	{
		return this->toLife;
	}

	inline int32 GetManaPointsChange() const
	{
		return this->toMana;
	}

	inline int32 GetMaxLifePointsChange() const
	{
		return this->toMaxLife;
	}

	inline int32 GetMaxManaPointsChange() const
	{
		return this->toMaxMana;
	}
	
	inline int32 GetOneHandedMeleeWeaponsTalentChange() const
	{
		return this->toOneHandedMeleeWeaponsTalent;
	}

	inline int32 GetPermanentDexterityChange() const
	{
		return this->toDexPerm;
	}

	inline int32 GetPermanentMaxLifePointsChange() const
	{
		return this->toMaxLifePerm;
	}
	
	inline int32 GetPermanentMaxManaPointsChange() const
	{
		return this->toMaxManaPerm;
	}
	
	inline int32 GetPermanentStrengthChange() const
	{
		return this->toStrPerm;
	}

	inline int32 GetProtectionAgainstEdgeChange() const
	{
		return this->toProtEdge;
	}

	inline int32 GetProtectionAgainstFireChange() const
	{
		return this->toProtFire;
	}

	inline int32 GetProtectionAgainstMagicChange() const
	{
		return this->toProtMagic;
	}

	inline int32 GetProtectionAgainstPointChange() const
	{
		return this->toProtPoint;
	}

	inline int32 GetRequiredDexterity() const
	{
		return this->requiredDexterity;
	}

	inline int32 GetRequiredStrength() const
	{
		return this->requiredStrength;
	}

	inline int32 GetStrengthChange() const
	{
		return this->toStr;
	}

	inline int32 GetTwoHandedMeleeWeaponsTalentChange() const
	{
		return this->toTwoHandedMeleeWeaponsTalent;
	}

	inline const CMap<uint8, CMap<const CNPC *, const CNPCInfo *>> &GetVendors() const
	{
		return this->salers;
	}
};