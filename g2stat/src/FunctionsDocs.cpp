/*//Main Header
#include "CreateDocs.h"
//SJC Libs
#include <SJCWinLib.h>
//Local
#include "Daedalus.h"
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

bool CreateFunctionsDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	SGlobals *pGlobal;
	SFunctionInfo *pInfo;
	CFileOutputStream file;

	stdOut << "Creating 'Functions' file." << endl;
	
	if(!file.Open(outputPath + "\\functions.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\functions.htm'");
	
	WriteHTMLHead("Functions", file);
	
	file << "<table id=\"sortableTable\"><thead>"
		<< "<tr>"
		<< "<th>Signature</th><th>Defined in</th><th>Referenced</th>"
		<< "</tr></thead><tbody>";
	
	for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		if(pGlobal->type != GLOBALTYPE_FUNCTION)
			continue;

		SFunction &refFunc = *pGlobal->value.pFunction;
		
		pInfo = refCompilePreproc.GetFunctionInfo(*refFunc.pName);
		
		file << "<tr>";
		
		file << "<td>" << ToString(refFunc) << "</td>";
		//Defined in
		file << "<td>" << *refFunc.pFileName << ":" << refFunc.lineNumber << "</td>";
		//Referenced
		file << "<td" << (pInfo->nReferences == 0 ? " class=\"warning\")" : "") << ">" << pInfo->nReferences << "</td>";
		
		file << "</tr>";
	}
	
	file << "</tbody>";
	file << "</table>";
	file << "<script type=\"text/javascript\">window.onload = function(){ MakeSortable(document.getElementById(\"sortableTable\")); };</script>";

	file << "</body>"
		<< "</html>";

	return true;
}*/