//Class Header
#include "CArrayIndex.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CIntExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CArrayIndex::CArrayIndex(uint32 index, const CWString &refFileName, uint32 lineNumber) : ANode(refFileName, lineNumber)
{
	this->index = index;
	this->isIdentifierSet = false;
}

CArrayIndex::CArrayIndex(const CString &refIdentifier, const CWString &refFileName, uint32 lineNumber) : ANode(refFileName, lineNumber)
{
	this->identifier = refIdentifier;
	this->isIdentifierSet = true;
}

//Destructor
CArrayIndex::~CArrayIndex()
{
	//needed because of virtual destructor
}

//Private methods
void CArrayIndex::Eval(CCompiler &refCompiler)
{
	OptAST::CConstant *pConstant;
	
	//Must be a constant
	if(refCompiler.ProcessConstant(this->identifier))
	{
		OptAST::CIntExpression *pInt;
		pConstant = refCompiler.FindConstant(this->identifier);

		if(pInt = dynamic_cast<OptAST::CIntExpression *>(pConstant->GetValue()))
		{
			this->isIdentifierSet = false;
			this->index = pInt->GetValue();
		}
		else
		{
			ASSERT(0);
		}
	}
	else
	{
		ASSERT(0);
	}
}

//Public methods
void CArrayIndex::Process(CCompiler &refCompiler)
{
	if(this->isIdentifierSet)
		this->Eval(refCompiler);
}