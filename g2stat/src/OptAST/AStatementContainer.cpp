//Class Header
#include "AStatementContainer.h"
//Namespaces
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Destructor
AStatementContainer::~AStatementContainer()
{
	for(AStatement *pStatement : this->statements)
	{
		delete pStatement;
	}
}