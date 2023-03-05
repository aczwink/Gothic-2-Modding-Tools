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

bool CreateAmuletsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	uint32 counter;
	const CItem *pItem;
	const CInstance *pInstance;
	CItemInfo *pItemInfo;
	CFileOutputStream file;
	
	CTextWriter &refWriter = CTextWriter(file);

	counter = 0;
	
	if(!file.Open(outputPath + "\\amulets.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\amulets.htm'");
	
	WriteHTMLHead("Amulets", file, "../");
	WriteHTMLSortableTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Description");
	WriteHTMLTableHeadCol(file, "Instance name");
	WriteHTMLTableHeadCol(file, "to Strength", "intSort");
	WriteHTMLTableHeadCol(file, "to Dexterity", "intSort");
	WriteHTMLTableHeadCol(file, "to Life", "intSort");
	WriteHTMLTableHeadCol(file, "to Mana", "intSort");
	WriteHTMLTableHeadCol(file, "Protection against Edge", "intSort");
	WriteHTMLTableHeadCol(file, "Protection against Point", "intSort");
	WriteHTMLTableHeadCol(file, "Protection against Magic", "intSort");
	WriteHTMLTableHeadCol(file, "Protection against Fire", "intSort");
	WriteHTMLTableHeadCol(file, "Receivable", "intSort");
	WriteHTMLTableHeadCol(file, "Value in Gold", "intSort");
	WriteHTMLTableHeadEnd(file);

	foreach(it, refAnalyzer.GetItemInfos())
	{
		pItemInfo = it.GetValue();
		pInstance = pItemInfo->GetInstance();
		pItem = pItemInfo->GetItem();
		
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MAGIC) && (pItem->GetFlags() & ITEM_FLAGS_AMULET))
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
			
			//to strength
			file << "<td>";
			if(pItemInfo->GetStrengthChange())
				file << pItemInfo->GetStrengthChange();
			file << "</td>";

			//to dexterity
			file << "<td>";
			if(pItemInfo->GetDexterityChange())
				file << pItemInfo->GetDexterityChange();
			file << "</td>";

			//to life
			file << "<td>";
			if(pItemInfo->GetMaxLifePointsChange())
				file << pItemInfo->GetMaxLifePointsChange();
			file << "</td>";

			//to mana
			file << "<td>";
			if(pItemInfo->GetMaxManaPointsChange())
				file << pItemInfo->GetMaxManaPointsChange();
			file << "</td>";

			//protection against edge
			file << "<td>";
			if(pItemInfo->GetProtectionAgainstEdgeChange())
				file << pItemInfo->GetProtectionAgainstEdgeChange();
			file << "</td>";

			//protection against point
			file << "<td>";
			if(pItemInfo->GetProtectionAgainstPointChange())
				file << pItemInfo->GetProtectionAgainstPointChange();
			file << "</td>";

			//protection against magic
			file << "<td>";
			if(pItemInfo->GetProtectionAgainstMagicChange())
				file << pItemInfo->GetProtectionAgainstMagicChange();
			file << "</td>";

			//protection against fire
			file << "<td>";
			if(pItemInfo->GetProtectionAgainstFireChange())
				file << pItemInfo->GetProtectionAgainstFireChange();
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