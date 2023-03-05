//Main Header
#include "CreateDocs.h"
//Global
#include <Windows.h>
//Local
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"

//Prototypes
bool CreateAmuletsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateArmorsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateBeltsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateBowsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateCrossbowsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateDocsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateFoodDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateMiscDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateOneHandedMeleeWeaponsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateOthersDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreatePotionsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateRingsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateRunesDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateScrollsDoc(CAnalyzer &refAnalyzer, CString outputPath);
bool CreateTwoHandedMeleeWeaponsDoc(CAnalyzer &refAnalyzer, CString outputPath);

bool CreateItemInfo(CItemInfo *pInfo, const CString &refPath, CAnalyzer &refAnalyzer)
{
	uint32 currentCount, count;
	const CItem *pItem;
	const CInstance *pInstance;
	const CNPCInfo *pVendor;
	CFileOutputStream file;
	
	CTextWriter &refWriter = CTextWriter(file);
	
	pItem = pInfo->GetItem();
	pInstance = pInfo->GetInstance();
	
	if(!file.Open(refPath + '\\' + pItem->GetInstanceName() + ".htm"))
		ERRORMSG("couldn't create output for item '" + pItem->GetInstanceName() + "'");
	
	WriteHTMLHead(pItem->GetInstanceName(), file, "../../");
	
	file << "<h1>" << pItem->GetInstanceName() << "</h1>";

	//----------
	//attributes
	//----------
	file << "<h3>Attributes</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Attribute");
	WriteHTMLTableHeadCol(file, "Value");
	WriteHTMLTableHeadEnd(file);
	
	//name
	file << "<tr>";
	file << "<td>Name</td>";
	file << "<td>";
	refWriter.WriteUTF8(pItem->GetName());
	file << "</td>";
	file << "</tr>";

	//description
	file << "<tr>";
	file << "<td>Description</td>";
	file << "<td>";
	refWriter.WriteUTF8(pItem->GetDescription());
	file << "</td>";
	file << "</tr>";

	//value
	file << "<tr>";
	file << "<td>Value in gold</td>";
	file << "<td>" << pItem->GetValue() << "</td>";
	file << "</tr>";

	WriteHTMLTableFoot(file);

	//---------------
	//effects when equipped
	//---------------
	if(pItem->IsEquipable())
	{
		file << "<h3>Effects when equipped</h3>";
		WriteHTMLTableHeadBegin(file);
		WriteHTMLTableHeadCol(file, "Name");
		WriteHTMLTableHeadCol(file, "Value");
		WriteHTMLTableHeadEnd(file);
		
		//to strength
		file << "<tr>";
		file << "<td>To strength</td>";
		file << "<td>" << pInfo->GetStrengthChange() << "</td>";
		file << "</tr>";

		//to dexterity
		file << "<tr>";
		file << "<td>To dexterity</td>";
		file << "<td>" << pInfo->GetDexterityChange() << "</td>";
		file << "</tr>";

		//to lifepoints
		file << "<tr>";
		file << "<td>To lifepoints</td>";
		file << "<td>" << pInfo->GetMaxLifePointsChange() << "</td>";
		file << "</tr>";

		//to manapoints
		file << "<tr>";
		file << "<td>To manapoints</td>";
		file << "<td>" << pInfo->GetMaxManaPointsChange() << "</td>";
		file << "</tr>";

		//to protection against edge
		file << "<tr>";
		file << "<td>To protection against edge</td>";
		file << "<td>" << pInfo->GetProtectionAgainstEdgeChange() << "</td>";
		file << "</tr>";

		//to protection against fire
		file << "<tr>";
		file << "<td>To protection against fire</td>";
		file << "<td>" << pInfo->GetProtectionAgainstFireChange() << "</td>";
		file << "</tr>";

		//to protection against magic
		file << "<tr>";
		file << "<td>To protection against magic</td>";
		file << "<td>" << pInfo->GetProtectionAgainstMagicChange() << "</td>";
		file << "</tr>";

		//to protection against point
		file << "<tr>";
		file << "<td>To protection against point</td>";
		file << "<td>" << pInfo->GetProtectionAgainstPointChange() << "</td>";
		file << "</tr>";

		WriteHTMLTableFoot(file);
	}

	//---------------
	//Receivability
	//---------------
	file << "<h3>Receivability</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Kind");
	WriteHTMLTableHeadCol(file, "Detail");
	WriteHTMLTableHeadCol(file, "Sum");
	WriteHTMLTableHeadEnd(file);
	
	//findability
	foreach(it, pInfo->GetInstances())
	{
		file << "<tr>";
		file << "<td>Findable in: " << it.GetKey()->GetName() << "</td>";
		file << "<td></td>";
		file << "<td>" << it.GetValue().GetNoOfElements() << "</td>";
		file << "</tr>";
	}
	
	//npcs
	file << "<tr>";
	file << "<td>NPC's having this item</td>";
	file << "<td>";
	foreach(it, pInfo->GetHolders())
	{
		file << "<a href=\"../../npcs/instances/" << it.GetValue()->GetInstanceName() << ".htm\">" << it.GetValue()->GetName() << "</a><br />";
	}
	file << "</td>";
	file << "<td>" << pInfo->GetHolders().GetNoOfElements() << "</td>";
	file << "</tr>";

	//salers
	foreach(it, pInfo->GetVendors())
	{
		count = 0;

		file << "<tr>";
		file << "<td>NPC's selling this item in chapter " << it.GetKey() << "</td>";
		file << "<td>";
		foreach(it2, it.GetValue())
		{
			pVendor = it2.GetValue();
			
			currentCount = pVendor->GetNumberOfItemsForTrade(it.GetKey(), pItem->GetInstanceName());
			count += currentCount;
			file << "<a href=\"../../npcs/instances/" << it2.GetKey()->GetInstanceName() << ".htm\">" << it2.GetKey()->GetName() << "</a>";
			if(currentCount > 1)
				file << " (" << currentCount << ')';
			file << "<br />";
		}
		file << "</td>";
		file << "<td>" << count << "</td>";
		file << "</tr>";
	}
	
	//sum
	file << "<tr>";
	file << "<td><b>Sum</b></td>";
	file << "<td></td>";
	file << "<td>" << pInfo->GetReceivabilityCount() << "</td>";
	file << "</tr>";
	
	WriteHTMLTableFoot(file);

	//---------------
	//additional info
	//---------------
	file << "<h3>Additional info</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Value");
	WriteHTMLTableHeadCol(file, "Sum");
	WriteHTMLTableHeadEnd(file);
	//defined in
	file << "<tr>";
	file << "<td>Defined in</td>";
	file << "<td>" << pInstance->GetFileName() << ':' << pInstance->GetLineNumber() << "</td>";
	file << "</tr>";

	//referenced
	file << "<tr>";
	file << "<td>Reference count</td>";
	file << "<td>" << pInstance->GetReferenceCount() << "</td>";
	file << "</tr>";

	WriteHTMLTableFoot(file);

	//---------------
	//text
	//---------------
	file << "<h3>Text</h3>";
	file << "<table class=\"tableborder_only\">";
	for(uint8 i = 0; i < 6; i++)
	{
		file << "<tr>";
		file << "<td>";
		if(!pItem->GetText(i).IsEmpty())
			refWriter.WriteUTF8(pItem->GetText(i));
		file << "</td><td class=\"txtright\">";
		if(pItem->GetCount(i) != -1)
			file << pItem->GetCount(i);
		file << "</td>";
		file << "</tr>";
	}
	file << "</table>";
	
	WriteHTMLFoot(file);
	
	return true;
}

bool CreateItemsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	CFileOutputStream file;
	CString instancesPath;

	stdOut << "Creating 'Items' files." << endl;
	
	if(!CreateDirectory((outputPath + "\\items").GetC_Str(), NULL))
		ERRORMSG("'items' folder in Output folder couldn't be created.");
	outputPath += "\\items";
	instancesPath = outputPath + "\\instances";
	if(!CreateDirectory((instancesPath).GetC_Str(), NULL))
		ERRORMSG("'instances' folder in Output folder couldn't be created.");

	foreach(it, refAnalyzer.GetItemInfos())
	{
		if(!CreateItemInfo(it.GetValue(), instancesPath, refAnalyzer))
			ERRORMSG("couldn't create item information");
	}
	
	if(!CreateAmuletsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateArmorsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateBeltsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateBowsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateCrossbowsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateDocsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateFoodDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateMiscDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateOneHandedMeleeWeaponsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateOthersDoc(refAnalyzer, outputPath))
		return false;
	if(!CreatePotionsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateRingsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateRunesDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateScrollsDoc(refAnalyzer, outputPath))
		return false;
	if(!CreateTwoHandedMeleeWeaponsDoc(refAnalyzer, outputPath))
		return false;
	
	return true;
}