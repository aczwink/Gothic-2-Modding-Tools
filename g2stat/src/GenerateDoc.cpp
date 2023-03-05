//SJC
#include <SJCLib.h>
#include <SJCWinLib.h>
//Local
#include "CAnalyzer.h"
#include "CCompiler.h"
#include "CDaedalusCallback.h"
#include "CDaedalusCompiler.h"
#include "CGame.h"
#include "CreateDocs.h"
#include "Definitions.h"
#include "globals.h"
#include "HTML.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
//Definitions
#undef ERRORMSG
#define ERRORMSG(msg) {stdErr << msg << endl; Cleanup(); return false;} //we need to call cleanup here

void Cleanup()
{
	foreach(it, g_npcInstances)
	{
		delete it.GetValue().pNPC;
	}
	g_npcInstances.Release();

	foreach(it, g_infoInstances)
	{
		delete it.GetValue();
	}
	g_infoInstances.Release();
}

bool CreateStyleFile(CString outputPath)
{
	CFileOutputStream styleFile;
	
	if(styleFile.Open(outputPath + "\\style.css"))
	{
		styleFile << "table{"
			<< "width:100%; padding:5px; border-collapse:collapse;"
			<< "}";
		styleFile << "th{"
			<< "cursor:pointer;"
			<< "}";
		styleFile << "th, td{"
			<< "padding:5px;"
			<< "}";
		styleFile << "table, td, th{"
			<< "border:1px solid #000;"
			<< "}";
		styleFile << "table.tableborder_only{"
			<< "border:1px solid #000"
			<< "}";
		styleFile << "table.tableborder_only th, table.tableborder_only td{"
			<< "border:none"
			<< "}";
		styleFile << ".warning{"
			<< "font-weight:bold; color:#FF7F00;"
			<< "}";
		styleFile << ".txtright{"
			<< "text-align:right;"
			<< "}";

		return true;
	}
	
	return false;
}

bool CreateJSSortFile(CString outputPath)
{
	CFileOutputStream sortFile;
	
	if(!sortFile.Open(outputPath + "\\sort.js"))
	{
		ERRORMSG("Couldn't create sort file");
	}
	sortFile << "function SortTable(table, col, asc, intSort)"
		<< "{"
		<< "var tb, tr;"
		<< "tb = table.tBodies[0];"
		<< "tr = Array.prototype.slice.call(tb.rows, 0);"
		<< "asc = asc ? -1 : 1;"
		<< "if(intSort){"
		<< "tr = tr.sort("
		<< "function(a, b)"
		<< "{"
		<< "var c,d;"
		<< "c = parseInt(a.cells[col].textContent.trim());"
		<< "d = parseInt(b.cells[col].textContent.trim());"
		<< "if(isNaN(c)) c = 0;"
		<< "if(isNaN(d)) d = 0;"
		<< "return asc * (c - d);"
		<< "}"
		<< ");"
		<< "}else{"
		<< "tr = tr.sort("
		<< "function(a, b)"
		<< "{"
		<< "return asc * (a.cells[col].textContent.trim().localeCompare(b.cells[col].textContent.trim()));"
		<< "}"
		<< ");"
		<< "}"
		<< "for(var i = 0; i < tr.length; i++)"
		<< "tb.appendChild(tr[i]);"
		<< "}"
		<< "function FireSort(table, th, idx)"
		<< "{"
		<< "var asc = true;"
		<< "th[idx].addEventListener(\"click\", function(){ SortTable(table, idx, (asc = !asc), th[idx].className == 'intSort'); });"
		<< "}"
		<< "function MakeSortable(table)"
		<< "{"
		<< "var th, i;"
		<< "th = table.tHead;"
		<< "th = th.rows[0].cells;"
		<< "i = th.length;"
		<< "while(--i >= 0)"
		<< "{"
		<< "FireSort(table, th, i);"
		<< "}"
		<< "}"
		<< "function MakeSortableList(tables)"
		<< "{"
		<< "for(var i = 0; i < tables.length; i++){"
		<< "MakeSortable(tables[i]);"
		<< "}"
		<< "}";

	return true;
}

bool GenerateDoc(CString g2dir, CString modName, CString outputPath)
{
	CFIFOBuffer scriptOutput;
	CFileInputStream input;
	CDaedalusCallback callback;
	
	CGame &refGame = CGame::GetInstance();
	CCompiler &refCompiler = CCompiler(callback);
	//CCompilePreprocessor &refCompilePreproc = CCompilePreprocessor(&callback);
	
	if(!refGame.Init(g2dir, modName))
		ERRORMSG("Failed to initialize the game object");
	
	if(!FileExists(g2dir + "\\_work\\data\\Scripts\\Content\\Gothic.src"))
		ERRORMSG("Gothic.src couldn't be found. Please install G2MDK with Scripts.");
	
	//DEBUG
	/*refGame.StartNewGame();
	CNPC hero("PC_HERO");
	refGame.GetProgram()->SetHero(&hero);
	refGame.GetProgram()->SetSelf(&hero);
	refGame.GetProgram()->ExecuteFunction("Use_Map_AddonWorld");*/
	//DEBUG
	
	//Preprocessing scripts
	if(!refCompiler.Process(g2dir + "\\_work\\data\\Scripts\\Content\\Gothic.src"))
		ERRORMSG("Processing scripts failed...");
	
	//Compiling
	stdOut << "Step three: Compiling..." << endl;
	refCompiler.Compile();
	scriptOutput.SetAllocationIntervalSize(1024 * 1024);
	refCompiler.WriteOutput(scriptOutput);
	stdOut << "Step three: Done compiling" << endl;

	stdOut << endl;

	//Step IV: Analyzing
	stdOut << "Step IV: Analyzing..." << endl;
	refGame.LoadScripts(scriptOutput);
	CAnalyzer &refAnalyzer = CAnalyzer(refCompiler);
	refAnalyzer.Run();
	stdOut << "Step IV Done." << endl;
	
	//Step V
	stdOut << "Step V: Creating output files..." << endl;
	if(FileExists(outputPath))
		ERRORMSG("Output folder already exists");
	
	if(!CreateDirectory(outputPath.GetC_Str(), NULL))
		ERRORMSG("Output folder couldn't be created.");
	if(!CreateItemsDoc(refAnalyzer, outputPath))
		ERRORMSG("Couldn't create items documentation.");
	if(!CreateNPCsDoc(refAnalyzer, outputPath))
		ERRORMSG("Couldn't create npcs documentation.");
	
	/*if(!CreateNPCInstancesDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create 'npc instances' documentation.");
	
	//Create programmers info
	if(!CreateConstantsDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create constants documentation.");
	if(!CreateClassesDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create classes documentation.");
	if(!CreateFunctionsDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create functions documentation.");
	if(!CreateInstancesDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create instances documentation.");
	if(!CreatePrototypesDoc(outputPath, refCompilePreproc))
		ERRORMSG("Couldn't create prototypes documentation.");

	//Create modders info*/
	
	//Create misc files
	if(!CreateStyleFile(outputPath))
		return false;
	if(!CreateJSSortFile(outputPath))
		return false;
	
	stdOut << "Step V Done." << endl;

	//Clean up
	stdOut << "No more steps! Cleaning up..." << endl;
	Cleanup();
	
	return true;
}