//Class Header
#include "AConstant.h"
//Local
#include "../CType.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AConstant::AConstant(CType *pType, const CString &refName, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->pType = pType;
	this->name = refName;
}

//Destructor
AConstant::~AConstant()
{
	delete this->pType;
}