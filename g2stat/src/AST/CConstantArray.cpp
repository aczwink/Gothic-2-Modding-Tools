//Class Header
#include "CConstantArray.h"
//Local
#include "../CCompiler.h"
#include "../CType.h"
#include "../OptAST/CConstant.h"
#include "../OptAST/CConstArrayExpression.h"
#include "CArrayIndex.h"
#include "CExprList.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
CConstantArray::CConstantArray(CType *pType, const CString &refName, CArrayIndex *pArraySize, CExprList *pValues, const CWString &refFileName, uint32 lineNumber) : AConstant(pType, refName, refFileName, lineNumber)
{
	this->pArraySize = pArraySize;
	this->pValues = pValues;
}

//Destructor
CConstantArray::~CConstantArray()
{
	delete this->pArraySize;
	delete this->pValues;
}

//Public methods
bool CConstantArray::Process(CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	bool isArrayConstant;
	
	this->pArraySize->Process(refCompiler);
	this->pType->SetNumberOfElements(this->pArraySize->GetIndex());
	this->pValues->Process(CMap<CString, OptAST::CLocalVariable *>(), NULL, NULL, refCompiler, refCallback);
	isArrayConstant = this->pValues->Optimize(refCompiler);
	
	if(isArrayConstant)
	{
		OptAST::CConstant *pConstant;
		
		pConstant = new OptAST::CConstant(*this->pType, this->GetName(), this->pValues->GetTranslatedExpression(refCompiler), this->GetFileName(), this->GetLineNumber());
		refCompiler.Add(pConstant);
	}
	else
	{
		ASSERT(0);
	}

	return true;
}

/*void CConstantArray::WriteSymbols(AOutputStream &refOutputStream) const
{
	UValue *pValues;
	CConstValues *pValuesNodes;
	
	pValues = (UValue *)MemAlloc(sizeof(UValue) * this->pType->GetNumberOfElements());
	pValuesNodes = dynamic_cast<CConstValues *>(this->pValue);
	for(uint32 i = 0; i < this->pType->GetNumberOfElements(); i++)
	{
		switch(this->pType->GetType())
		{
		case DAEDALUS_TYPE_FLOAT:
			{
				pValues[i].f = dynamic_cast<CConstValueFloat *>(pValuesNodes->GetValues()[i])->GetValue();
			}
			break;
		case DAEDALUS_TYPE_INT:
			{
				pValues[i].i = dynamic_cast<CConstValueInt *>(pValuesNodes->GetValues()[i])->GetValue();
			}
			break;
		case DAEDALUS_TYPE_STRING:
			{
				pValues[i].pStr = new CString;
				*pValues[i].pStr = dynamic_cast<CConstValueLiteral *>(pValuesNodes->GetValues()[i])->GetValue();
			}
			break;
		}
	}

	this->WriteSymbol(refOutputStream, CString(), 0, this->pType->GetNumberOfElements(), this->pType->GetType(), 0, 0, pValues, this->pType->GetNumberOfElements(), UINT32_MAX);

	if(this->pType->GetType() == DAEDALUS_TYPE_STRING)
	{
		for(uint32 i = 0; i < this->pType->GetNumberOfElements(); i++)
		{
			delete pValues[i].pStr;
		}
	}
}*/