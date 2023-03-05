//Class Header
#include "AValueExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Public methods
void AValueExpression::CollectSymbols(CCompiler &refCompiler)
{
	//usually leafs don't need to be written as symbols
}