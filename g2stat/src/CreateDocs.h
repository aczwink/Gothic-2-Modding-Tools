//SJCLib
#include <SJCLib.h>
//Local
#include "CAnalyzer.h"
#include "CCompiler.h"
#include "CItem.h"
#include "Daedalus.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

/*bool CreateClassesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);
bool CreateConstantsDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);
bool CreateFunctionsDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);
bool CreateInstancesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);*/
bool CreateItemsDoc(CAnalyzer &refAnalyzer, CString outputPath);
//bool CreateNPCInstancesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);*/
bool CreateNPCsDoc(CAnalyzer &refAnalyzer, CString outputPath);
/*bool CreatePrototypesDoc(CString outputPath, CCompilePreprocessor &refCompilePreproc);
void PrintLink(const CItem *pItem, AOutputStream &refOutput, CString path = "");*/