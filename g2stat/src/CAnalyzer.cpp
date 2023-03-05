//Class Header
#include "CAnalyzer.h"
//Local
#include "CInfo.h"
#include "CTriggerChangeLevel.h"

//Constructor
CAnalyzer::CAnalyzer(CCompiler &refCompiler) : refCompiler(refCompiler)
{
}

//Destructor
CAnalyzer::~CAnalyzer()
{
	foreach(it, this->itemInfo)
	{
		delete it.GetValue();
	}
	this->itemInfo.Release();

	foreach(it, this->merchants)
	{
		delete it.GetValue();
	}

	foreach(it, this->npcInfo)
	{
		delete it.GetValue();
	}
}

//Private methods
void CAnalyzer::AddHolder(const CItem *pItem, const CNPC *pNPC)
{
	if(!pItem)
		return;
	
	this->itemInfo[pItem->GetInstanceName().ToLowercase()]->AddHolder(pNPC);
}

void CAnalyzer::AddSaleItem(const CItem *pItem, CNPCInfo *pSalerInfo, uint8 chapter)
{
	if(!pItem)
		return;
	
	pSalerInfo->AddSaleItem(chapter, pItem);
	this->itemInfo[pItem->GetInstanceName().ToLowercase()]->AddSaler(chapter, pSalerInfo->GetNPC(), this->npcInfo[pSalerInfo->GetNPC()->GetInstanceName().ToLowercase()]);
}

void CAnalyzer::AnalyzeInfoInstance(CInstance *pInstance)
{
	CInfo *pInfo;
	CDaedalusProgram *pProgram;
	
	CGame &refGame = CGame::GetInstance();
	
	pProgram = refGame.GetProgram();
	
	pProgram->SetOther(refGame.GetHero()); //set 'hero' as 'other' for 'description' member
	pInfo = new CInfo(pInstance->GetName());
	
	if(pInfo->IsTrade())
	{
		const SSymbol &refNPCSymbol = pProgram->GetSymbol(pInfo->GetNPCSymbolIndex());
		
		this->merchants[this->npcInfo[refNPCSymbol.name.ToLowercase()]] = pInfo;
	}
	else
	{
		delete pInfo;
	}
}

void CAnalyzer::AnalyzeInfoInstances()
{
	CClass *pClass;

	const CMap<CString, CInstance *> &refInstances = this->refCompiler.GetInstances();
	
	foreach(it, refInstances)
	{
		pClass = it.GetValue()->GetClass();
		if(pClass->GetName() == "C_INFO")
		{
			this->AnalyzeInfoInstance(it.GetValue());
		}
	}
}

void CAnalyzer::AnalyzeInstance(CInstance *pInstance)
{
	CClass *pClass;
	
	pClass = pInstance->GetClass();
	if(pClass->GetName() == "C_NPC")
	{
		this->npcInfo.Insert(pInstance->GetName().ToLowercase(), new CNPCInfo(pInstance));
	}
	else if(pClass->GetName() == "C_Item")
	{
		this->itemInfo.Insert(pInstance->GetName().ToLowercase(), new CItemInfo(pInstance));
	}
}

void CAnalyzer::AnalyzeInventory(CNPCInfo *pInfo)
{
	const CNPC *pNPC;
	
	pNPC = pInfo->GetNPC();
	
	this->AddHolder(pNPC->GetAmulet(), pNPC);

	foreach(it, pNPC->GetInventory())
	{
		this->AddHolder(it.GetValue(), pNPC);
	}
}

