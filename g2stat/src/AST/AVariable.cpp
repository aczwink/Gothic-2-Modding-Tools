//Class Header
#include "AVariable.h"
//Local
#include "../CType.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AVariable::AVariable(CType *pType, const CWString &refFileName, uint32 lineNumber) : AGlobal(refFileName, lineNumber)
{
	this->pType = pType;
}

//Destructor
AVariable::~AVariable()
{
	delete this->pType;
}