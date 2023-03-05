//Class Header
#include "CAttributeExpression.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CClassVariable.h"
#include "../OptAST/CSymbolExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CAttributeExpression::CAttributeExpression(OptAST::CClassVariable *pAttribute, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->pAttribute = pAttribute;
	this->hasIndex = false;
}

CAttributeExpression::CAttributeExpression(OptAST::CClassVariable *pAttribute, uint8 index, const CWString &refFileName, uint32 lineNumber) : AValueExpression(refFileName, lineNumber)
{
	this->pAttribute = pAttribute;
	this->hasIndex = true;
	this->index = index;
}

//Public methods
OptAST::AExpression *CAttributeExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	if(this->hasIndex)
		return new OptAST::CSymbolExpression(this->pAttribute, this->index);
	return new OptAST::CSymbolExpression(this->pAttribute);
}

CType CAttributeExpression::GetType() const
{
	const CType &refType = this->pAttribute->GetType();

	if(this->hasIndex)
	{
		CType &refSubType = CType(refType);
		
		refSubType.UnsetArray();

		return refSubType;
	}

	return refType;
}