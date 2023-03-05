//Class Header
#include "CDeclarationStatement.h"
//Local
#include "../OptAST/CLocalVariable.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CDeclarationStatement::CDeclarationStatement(CLocalVariable *pVariable)
{
	this->pVariable = pVariable;
}

//Destructor
CDeclarationStatement::~CDeclarationStatement()
{
	delete this->pVariable;
}

//Public methods
void CDeclarationStatement::CollectSymbols(CCompiler &refCompiler)
{
	this->pVariable->CollectSymbols(refCompiler);
}

void CDeclarationStatement::Compile(CProgramBuffer &refProgram) const
{
}