//Class Header
#include "AExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
AExpression::AExpression(const CWString &refFileName, uint32 lineNumber) : ANode(refFileName, lineNumber)
{
}