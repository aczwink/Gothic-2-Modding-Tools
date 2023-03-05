/*//Main Header
#include "CreateDocs.h"
//SJC Libs
#include <SJCWinLib.h>
//Local
#include "CGame.h"
#include "Daedalus.h"
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

void OutputItemInfo(AOutputStream &refOutput, const CString &refItemInstance, SInstance *pInstance)
{
	uint32 nEncodedBytes;
	CItem *pItem;
	SItemInstanceInfo itemInstanceInfo;
	byte utf8encoded[UTF8_BUFFERSIZE];
	
	pItem = new CItem(refItemInstance);
	
	refOutput << "<tr><td>Name</td><td>";
	nEncodedBytes = UTF8Encode(pItem->GetName(), utf8encoded);
	refOutput.WriteBytes(utf8encoded, nEncodedBytes);
	refOutput << "</td></tr>";
	
	refOutput << "<tr><td>Description</td><td>";
	nEncodedBytes = UTF8Encode(pItem->GetDescription(), utf8encoded);
	refOutput.WriteBytes(utf8encoded, nEncodedBytes);
	refOutput << "</td></tr>";

	refOutput << "<tr><td>Value</td><td>" << pItem->GetValue() << "</td></tr>";

	//Fill out structure
	itemInstanceInfo.pItem = pItem;
	itemInstanceInfo.pInstance = pInstance;
	g_itemInstances.Push(itemInstanceInfo);
}

void OutputNPCInfo(AOutputStream &refOutput, const CString &refNPCInstance)
{
}

/*void OutputInfoInfo(AOutputStream &refOutput, const CString &refInfoInstance)
{
	//npc
	
	//nr
	refOutput << "<tr><td>Number</td><td>" << pInfo->GetNumber() << "</td></tr>";

	//important
	refOutput << "<tr><td>Important</td><td>" << pInfo->IsImportant() << "</td></tr>";

	//condition
	//information

	//description
	refOutput << "<tr><td>Description</td><td>" << pInfo->GetDescription() << "</td></tr>";

	//trade
	refOutput << "<tr><td>Trade</td><td>" << pInfo->IsTrade() << "</td></tr>";

	//permanent
	refOutput << "<tr><td>Permanent</td><td>" << pInfo->IsPermanent() << "</td></tr>";
}* /

bool CreateInstancesDoc(CString outputPath, SInstance *pInstance, SInstanceInfo &refInfo, CCompilePreprocessor &refCompilePreproc)
{
	return true;
	/*
	
	//Print the variable values
	file << "<h2>Member values dump</h2>";
	file << "<table>";
	file << "<tr><th>Member</th><th>Value</th></tr>";

	file << "</table>";


	* /
	
	return true;
}

bool CreateInstancesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	/*for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		if(pGlobal->type != GLOBALTYPE_INSTANCE)
			continue;

		pInstance = pGlobal->value.pInstance;
		
		//Class/Prototype
		file << "<td><a href=\"";

		if(refCompilePreproc.IsPrototypeDefined(*pInstance->pClassName))
		{
			file << "prototypes";
		}
		else
		{
			file << "classes";
		}
		file << "/" << *pInstance->pClassName << ".htm\">" << *pInstance->pClassName << "</a></td>";
		//Defined in
		file << "<td>" << *pInstance->pFileName << ":" << pInstance->lineNumber << "</td>";
		//Referenced
		file << "<td" << (refInfo.nReferences == 0 ? " class=\"warning\")" : "") << ">" << refInfo.nReferences << "</td>";
	}* /
	
	return true;
}*/