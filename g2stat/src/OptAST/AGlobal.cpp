//Class Header
#include "AGlobal.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
AGlobal::AGlobal(const CString &refName, const CWString &refFileName, uint32 lineNumber) : ANode(refFileName, lineNumber)
{
	this->name = refName;
}