//Class Header
#include "CConstant.h"
//Local
#include "../CCompiler.h"
#include "../OptAST/AValueExpression.h"
#include "AExpression.h"
#include "AValueExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CConstant::CConstant(CType *pType, const CString &refName, AExpression *pValue, const CWString &refFileName, uint32 lineNumber) : AConstant(pType, refName, refFileName, lineNumber)
{
	this->pValue = pValue;
}

//Destructor
CConstant::~CConstant()
{
	delete this->pValue;
}

//Public methods
/*void CConstant::Compile(AOutputStream &refProgram, CCompiler &refCompiler) const
{
	CMap<CString, AVariable *> localVariables;
	
	this->pValue->Compile(refProgram, localVariables, NULL, refCompiler);
}*/

bool CConstant::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	AExpression *pValue;
	
	this->pValue->Process(CMap<CString, OptAST::CLocalVariable *>(), NULL, NULL, refCompiler, refCallback); //no local variables and no class
	pValue = this->pValue->GetOptimizedExpression(refCompiler);
	if(pValue != this->pValue)
	{
		//value was optimized
		delete this->pValue;
		this->pValue = pValue;
	}

	if(dynamic_cast<AValueExpression *>(this->pValue))
	{
		OptAST::CConstant *pConstant;
		
		pConstant = new OptAST::CConstant(*this->pType, this->GetName(), (OptAST::AValueExpression *)(this->pValue->GetTranslatedExpression(refCompiler)), this->GetFileName(), this->GetLineNumber());
		refCompiler.Add(pConstant);
	}
	else
	{
		ASSERT(0);
	}

	return true;
}

/*void CConstant::WriteSymbols(SJCLib::AOutputStream &refOutputStream) const
{
	UValue value;
	
	ASSERT(this->pType->GetNumberOfElements() == 1);
	switch(this->pType->GetType())
	{
	case DAEDALUS_TYPE_FLOAT:
		{
			value.f = dynamic_cast<CConstValueFloat *>(this->pValue)->GetValue();
		}
		break;
	case DAEDALUS_TYPE_INT:
		{
			value.i = dynamic_cast<CConstValueInt *>(this->pValue)->GetValue();
		}
		break;
	case DAEDALUS_TYPE_STRING:
		{
			value.pStr = new CString;
			*value.pStr = dynamic_cast<CConstValueLiteral *>(this->pValue)->GetValue();
		}
		break;
	default:
		ASSERT(0);
	}
	
	this->WriteSymbol(refOutputStream, CString(), 0, this->pType->GetNumberOfElements(), this->pType->GetType(), 0, 0, 0, 0, UINT32_MAX);

	if(this->pType->GetType() == DAEDALUS_TYPE_STRING)
	{
		delete value.pStr;
	}
}*/