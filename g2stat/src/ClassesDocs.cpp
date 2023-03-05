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
//Definitions
#undef GetClassInfo

//Prototypes
bool CreateClassesDoc(CString outputPath, SClass &refClass, SClassInfo &refClassInfo);

bool CreateClassesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc)
{
	SGlobals *pGlobal;
	CFileOutputStream file;
	
	if(!CreateDirectory((outputPath + "\\classes").GetC_Str(), NULL))
		ERRORMSG("'classes' folder in Output folder couldn't be created.");
	
	if(!file.Open(outputPath + "\\classes.htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\classes.htm'");

	stdOut << "Creating 'Classes' files." << endl;
	
	WriteHTMLHead("Classes", file);
	
	file << "<table id=\"sortableTable\"><thead>"
		<< "<tr>"
		<< "<th>Name</th><th>Defined in</th><th>Referenced</th>"
		<< "</tr></thead><tbody>";

	for(pGlobal = refCompilePreproc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		if(pGlobal->type != GLOBALTYPE_CLASS)
			continue;

		SClass &refClass = *pGlobal->value.pClass;
		SClassInfo &refClassInfo = *refCompilePreproc.GetClassInfo(*refClass.pName);
		
		if(!CreateClassesDoc(outputPath, refClass, refClassInfo))
			ERRORMSG("Couldn't create classes documentation for class '" + *refClass.pName + "'.");
		
		file << "<tr>";
		
		file << "<td><a href=\"classes/" << *refClass.pName << ".htm\">" << *refClass.pName << "</a></td>";
		//Defined in
		file << "<td>" << *refClass.pFilename << ":" << refClass.lineNumber << "</td>";
		//Referenced
		file << "<td" << (refClassInfo.nReferences == 0 ? " class=\"warning\")" : "") << ">" << refClassInfo.nReferences << "</td>";
		
		file << "</tr>";
	}

	file << "</tbody>";
	file << "</table>";
	file << "<script type=\"text/javascript\">window.onload = function(){ MakeSortable(document.getElementById(\"sortableTable\")); };</script>";

	file << "</body>"
		<< "</html>";

	return true;
}

bool CreateClassesDoc(CString outputPath, SClass &refClass, SClassInfo &refClassInfo)
{
	SVariables *pVariables;
	CFileOutputStream file;
	
	if(!file.Open(outputPath + "\\classes\\" + *refClass.pName + ".htm"))
		ERRORMSG("Couldn't open file '" + outputPath + "\\classes\\" + *refClass.pName + ".htm'");

	WriteHTMLHead(*refClass.pName, file, "../");

	file << "<h1>" << *refClass.pName << "</h1>";

	file << "<table>";
	//Print defined in
	file << "<tr><td>Defined in:</td><td>" << *refClass.pFilename << ":" << refClass.lineNumber << "</td></tr>";
	//Print the number of references
	file << "<tr><td>Referenced:</td><td>" << refClassInfo.nReferences << "</td></tr>";
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