//Local
#include "AInstance.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AInstance::AInstance(const CString &refClassName, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->className = refClassName;
}