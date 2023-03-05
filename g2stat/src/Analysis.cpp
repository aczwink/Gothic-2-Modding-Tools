//Main Header
#include "CreateDocs.h"
//Local
#include "CGame.h"
#include "globals.h"
/*
#include "CInfo.h"

//Local Functions
void AnalyzeInstance(const SInstance *pInstance)
{
	if(*pInstance->pClassName == "C_INFO")
	{
		AnalyzeInfoInstance(*pInstance->pNames->pName);
	}
	else if(*pInstance->pClassName == "C_NPC")
	{
		AnalyzeNPCInstance(*pInstance->pNames->pName, pInstance);
	}
}

//Global Functions
void Analyze(CCompilePreprocessor &refCompilePreproc)
{
	SGlobals *pGlobal;

	//Loop through all instances
	for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		switch(pGlobal->type)
		{
		case GLOBALTYPE_INSTANCE:
			{
				AnalyzeInstance(pGlobal->value.pInstance);
			}
			break;
		}
	}

	//Loop through all merchant infos
	foreach(it, g_merchantInfo)
	{
		AnalyzeMerchantInfo(it.GetValue());
	}
}*/