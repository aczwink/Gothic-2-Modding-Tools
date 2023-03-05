//Class Header
#include "CLeftValueArray.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CClass.h"
#include "../OptAST/CSymbolExpression.h"
#include "AValueExpression.h"
#include "AVariable.h"
#include "CArrayIndex.h"
#include "CAttributeExpression.h"
#include "CClass.h"
#include "CVariables.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLeftValueArray::CLeftValueArray(const CString &refIdentifier, CArrayIndex *pArrayIndex, const CWString &refFileName, uint32 lineNumber) : CLeftValueIdentifier(refIdentifier, refFileName, lineNumber)
{
	this->pArrayIndex = pArrayIndex;
}

//Destructor
CLeftValueArray::~CLeftValueArray()
{
	delete this->pArrayIndex;
}

//Public methods
AExpression *CLeftValueArray::GetOptimizedExpression(CCompiler &refCompiler)
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_ATTRIBUTE:
		{
			return new CAttributeExpression(this->pClass->FindVariable(this->identifier), (uint8)this->pArrayIndex->GetIndex(), this->GetFileName(), this->GetLineNumber());
		}
		break;
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			return this;
		}
		break;
	}

	ASSERT(0);
	return NULL;
}

OptAST::AExpression *CLeftValueArray::GetTranslatedExpression(CCompiler &refCompiler) const
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			return new OptAST::CSymbolExpression(refCompiler.FindGlobalVariable(this->identifier), (uint8)this->pArrayIndex->GetIndex());
		}
		break;
	}

	ASSERT(0);
	return NULL;
}

CType CLeftValueArray::GetType() const
{
	CType &refType = CLeftValueIdentifier::GetType();

	if(refType.GetType() == DAEDALUS_TYPE_INSTANCE)
		return CType(refType.GetClassName());
	return CType(refType.GetType());
}

bool CLeftValueArray::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	CLeftValueIdentifier::Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	this->pArrayIndex->Process(refCompiler);

	return true;
}