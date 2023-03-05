//Main Header
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
using namespace Daedalus;
//Definitions
#undef GetClassInfo

/*bool CreatePrototypesDoc(CString outputPath, SPrototype &refPrototype, SPrototypeInfo &refInfo, SClass &refClass)
{
	SVariables *pVariables;
	CFileOutputStream file;
	
	if(!file.Open(outputPath + "\\prototypes\\" + *refPrototype.pName + ".htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\prototypes\\" + *refPrototype.pName + ".htm'");

	WriteHTMLHead(*refPrototype.pName, file, "../");
	
	file << "<table>";
	//Print defined in
	file << "<tr><td>Defined in:</td><td>" << *refPrototype.pFileName << ":" << refPrototype.lineNumber << "</td></tr>";
	//Print the number of references
	file << "<tr><td>Referenced:</td><td>" << refInfo.nReferences << "</td></tr>";
	file << "</table>";
	
	file << "<h2>Variables</h2>";
	file << "<table>";
	file << "<tr><th>Type</th><th>Name</th></tr>";

	for(pVariables = refClass.pVariables; pVariables; pVariables = pVariables->pNext)
	{
		file << "<tr>";
		file << "<td>" << ToString(*pVariables->pVariable->pType) << "</td><td>" << *pVariables->pVariable->pName << "</td>";
		file << "</tr>";
	}

	file << "</table>";
	
	file << "</body>"
		<< "</html>";
	
	return true;
}*/

/*bool CreatePrototypesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	SGlobals *pGlobal;
	CFileOutputStream file;
	
	stdOut << "Creating 'Prototypes' files." << endl;
	
	if(!CreateDirectory((outputPath + "\\prototypes").GetC_Str(), NULL))
		ERRORMSG("'prototypes' folder in Output folder couldn't be created.");
	
	if(!file.Open(outputPath + "\\prototypes.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\prototypes.htm'");
	
	WriteHTMLHead("Prototypes", file);
	
	file << "<table id=\"sortableTable\"><thead>"
		<< "<tr>"
		<< "<th>Name</th><th>Class name</th><th>Defined in</th><th>Referenced</th>"
		<< "</tr></thead><tbody>";
	
	for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		if(pGlobal->type != GLOBALTYPE_PROTOTYPE)
			continue;

		SPrototype &refPrototype = *pGlobal->value.pPrototype;
		SPrototypeInfo &refInfo = *refCompilePreproc.GetPrototypeInfo(*refPrototype.pName);
		
		/*
		if(!CreatePrototypesDoc(outputPath, refPrototype, refInfo, *refClassInfo.pClass))
		{
			ERRORMSG("Couldn't create prototypes documentation for prototype '" + *refPrototype.pName + "'.");
		}
		* /
		
		file << "<tr>";

		//Name
		file << "<td>" << *refPrototype.pName << "</td>";
		//Class Name
		file << "<td><a href=\"classes/" << *refPrototype.pClassName << ".htm\">" << *refPrototype.pClassName << "</a></td>";
		//Defined in
		file << "<td>" << *refPrototype.pFileName << ":" << refPrototype.lineNumber << "</td>";
		//Referenced
		file << "<td" << (refInfo.nReferences == 0 ? " class=\"warning\")" : "") << ">" << refInfo.nReferences << "</td>";
		
		file << "</tr>";
	}
	
	file << "</tbody>";
	file << "</table>";
	file << "<script type=\"text/javascript\">window.onload = function(){ MakeSortable(document.getElementById(\"sortableTable\")); };</script>";

	file << "</body>"
		<< "</html>";

	return true;
}*/