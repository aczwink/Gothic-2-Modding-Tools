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

bool CreateDocsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	uint32 counter;
	const CItem *pItem;
	const CInstance *pInstance;
	CItemInfo *pItemInfo;
	CFileOutputStream file;
	
	CTextWriter &refWriter = CTextWriter(file);

	counter = 0;
	
	if(!file.Open(outputPath + "\\docs.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\docs.htm'");
	
	WriteHTMLHead("Documents", file, "../");

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
		
		if((pItem->GetMainFlag() & ITEM_MAINFLAG_DOCS))
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