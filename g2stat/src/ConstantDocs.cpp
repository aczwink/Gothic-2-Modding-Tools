/*//SJCLib
#include <SJCLib.h>
//Local
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
#include "CCompilePreprocessor.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

bool CreateConstantsDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	uint32 nEncodedBytes;
	SGlobals *pGlobal;
	SConstantInfo *pInfo;
	CFileOutputStream file;
	byte utf8encoded[UTF8_BUFFERSIZE];
	
	if(!file.Open(outputPath + "\\constants.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\constants.htm'");

	stdOut << "Creating 'Constants' file." << endl;

	WriteHTMLHead("Constants", file);
	
	file << "<table id=\"sortableTable\">"
		<< "<thead><tr>"
		<< "<th>Type</th><th>Name</th><th>Value</th><th>Defined in</th><th>Referenced</th>"
		<< "</tr></thead>";
	file << "<tbody>";

	for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		if(pGlobal->type != GLOBALTYPE_CONSTANT)
			continue;
		
		SConstant &refConstant = *pGlobal->value.pConstant;

		//pInfo = refCompilePreproc.GetConstantInfo(*refConstant.pName);
		pInfo = NULL;
		ASSERT(0);
		
		file << "<tr>";
		
		//Type
		file << "<td>" << ToString(*refConstant.pType) << "</td>";
		
		//Name
		nEncodedBytes = UTF8Encode(*refConstant.pName, utf8encoded);
		file << "<td>";
		file.WriteBytes(utf8encoded, nEncodedBytes);
		file << "</td>";
		
		//Value
		nEncodedBytes = UTF8Encode(ValueToString(refConstant), utf8encoded);
		file << "<td>";
		file.WriteBytes(utf8encoded, nEncodedBytes);
		file << "</td>";
		//Defined in
		file << "<td>" << *refConstant.pFilename << ":" << refConstant.lineNumber << "</td>";
		//Referenced
		file << "<td" << (pInfo->nReferences == 0 ? " class=\"warning\"" : "") << ">" << pInfo->nReferences << "</td>";
		
		file << "</tr>";
	}
	
	file << "</tbody>";
	file << "</table>";
	file << "<script type=\"text/javascript\">window.onload = function(){ MakeSortable(document.getElementById(\"sortableTable\")); };</script>";
	
	file << "</body>"
		<< "</html>";
	
	return true;
}*/