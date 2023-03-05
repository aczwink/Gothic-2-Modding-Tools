//Class Header
#include "CLeftValueIdentifier.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/CFuncExpression.h"
#include "../OptAST/CInstanceExpression.h"
#include "../OptAST/CIntExpression.h"
#include "../OptAST/CLocalVariable.h"
#include "../OptAST/CStringExpression.h"
#include "../OptAST/CSymbolExpression.h"
#include "CAttributeExpression.h"
#include "CFuncExpression.h"
#include "CIntExpression.h"
#include "CStringExpression.h"
#include "CVariables.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CLeftValueIdentifier::CLeftValueIdentifier(const CString &refIdentifier, const CWString &refFileName, uint32 lineNumber) : AExpression(refFileName, lineNumber)
{
	this->identifier = refIdentifier;
	this->hasCast = false;
}

//Destructor
CLeftValueIdentifier::~CLeftValueIdentifier()
{
	//needed because of virtual destructor
}

//Public methods
/*void CLeftValueIdentifier::Compile(AOutputStream &refOutputStream, CMap<CString, AVariable *> &refLocalVariables, CClass *pClass, CCompiler &refCompiler)
{
	AConstant *pConstant;
	CFunction *pFunction;
	CInstance *pInstance;
	CVariable *pVariable;
	
	//Might be an attribute
	if(pClass)
	{
		for(AVariable *pVariable : pClass->GetVariables()->GetList())
		{
			if(pVariable->GetName() == this->identifier)
			{
				refOutputStream.WriteByte(OPCODE_PUSHVAR);
				refOutputStream.WriteUInt32(pVariable->GetSymbolIndex());
				
				return;
			}
		}
	}
	
	//Might be a constant
	pConstant = refCompiler.FindConstant(this->identifier);
	if(pConstant)
	{
		pConstant->Compile(refOutputStream, refCompiler);
		return;
	}
	
	//Might be an instance
	pInstance = refCompiler.FindInstance(this->identifier);
	if(pInstance)
	{
		refOutputStream.WriteByte(OPCODE_PUSHINT);
		refOutputStream.WriteUInt32(pInstance->GetSymbolIndex());
		
		return;
	}
	
	//Might be a function
	pFunction = refCompiler.FindFunction(this->identifier);
	if(pFunction)
	{
		refOutputStream.WriteByte(OPCODE_PUSHINT);
		refOutputStream.WriteUInt32(pFunction->GetSymbolIndex());
		return;
	}
	
	//Might be a global variable
	pVariable = refCompiler.FindVariable(this->identifier);
	if(pVariable)
	{
		if(pVariable->GetType().GetType() == DAEDALUS_TYPE_INSTANCE)
			refOutputStream.WriteByte(OPCODE_PUSHINSTANCE);
		else
			refOutputStream.WriteByte(OPCODE_PUSHVAR);
		
		refOutputStream.WriteUInt32(pVariable->GetSymbolIndex());
		return;
	}
	
	ASSERT(0);
}*/

AExpression *CLeftValueIdentifier::GetOptimizedExpression(CCompiler &refCompiler)
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_ATTRIBUTE:
		{
			return new CAttributeExpression(this->pClass->FindVariable(this->identifier), this->GetFileName(), this->GetLineNumber());
		}
		break;
	case IDENTIFIERTYPE_CONSTANT:
		{
			OptAST::CConstant *pConstant;
			OptAST::CIntExpression *pInt;
			OptAST::CStringExpression *pStr;
			
			pConstant = refCompiler.FindConstant(this->identifier);
			
			if(pInt = dynamic_cast<OptAST::CIntExpression *>(pConstant->GetValue()))
			{
				return new CIntExpression(pInt->GetValue(), this->GetFileName(), this->GetLineNumber());
			}
			else if(pStr = dynamic_cast<OptAST::CStringExpression *>(pConstant->GetValue()))
			{
				return new CStringExpression(pStr->GetValue(), this->GetFileName(), this->GetLineNumber());
			}
			else
			{
				ASSERT(0);
			}
		}
		break;
	case IDENTIFIERTYPE_FUNCTION:
		return new CFuncExpression(this->pFunction->GetName(), this->GetFileName(), this->GetLineNumber());
	case IDENTIFIERTYPE_GLOBALVARIABLE:
	case IDENTIFIERTYPE_INSTANCE:
	case IDENTIFIERTYPE_LOCALVARIABLE:
	case IDENTIFIERTYPE_NOFUNC:
	case IDENTIFIERTYPE_NULL:
	case IDENTIFIERTYPE_SLF:
		{
			return this;
		}
		break;
	}

	ASSERT(0);
	return NULL;
}

