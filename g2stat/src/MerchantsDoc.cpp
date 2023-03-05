//Libs
#include <SJCLib.h>
//Local
#include "CAnalyzer.h"
#include "CGame.h"
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

bool CreateMerchantsDoc(CAnalyzer &refAnalyzer, CString outputPath)
{
	const CNPC *pNPC;
	CFileOutputStream file;

	CTextWriter &refWriter = CTextWriter(file);
	
	if(!file.Open(outputPath + "\\merchants.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\merchants.htm'");
	
	WriteHTMLHead("Merchants", file, "../");
	WriteHTMLSortableTableHeadBegin(file);
	WriteHTMLTableHeadCol(file, "Name");
	WriteHTMLTableHeadCol(file, "Instance name");
	WriteHTMLTableHeadEnd(file);

	foreach(it, refAnalyzer.GetMerchants())
	{
		pNPC = it.GetKey()->GetNPC();
		
		//name
		file << "<tr>";
		file << "<td>";
		refWriter.WriteUTF8(pNPC->GetName());
		file << "</td>";

		//instance name
		file << "<td><a href=\"instances/" << pNPC->GetInstanceName() << ".htm\">" << pNPC->GetInstanceName() << "</a></td></tr>";
	}

	WriteHTMLTableFoot(file);
	WriteHTMLFoot(file);
	
	return true;
}