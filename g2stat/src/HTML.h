//SJCLib
#include <SJCLib.h>
//Namespaces
using namespace SJCLib;

void WriteHTMLHead(CString title, AOutputStream &refOutputStream, CString pathToRoot = "");
void WriteHTMLTableHeadBegin(AOutputStream &refOutputStream);
void WriteHTMLSortableTableHeadBegin(AOutputStream &refOutputStream);
void WriteHTMLTableHeadCol(AOutputStream &refOutputStream, const CString &refTitle);
void WriteHTMLTableHeadCol(AOutputStream &refOutputStream, const CString &refTitle, const CString &refClass);
void WriteHTMLTableHeadEnd(AOutputStream &refOutputStream);
void WriteHTMLTableFoot(AOutputStream &refOutputStream);
void WriteHTMLFoot(AOutputStream &refOutputStream);