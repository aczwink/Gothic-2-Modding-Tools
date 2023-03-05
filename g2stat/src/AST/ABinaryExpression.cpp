//Class Header
#include "ABinaryExpression.h"
//Local
#include "../OptAST/CBinaryExpression.h"
#include "AValueExpression.h"
#include "CIntExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::AST;

//Constructor
ABinaryExpression::ABinaryExpression(AExpression *pLeft, AExpression *pRight) : AExpression(CWString(), 0)
{
	this->pLeft = pLeft;
	this->pRight = pRight;
}

//Destructor
ABinaryExpression::~ABinaryExpression()
{
	delete this->pLeft;
	delete this->pRight;
}

//Public methods
AExpression *ABinaryExpression::GetOptimizedExpression(CCompiler &refCompiler)
{
	AExpression *pExpr;
	
	//optimize left
	pExpr = this->pLeft->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pLeft)
	{
		delete this->pLeft;
		this->pLeft = pExpr;
	}
	
	//optimize right
	pExpr = this->pRight->GetOptimizedExpression(refCompiler);
	if(pExpr != this->pRight)
	{
		delete this->pRight;
		this->pRight = pExpr;
	}
	
	if(dynamic_cast<AValueExpression *>(this->pLeft) && dynamic_cast<AValueExpression *>(this->pRight))
	{
		CIntExpression *pIntLeft, *pIntRight;
		
		//values can be combined

		if(pIntLeft = dynamic_cast<CIntExpression *>(this->pLeft))
		{
			if(pIntRight = dynamic_cast<CIntExpression *>(this->pRight))
			{
				return new CIntExpression(this->Combine(pIntLeft->GetValue(), pIntRight->GetValue()), this->GetFileName(), this->GetLineNumber());
			}
			else
			{
				ASSERT(0);
			}
		}
	}

	//can't be optimized further
	return this;
}

OptAST::AExpression *ABinaryExpression::GetTranslatedExpression(CCompiler &refCompiler) const
{
	OptAST::AExpression *pLeft, *pRight;
	
	pLeft = this->pLeft->GetTranslatedExpression(refCompiler);
	pRight = this->pRight->GetTranslatedExpression(refCompiler);

	return new OptAST::CBinaryExpression(this->GetOpcode(), pLeft, pRight);
}

bool ABinaryExpression::Process(CMap<CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback)
{
	if(!this->pLeft->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
		return false;
	if(!this->pRight->Process(refLocalVariables, pClass, pInstance, refCompiler, refCallback))
		return false;

	return true;
}

void ABinaryExpression::SetCastTo(const CType &refType)
{
}