void CAnalyzer::AnalyzeMerchants()
{
	uint8 chapter;
	uint32 currentIndex;
	CDaedalusProgram *pProgram;
	CArray<CNPC *> tmpTraders;
	
	CGame &refGame = CGame::GetInstance();
	
	pProgram = refGame.GetProgram();
	
	foreach(it, this->merchants)
	{
		const SSymbol &refNPCSymbol = pProgram->GetSymbol(it.GetValue()->GetNPCSymbolIndex());
		
		tmpTraders.Push(new CNPC(refNPCSymbol.name));
	}
	
	currentIndex = 0;
	foreach(it, this->merchants)
	{
		const SSymbol &refNPCSymbol = pProgram->GetSymbol(it.GetValue()->GetNPCSymbolIndex());
		
		pProgram->SetSelf(tmpTraders[currentIndex]);
		pProgram->SetOther(refGame.GetHero()); //set 'hero' as 'other' for 'description' member
		
		tmpTraders[currentIndex]->ClearInventory(); //clear ambient inventory...
		for(chapter = 1; chapter <= 6; chapter++)
		{
			pProgram->SetGlobalVariable("Kapitel", chapter);
			pProgram->ExecuteFunction(it.GetValue()->GetInformationSymbolIndex());
			foreach(it2, tmpTraders[currentIndex]->GetInventory())
			{
				this->AddSaleItem(it2.GetValue(), this->npcInfo[refNPCSymbol.name.ToLowercase()], chapter);
			}
			tmpTraders[currentIndex]->EmptyInventory();
		}

		currentIndex++;
	}

	foreach(it, tmpTraders)
	{
		delete it.GetValue();
	}
}

void CAnalyzer::AnalyzeWorlds()
{
	CDaedalusProgram *pProgram;
	CWorld *pWorld;
	CItem *pItem;
	CNPC *pNPC;
	CTriggerChangeLevel *pTrigger;
	CString currentWorldName;
	CArray<CString> worldsStack;
	CArray<CWorld *> worlds;
	CFiniteSet<CString> finishedWorlds;
	
	CGame &refGame = CGame::GetInstance();
	
	pProgram = refGame.GetProgram();
	
	refGame.StartNewGame(); //enters start world
	
	//collect all worlds first
	worldsStack.Push(refGame.GetDefaultWorldName());
	while(!worldsStack.IsEmpty())
	{
		currentWorldName = worldsStack.Pop();
		if(finishedWorlds.Contains(currentWorldName.ToLowercase()))
			continue;
		
		finishedWorlds.Insert(currentWorldName.ToLowercase());
		//enter each world one time so that startup function gets called (which may set the chapter)
		refGame.EnterWorld(currentWorldName);
		pWorld = refGame.GetActiveWorld(); //get start world
		worlds.Push(pWorld);
		
		foreach(it2, pWorld->GetVobs())
		{
			pTrigger = dynamic_cast<CTriggerChangeLevel *>(*it2);
			if(pTrigger)
				worldsStack.Push(pTrigger->GetLevelName());
		}
	}
	
	//set the max chapter for world analysis
	pProgram->SetGlobalVariable("Kapitel", 6);

	foreach(it, worlds)
	{
		pWorld = it.GetValue();
		
		foreach(it, pWorld->GetVobs())
		{
			//npcs
			pNPC = dynamic_cast<CNPC *>(*it);
			if(pNPC)
			{
				this->npcInfo[pNPC->GetInstanceName().ToLowercase()]->AddInstance(pWorld, pNPC);
			}

			//items
			pItem = dynamic_cast<CItem *>(*it);
			if(pItem)
			{
				this->itemInfo[pItem->GetInstanceName().ToLowercase()]->AddInstance(pWorld, pItem);
			}
		}
	}
	
	//pProgram->SetSelf(refGame.GetHero());
	//pProgram->ExecuteFunction("Use_FireStew");
}

//Public methods
const CNPCInfo *CAnalyzer::GetVendor(const CString &refInstanceName)
{
	auto &refIt = this->npcInfo.Find(refInstanceName.ToLowercase());

	if(refIt.IsValid())
	{
		auto &refIt2 = this->merchants.Find(refIt.GetValue());

		if(refIt2.IsValid())
		{
			return refIt2.GetKey();
		}
	}

	return NULL;
}

void CAnalyzer::Run()
{
	const CMap<CString, CInstance *> &refInstances = this->refCompiler.GetInstances();
	
	foreach(it, refInstances)
	{
		this->AnalyzeInstance(it.GetValue());
	}
	
	this->AnalyzeInfoInstances();
	this->AnalyzeWorlds();
	
	foreach(it, this->itemInfo)
	{
		it.GetValue()->GetEventFunctionInfo();
	}

	foreach(it, this->npcInfo)
	{
		this->AnalyzeInventory(it.GetValue());
	}

	this->AnalyzeMerchants();
}