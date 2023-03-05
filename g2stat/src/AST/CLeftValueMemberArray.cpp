//Class Header
#include "CLeftValueMemberArray.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CAccessExpression.h"
#include "../OptAST/CClassVariable.h"
#include "../OptAST/CLocalVariable.h"
#include "../OptAST/CSymbolExpression.h"
#include "AValueExpression.h"
#include "CArrayIndex.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLeftValueMemberArray::CLeftValueMemberArray(const CString &refIdentifier, const CString &refMemberName, CArrayIndex *pArrayIndex, const CWString &refFileName, uint32 lineNumber) : CLeftValueMember(refIdentifier, refMemberName, refFileName, lineNumber)
{
	this->pArrayIndex = pArrayIndex;
}

//Destructor
CLeftValueMemberArray::~CLeftValueMemberArray()
{
	delete this->pArrayIndex;
}

//Public methods
AExpression *CLeftValueMemberArray::GetOptimizedExpression(CCompiler &refCompiler)
{
	return this;
}

OptAST::AExpression *CLeftValueMemberArray::GetTranslatedExpression(CCompiler &refCompiler) const
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			return new OptAST::CAccessExpression(this->pGlobalVar, new OptAST::CSymbolExpression(this->pAttribute, (uint8)this->pArrayIndex->GetIndex()));
		}
		break;
	case IDENTIFIERTYPE_LOCALVARIABLE:
		return new OptAST::CAccessExpression(this->pLocalVariable, new OptAST::CSymbolExpression(this->pAttribute, (uint8)this->pArrayIndex->GetIndex()));
		break;
	}

	return new OptAST::CAccessExpression(this->pInstance, new OptAST::CSymbolExpression(this->pAttribute, (uint8)this->pArrayIndex->GetIndex()));
}

CType CLeftValueMemberArray::GetType() const
{
	return CType(this->pAttribute->GetType().GetType());
}

bool CLeftValueMemberArray::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	CLeftValueMember::Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	this->pArrayIndex->Process(refCompiler);

	return true;
}