//Class Header
#include "CLeftValueMember.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CAccessExpression.h"
#include "../OptAST/CClassVariable.h"
#include "../OptAST/CLocalVariable.h"
#include "../OptAST/CSymbolExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLeftValueMember::CLeftValueMember(const CString &refIdentifier, const CString &refMemberName, const CWString &refFileName, uint32 lineNumber) : CLeftValueIdentifier(refIdentifier, refFileName, lineNumber)
{
	this->memberName = refMemberName;
}

//Destructor
CLeftValueMember::~CLeftValueMember()
{
	//needed because of virtual destructor
}

//Public methods
AExpression *CLeftValueMember::GetOptimizedExpression(CCompiler &refCompiler)
{
	return this;
}

OptAST::AExpression *CLeftValueMember::GetTranslatedExpression(CCompiler &refCompiler) const
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			return new OptAST::CAccessExpression(this->pGlobalVar, new OptAST::CSymbolExpression(this->pAttribute));
		}
		break;
	case IDENTIFIERTYPE_LOCALVARIABLE:
		return new OptAST::CAccessExpression(this->pLocalVariable, new OptAST::CSymbolExpression(this->pAttribute));
	}

	return new OptAST::CAccessExpression(this->pInstance, new OptAST::CSymbolExpression(this->pAttribute));
}

CType CLeftValueMember::GetType() const
{
	return this->pAttribute->GetType();
}

bool CLeftValueMember::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	CLeftValueIdentifier::Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback);
	
	switch(this->type)
	{
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			this->pGlobalVar = refCompiler.FindGlobalVariable(this->identifier);
			this->pClass = refCompiler.FindClass(this->pGlobalVar->GetType().GetClassName());
			refCompiler.ProcessAttribute(this->memberName, this->pClass);
			this->pAttribute = this->pClass->FindVariable(this->memberName);
		}
		break;
	case IDENTIFIERTYPE_INSTANCE:
		{
			this->pInstance = refCompiler.FindInstance(this->identifier);
			refCompiler.ProcessAttribute(this->memberName, this->pInstance->GetClass());
			this->pAttribute = this->pInstance->GetClass()->FindVariable(this->memberName);
		}
		break;
	case IDENTIFIERTYPE_LOCALVARIABLE:
		{
			this->pLocalVariable = refLocalVariables[this->identifier.ToLowercase()];
			this->pClass = refCompiler.FindClass(this->pLocalVariable->GetType().GetClassName());
			refCompiler.ProcessAttribute(this->memberName, this->pClass);
			this->pAttribute = this->pClass->FindVariable(this->memberName);
		}
		break;
	case IDENTIFIERTYPE_SLF:
		{
			this->pInstance = pInstance;
			refCompiler.ProcessAttribute(this->memberName, this->pInstance->GetClass());
			this->pAttribute = this->pInstance->GetClass()->FindVariable(this->memberName);
		}
		break;
	default:
		ASSERT(0);
	}

	return true;
}