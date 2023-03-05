//Main Header
#include "CreateDocs.h"
//Global
#include <Windows.h>
//Local
#include "Definitions.h"
#include "HTML.h"

//Prototypes
bool CreateMerchantsDoc(CAnalyzer &refAnalyzer, CString outputPath);

void PrintItemLink(const CItem *pItem, AOutputStream &refOutput, CTextWriter &refWriter)
{
	if(!pItem)
		return;
	
	refOutput << "<a href=\"../../items/instances/" << pItem->GetInstanceName() << ".htm\">";
	refWriter.WriteUTF8(pItem->GetName());
	refOutput << "</a>";
}

void PrintKeyValuePair(const CString &refKey, const CString &refValue, AOutputStream &refOutput)
{
	refOutput << "<tr>";
	refOutput << "<td>" << refKey << "</td>";
	refOutput << "<td>" << refValue << "</td>";
	refOutput << "</tr>";
}

void PrintItem(const CString &refKey, const CItem *pItem, AOutputStream &refOutput, CTextWriter &refWriter)
{
	refOutput << "<tr>";
	refOutput << "<td>" << refKey << "</td>";
	refOutput << "<td>";
	if(pItem)
		PrintItemLink(pItem, refOutput, refWriter);
	refOutput << "</td>";
	refOutput << "</tr>";
}

bool CreateNPCDoc(CNPCInfo *pInfo, const CString &refPath)
{
	const CNPC *pNPC;
	const CInstance *pInstance;
	CFileOutputStream file;
	
	CTextWriter &refWriter = CTextWriter(file);
	
	pNPC = pInfo->GetNPC();
	pInstance = pInfo->GetInstance();
	
	if(!file.Open(refPath + '\\' + pNPC->GetInstanceName() + ".htm"))
		ERRORMSG("couldn't create output for item '" + pNPC->GetInstanceName() + "'");
	
	WriteHTMLHead(pNPC->GetInstanceName(), file, "../../");
	
	file << "<h1>" << pNPC->GetInstanceName() << "</h1>";
	
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
	refWriter.WriteUTF8(pNPC->GetName());
	file << "</td>";
	file << "</tr>";

	//level
	file << "<tr>";
	file << "<td>Level</td>";
	file << "<td>" << pNPC->GetLevel() << "</td>";
	file << "</tr>";

	//strength
	file << "<tr>";
	file << "<td>Strength</td>";
	file << "<td>" << pNPC->GetStrength() << "</td>";
	file << "</tr>";

	//dexterity
	file << "<tr>";
	file << "<td>Dexterity</td>";
	file << "<td>" << pNPC->GetDexterity() << "</td>";
	file << "</tr>";

	//life
	file << "<tr>";
	file << "<td>Lifepoints</td>";
	file << "<td>" << pNPC->GetMaxLifePoints() << "</td>";
	file << "</tr>";

	//mana
	file << "<tr>";
	file << "<td>Manapoints</td>";
	file << "<td>" << pNPC->GetMaxManaPoints() << "</td>";
	file << "</tr>";

	WriteHTMLTableFoot(file);

	//---------------
	//equipment
	//---------------
	file << "<h3>Equipment</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Body part");
	WriteHTMLTableHeadCol(file, "Item");
	WriteHTMLTableHeadEnd(file);
	
	//melee weapon
	file << "<tr>";
	file << "<td>Melee weapon</td>";
	file << "<td>";
	if(pNPC->GetMeleeWeapon())
		PrintItemLink(pNPC->GetMeleeWeapon(), file, refWriter);
	file << "</td>";
	file << "</tr>";
	
	PrintItem("Range weapon", pNPC->GetRangedWeapon(), file, refWriter);

	//inventory
	file << "<tr>";
	file << "<td>Inventory</td>";
	file << "<td>";
	foreach(it, pNPC->GetInventory())
	{
		if(it.GetValue()->GetMultiplicity() > 1)
			file << it.GetValue()->GetMultiplicity() << "x ";
		PrintItemLink(it.GetValue(), file, refWriter);
		file << "<br />";
	}
	file << "</td>";
	file << "</tr>";

	WriteHTMLTableFoot(file);

	//---------------
	//items for sale
	//---------------
	file << "<h3>Items for sale</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Chapter");
	WriteHTMLTableHeadCol(file, "Items");
	WriteHTMLTableHeadEnd(file);

	foreach(it, pInfo->GetItemsForTrade())
	{
		file << "<tr>";
		file << "<td>Chapter " << it.GetKey() << "</td>";
		file << "<td>";
		foreach(it2, it.GetValue())
		{
			PrintItemLink(it2.GetValue(), file, refWriter);
			if(it2.GetValue()->GetMultiplicity() > 1)
			{
				file << " (" << it2.GetValue()->GetMultiplicity() << ')';
			}
			file << "<br />";
		}
		file << "</td>";
		file << "</tr>";
	}

	WriteHTMLTableFoot(file);

	//---------------
	//location
	//---------------
	file << "<h3>Location</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "World");
	WriteHTMLTableHeadCol(file, "Count");
	WriteHTMLTableHeadEnd(file);
	
	foreach(it, pInfo->GetInstances())
	{
		file << "<tr>";
		file << "<td>" << it.GetKey()->GetName() << "</td>";
		file << "<td>" << it.GetValue().GetNoOfElements() << "</td>";
		file << "</tr>";
	}
	
	WriteHTMLTableFoot(file);
	
	//---------------
	//additional info
	//---------------
	file << "<h3>Additional info</h3>";
	WriteHTMLTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Value");
	WriteHTMLTableHeadEnd(file);
	//defined in
	file << "<tr>";
	file << "<td>Defined in</td>";
	file << "<td>" << pInstance->GetFileName() << ':' << pInstance->GetLineNumber() << "</td>";
	file << "</tr>";

	//referenced
	file << "<tr>";
	file << "<td>Referenced</td>";
	file << "<td>" << pInstance->GetReferenceCount() << "</td>";
	file << "</tr>";

	WriteHTMLTableFoot(file);
	
	WriteHTMLFoot(file);
	
	return true;
}

bool CreateNPCsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	CFileOutputStream file;
	CString instancesPath;

	stdOut << "Creating 'NPC's' files." << endl;
	
	if(!CreateDirectory((outputPath + "\\npcs").GetC_Str(), NULL))
		ERRORMSG("'npcs' folder in Output folder couldn't be created.");
	outputPath += "\\npcs";
	instancesPath = outputPath + "\\instances";
	if(!CreateDirectory((instancesPath).GetC_Str(), NULL))
		ERRORMSG("'instances' folder in Output folder couldn't be created.");
	
	foreach(it, refAnalyzer.GetNPCInfos())
	{
		if(!CreateNPCDoc(it.GetValue(), instancesPath))
			ERRORMSG("couldn't create item information");
	}

	if(!CreateMerchantsDoc(refAnalyzer, outputPath))
		return false;
	
	return true;
}