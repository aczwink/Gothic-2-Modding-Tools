//Class Header
#include "CIdentifierList.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CIdentifierList::CIdentifierList(const CString &refIdentifier) : ANode(CWString(), 0)
{
	this->identifiers.InsertTail(refIdentifier);
}

//Destructor
CIdentifierList::~CIdentifierList()
{
	//needs to be there because of virtual destructor
}