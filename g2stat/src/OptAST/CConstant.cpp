//Class Header
#include "CConstant.h"
//Local
#include "AValueExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CConstant::CConstant(const CType &refType, const SJCLib::CString &refName, AValueExpression *pValue, const SJCLib::CWString &refFileName, uint32 lineNumber) : AGlobal(refName, refFileName, lineNumber)
{
	this->type = refType;
	this->pValue = pValue;
}

//Destructor
CConstant::~CConstant()
{
	delete this->pValue;
}

//Public methods
void CConstant::CollectSymbols(CCompiler &refCompiler)
{
	this->pValue->CollectSymbols(refCompiler);
}