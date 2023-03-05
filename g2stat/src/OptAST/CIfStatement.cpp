//Class Header
#include "CIfStatement.h"
//Local
#include "CIfAlternative.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Destructor
CIfStatement::~CIfStatement()
{
	for(CIfAlternative *pAlternative : this->alternatives)
		delete pAlternative;
}

//Public methods
void CIfStatement::CollectSymbols(CCompiler &refCompiler)
{
	for(CIfAlternative *pAlternative : this->alternatives)
		pAlternative->CollectSymbols(refCompiler);
}

void CIfStatement::Compile(CProgramBuffer &refProgram) const
{
	CArray<uint32> endOfChainInsertOffsets;
	
	for(CIfAlternative *pAlternative : this->alternatives)
		pAlternative->Compile(refProgram, endOfChainInsertOffsets);

	//set end of chain offsets
	foreach(it, endOfChainInsertOffsets)
		refProgram.WriteAt(it.GetValue(), refProgram.GetCurrentOffset());
}