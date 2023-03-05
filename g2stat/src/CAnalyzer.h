#pragma once
//Local
#include "CCompiler.h"
#include "CGame.h"
#include "CInfo.h"
#include "CItemInfo.h"
#include "CNPCInfo.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

class CAnalyzer
{
private:
	//Members
	CCompiler &refCompiler;
	CMap<CString, CItemInfo *> itemInfo;
	CMap<CString, CNPCInfo *> npcInfo;
	CMap<CNPCInfo *, CInfo *> merchants;
	//Methods
	void AddHolder(const CItem *pItem, const CNPC *pHolder);
	void AddSaleItem(const CItem *pItem, CNPCInfo *pSalerInfo, uint8 chapter);
	void AnalyzeInfoInstance(CInstance *pInstance);
	void AnalyzeInfoInstances();
	void AnalyzeInstance(CInstance *pInstance);
	void AnalyzeInventory(CNPCInfo *pInfo);
	void AnalyzeMerchants();
	void AnalyzeWorlds();
public:
	//Constructor
	CAnalyzer(CCompiler &refCompiler);
	//Destructor
	~CAnalyzer();
	//Methods
	const CNPCInfo *GetVendor(const CString &refInstanceName);
	void Run();
	//Inline
	inline const CMap<CString, CItemInfo *> &GetItemInfos() const
	{
		return this->itemInfo;
	}

	inline const CMap<CNPCInfo *, CInfo *> &GetMerchants() const
	{
		return this->merchants;
	}

	inline const CMap<CString, CNPCInfo *> &GetNPCInfos() const
	{
		return this->npcInfo;
	}
};