OptAST::AExpression *CLeftValueIdentifier::GetTranslatedExpression(CCompiler &refCompiler) const
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_CONSTANT:
		return refCompiler.FindConstant(this->identifier)->GetValue()->Copy();
	case IDENTIFIERTYPE_FUNCTION:
		return new OptAST::CFuncExpression(refCompiler.FindFunction(this->identifier));
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		if(this->pGlobalVar->GetType().GetType() == DAEDALUS_TYPE_INSTANCE)
			return new OptAST::CInstanceExpression(this->pGlobalVar);
		return new OptAST::CSymbolExpression(this->pGlobalVar);
	case IDENTIFIERTYPE_INSTANCE:
		{
			if(this->hasCast && this->castToType.GetType() == DAEDALUS_TYPE_INT)
				return new OptAST::CFuncExpression(this->pInstance);
			
			return new OptAST::CInstanceExpression(this->pInstance);
		}
		break;
	case IDENTIFIERTYPE_LOCALVARIABLE:
		{
			if(this->pLocalVariable->GetType().GetType() == DAEDALUS_TYPE_INSTANCE)
				return new OptAST::CInstanceExpression(this->pLocalVariable);

			return new OptAST::CSymbolExpression(this->pLocalVariable);
		}
		break;
	case IDENTIFIERTYPE_NOFUNC:
		return new OptAST::CIntExpression(-1);
	case IDENTIFIERTYPE_NULL:
		return new OptAST::CIntExpression(0);
	case IDENTIFIERTYPE_SLF:
		{
			return new OptAST::CSymbolExpression(this->pInstance);
		}
		break;
	}

	ASSERT(0);
	return NULL;
}

CType CLeftValueIdentifier::GetType() const
{
	switch(this->type)
	{
	case IDENTIFIERTYPE_CONSTANT:
		return this->pConstant->GetType();
	case IDENTIFIERTYPE_FUNCTION:
		return CType(DAEDALUS_TYPE_FUNC);
	case IDENTIFIERTYPE_GLOBALVARIABLE:
		{
			return this->pGlobalVar->GetType();
		}
		break;
	case IDENTIFIERTYPE_INSTANCE:
	case IDENTIFIERTYPE_SLF:
		if(!this->pInstance->GetClass())
			return CType(CString()); //TODO: SHIT!
		return CType(this->pInstance->GetClass()->GetName());
	case IDENTIFIERTYPE_LOCALVARIABLE:
		{
			return this->pLocalVariable->GetType();
		}
		break;
	case IDENTIFIERTYPE_NOFUNC:
		return CType(DAEDALUS_TYPE_FUNC);
	case IDENTIFIERTYPE_NULL:
		return CType(CString()); //any instance
	}

	ASSERT(0);
	return CType();
}

bool CLeftValueIdentifier::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	if(pClass)
	{
		if(this->identifier == "slf") //special reference to class in constructor
		{
			this->type = IDENTIFIERTYPE_SLF;
			this->pInstance = pInstance;
			return true;
		}
		//Might be an attribute
		if(refCompiler.ProcessAttribute(this->identifier, pClass))
		{
			this->type = IDENTIFIERTYPE_ATTRIBUTE;
			this->pClass = pClass;
			return true;
		}
	}
	
	//Might be the constant "NULL"
	if(this->identifier == "NULL")
	{
		this->type = IDENTIFIERTYPE_NULL;
		return true;
	}
	//Might be the constant "NOFUNC"
	if(this->identifier == "NOFUNC")
	{
		this->type = IDENTIFIERTYPE_NOFUNC;
		return true;
	}
	//Might be a local variable
	auto &refIt = refLocalVariables.Find(this->identifier.ToLowercase());
	if(refIt.IsValid())
	{
		this->type = IDENTIFIERTYPE_LOCALVARIABLE;
		this->pLocalVariable = refIt.GetValue();
		return true;
	}
	//might be a constant
	if(refCompiler.ProcessConstant(this->identifier))
	{
		this->type = IDENTIFIERTYPE_CONSTANT;
		this->pConstant = refCompiler.FindConstant(this->identifier);
		return true;
	}
	//Might be a function
	if(refCompiler.ProcessFunction(this->identifier))
	{
		this->type = IDENTIFIERTYPE_FUNCTION;
		this->pFunction = refCompiler.FindFunction(this->identifier);
		
		return true;
	}
	//Might be an instance
	if(refCompiler.ProcessInstance(this->identifier))
	{
		this->type = IDENTIFIERTYPE_INSTANCE;
		this->pInstance = refCompiler.FindInstance(this->identifier);
		return true;
	}
	//Might be a global variable
	if(refCompiler.ProcessGlobalVariable(this->identifier))
	{
		this->type = IDENTIFIERTYPE_GLOBALVARIABLE;
		this->pGlobalVar = refCompiler.FindGlobalVariable(this->identifier);
		return true;
	}
	
	refCallback.OnUndefinedIdentifier(this->identifier, this->GetFileName(), this->GetLineNumber());
	return false;
}

void CLeftValueIdentifier::SetCastTo(const CType &refType)
{
	this->hasCast = true;
	this->castToType = refType;
}