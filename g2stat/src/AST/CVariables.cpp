//Class Header
#include "CVariables.h"
//Local
#include "AVariable.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CVariables::CVariables() : ANode(CWString(), 0)
{
}

//Destructor
CVariables::~CVariables()
{
	for(AVariable *pVariable : this->variables)
		delete pVariable;
}

//Public methods
void CVariables::AddVariableAfter(AVariable *pNew, AVariable *pAfter)
{
	uint32 index;
	
	index = UINT32_MAX;
	foreach(it, this->variables)
	{
		if(*it == pAfter)
		{
			index = it.GetIndex();
			break;
		}
	}
	
	this->variables.InsertAfter(index, pNew);
}

void CVariables::Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass)
{
	for(AVariable *pVariable : this->variables)
	{
		pVariable->Process(refCompiler, pClass, pOptClass);
	}
}

void CVariables::RemoveVariable(AVariable *pVariable)
{
	foreach(it, this->variables)
	{
		if(*it == pVariable)
		{
			it.Delete();
			break;
		}
	}
}