//Local
#include "OptAST/CInstance.h"
#include "CNPC.h"
#include "CWorld.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

class CNPCInfo
{
private:
	//Members
	CInstance *pInstance;
	CNPC *pNPC;
	CMap<CWorld *, CArray<CNPC *>> instances;
	CMap<uint8, CMap<CString, const CItem *>> itemsForTrade;
public:
	//Constructor
	CNPCInfo(CInstance *pInstance);
	//Destructor
	~CNPCInfo();
	//Methods
	void AddInstance(CWorld *pWorld, CNPC *pNPC);
	void AddSaleItem(uint8 chapter, const CItem *pItem);
	uint32 GetNumberOfItemsForTrade(uint8 chapter, const CString &refItemInstanceName) const;
	//Inline
	inline const CInstance *GetInstance() const
	{
		return this->pInstance;
	}

	inline const CMap<CWorld *, CArray<CNPC *>> &GetInstances() const
	{
		return this->instances;
	}

	inline const CMap<uint8, CMap<CString, const CItem *>> &GetItemsForTrade() const
	{
		return this->itemsForTrade;
	}

	inline const CNPC *GetNPC() const
	{
		return this->pNPC;
	}
};