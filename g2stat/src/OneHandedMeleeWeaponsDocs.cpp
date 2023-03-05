//Main Header
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

bool CreateOneHandedMeleeWeaponsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	uint32 counter;
	const CItem *pItem;
	const CInstance *pInstance;
	CItemInfo *pItemInfo;
	CFileOutputStream file;
	
	CTextWriter &refWriter = CTextWriter(file);

	counter = 0;
	
	if(!file.Open(outputPath + "\\one-handed melee weapons.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\one-handed melee weapons.htm'");
	
	WriteHTMLHead("One-handed melee weapons", file, "../");

	WriteHTMLSortableTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Description");
	WriteHTMLTableHeadCol(file, "Instance name");
	WriteHTMLTableHeadCol(file, "Damage", "intSort");
	WriteHTMLTableHeadCol(file, "Range", "intSort");
	WriteHTMLTableHeadCol(file, "Required Strength", "intSort");
	WriteHTMLTableHeadCol(file, "Required Dexterity", "intSort");
	WriteHTMLTableHeadCol(file, "to one-handed melee weapons talent", "intSort");
	WriteHTMLTableHeadCol(file, "Receivable", "intSort");
	WriteHTMLTableHeadCol(file, "Value in Gold", "intSort");
	WriteHTMLTableHeadEnd(file);
	
	foreach(it, refAnalyzer.GetItemInfos())
	{
		pItemInfo = it.GetValue();
		pInstance = pItemInfo->GetInstance();
		pItem = pItemInfo->GetItem();
		
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MELEE) && (pItem->GetFlags() & (ITEM_FLAGS_SWORD | ITEM_FLAGS_AXE)))
		{
			file << "<tr>";
			
			//Name
			file << "<td>";
			refWriter.WriteUTF8(pItem->GetName());
			file << "</td>";

			//Description
			file << "<td>";
			refWriter.WriteUTF8(pItem->GetDescription());
			file << "</td>";

			//Instance name
			file << "<td><a href=\"instances/" << pInstance->GetName() << ".htm\">" << pInstance->GetName() << "</a></td>";
			
			//damage
			file << "<td>";
			if(pItem->GetDamageTotal())
				file << pItem->GetDamageTotal();
			file << "</td>";

			//range
			file << "<td>";
			if(pItem->GetRange())
				file << pItem->GetRange();
			file << "</td>";

			//required strength
			file << "<td>";
			if(pItemInfo->GetRequiredStrength())
				file << pItemInfo->GetRequiredStrength();
			file << "</td>";

			//required dexterity
			file << "<td>";
			if(pItemInfo->GetRequiredDexterity())
				file << pItemInfo->GetRequiredDexterity();
			file << "</td>";

			//to one-handed melee weapons talent
			file << "<td>";
			if(pItemInfo->GetOneHandedMeleeWeaponsTalentChange())
				file << pItemInfo->GetOneHandedMeleeWeaponsTalentChange();
			file << "</td>";
			
			//receivable
			file << "<td>" << pItemInfo->GetReceivabilityCount() << "</td>";

			//value in gold
			file << "<td>" << pItem->GetValue() << "</td>";
			
			file << "</tr>";

			counter++;
		}
	}
	WriteHTMLTableFoot(file);

	file << "<p>Number of items: " << counter << "</p>";
	
	WriteHTMLFoot(file);
	
	return true;
}