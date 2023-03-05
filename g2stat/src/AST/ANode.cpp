//Class Header
#include "ANode.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
ANode::ANode(const CWString &refFileName, uint32 lineNumber)
{
	this->fileName = refFileName;
	this->lineNumber = lineNumber;
}