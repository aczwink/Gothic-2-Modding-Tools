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

bool CreateOthersDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	uint32 counter;
	const CItem *pItem;
	const CInstance *pInstance;
	CItemInfo *pItemInfo;
	CFileOutputStream file;

	CTextWriter &refWriter = CTextWriter(file);

	counter = 0;

	if(!file.Open(outputPath + "\\others.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\others.htm'");

	WriteHTMLHead("Items that don't fit any category (potentially programming errors)", file, "../");

	WriteHTMLSortableTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Description");
	WriteHTMLTableHeadCol(file, "Instance name");
	WriteHTMLTableHeadCol(file, "Receivable", "intSort");
	WriteHTMLTableHeadCol(file, "Value in Gold", "intSort");
	WriteHTMLTableHeadEnd(file);

	foreach(it, refAnalyzer.GetItemInfos())
	{
		pItemInfo = it.GetValue();
		pInstance = pItemInfo->GetInstance();
		pItem = pItemInfo->GetItem();

		//ignore all other filters
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MAGIC) && (pItem->GetFlags() & ITEM_FLAGS_AMULET))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_ARMOR))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MAGIC) && (pItem->GetFlags() & ITEM_FLAGS_BELTS))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_RANGED) && (pItem->GetFlags() & ITEM_FLAGS_BOW))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_RANGED) && (pItem->GetFlags() & ITEM_FLAGS_CROSSBOW))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_DOCS))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_FOOD))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MISC))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MELEE) && (pItem->GetFlags() & (ITEM_FLAGS_SWORD | ITEM_FLAGS_AXE)))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_POTIONS))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MAGIC) && (pItem->GetFlags() & ITEM_FLAGS_RINGS))
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_SPELL) && !(pItem->GetFlags() & ITEM_FLAGS_STACKABLE)) //runes are not stackable
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_SPELL) && (pItem->GetFlags() & ITEM_FLAGS_STACKABLE)) //runes are not stackable
			continue;
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_MELEE) && (pItem->GetFlags() & (ITEM_FLAGS_2HD_SWORD | ITEM_FLAGS_2HD_AXE)))
			continue;

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

		//receivable
		file << "<td>" << pItemInfo->GetReceivabilityCount() << "</td>";

		//value in gold
		file << "<td>" << pItem->GetValue() << "</td>";

		file << "</tr>";

		counter++;
	}
	WriteHTMLTableFoot(file);

	file << "<p>Number of items: " << counter << "</p>";

	WriteHTMLFoot(file);

	return true;
}