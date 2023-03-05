//Class Header
#include "CNPCInfo.h"

//Constructor
CNPCInfo::CNPCInfo(CInstance *pInstance)
{
	this->pInstance = pInstance;
	this->pNPC = new CNPC(pInstance->GetName());
}

//Destructor
CNPCInfo::~CNPCInfo()
{
	delete this->pNPC;

	foreach(it, this->itemsForTrade)
	{
		foreach(it2, it.GetValue())
		{
			delete it2.GetValue();
		}
	}
}

//Public methods
void CNPCInfo::AddInstance(CWorld *pWorld, CNPC *pNPC)
{
	this->instances[pWorld].Push(pNPC);
}

void CNPCInfo::AddSaleItem(uint8 chapter, const CItem *pItem)
{
	this->itemsForTrade[chapter].Insert(pItem->GetInstanceName().ToLowercase(), pItem);
}

uint32 CNPCInfo::GetNumberOfItemsForTrade(uint8 chapter, const CString &refItemInstanceName) const
{
	auto &refIt = this->itemsForTrade.Find(chapter);
	
	if(refIt.IsValid())
	{
		auto &refIt2 = refIt.GetValue().Find(refItemInstanceName.ToLowercase());
		if(refIt2.IsValid())
		{
			return refIt2.GetValue()->GetMultiplicity();
		}
	}
	return 0;
}