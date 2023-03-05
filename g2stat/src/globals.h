/*//SJCLib
#include <SJCLib.h>
//Local
#include "CDaedalusCompiler.h"
#include "CDaedalusProgram.h"
#include "Daedalus.h"

//Structs
struct SAST
{
	CString name;
	SGlobals *pAST;
};

//Global Variables
extern CFiniteSet<CString> g_parsedFiles;
extern CArray<SAST> g_ASTs;
extern CDaedalusCompiler g_compiler;
extern CDaedalusProgram g_program;*/
//Local
#include "CCompiler.h"
#include "CInfo.h"
#include "CItem.h"
#include "CNPC.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

struct SNPCInstanceInfo
{
	CNPC *pNPC;
	CInstance *pInstance;
};

//Global Variables
extern CArray<SNPCInstanceInfo> g_npcInstances;
extern CArray<CInfo *> g_infoInstances;