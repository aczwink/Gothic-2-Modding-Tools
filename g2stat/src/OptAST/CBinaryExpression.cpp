//Class Header
#include "CBinaryExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructor
CBinaryExpression::CBinaryExpression(EOpcode op, AExpression *pLeft, AExpression *pRight)
{
	this->op = op;
	this->pLeft = pLeft;
	this->pRight = pRight;
}

//Destructor
CBinaryExpression::~CBinaryExpression()
{
	delete this->pLeft;
	delete this->pRight;
}

//Public methods
void CBinaryExpression::CollectSymbols(CCompiler &refCompiler)
{
	this->pLeft->CollectSymbols(refCompiler);
	this->pRight->CollectSymbols(refCompiler);
}

void CBinaryExpression::Compile(CProgramBuffer &refProgram) const
{
	this->pRight->Compile(refProgram);
	this->pLeft->Compile(refProgram);
	refProgram.WriteByte(this->op);
}