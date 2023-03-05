//Class Header
#include "CGlobalVariable.h"
//Local
#include "../CCompiler.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CGlobalVariable::CGlobalVariable(const CType &refType, const CString &refName) : AGlobal(refName, CWString(), 0)
{
	this->type = refType;
}

//Public methods
void CGlobalVariable::CollectSymbols(CCompiler &refCompiler)
{
	this->symbolIndex = refCompiler.AddSymbol(this);
}

void CGlobalVariable::WriteSymbol(AOutputStream &refOutputStream) const
{
	this->WriteSymbol(refOutputStream, this->GetName(), 0, this->type.GetNumberOfElements(), this->type.GetType(), 0, 0, UINT32_MAX);
}