//Class Header
#include "CTextNode.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CTextNode::CTextNode(const CString &refString, uint32 lineNumber) : ANode(CWString(), lineNumber)
{
	this->string = refString;
}