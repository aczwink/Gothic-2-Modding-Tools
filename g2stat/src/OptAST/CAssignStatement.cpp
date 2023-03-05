//Class Header
#include "CAssignStatement.h"
//Local
#include "AExpression.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
using namespace SJCPBLib::Daedalus::OptAST;

//Constructors
CAssignStatement::CAssignStatement(EType assignType, AExpression *pLeftValue, AExpression *pExpr)
{
	this->assignType = assignType;
	this->pLeftValue = pLeftValue;
	this->pExpr = pExpr;
	this->hasOp = false;
}

CAssignStatement::CAssignStatement(EType assignType, EOpcode op, AExpression *pLeftValue, AExpression *pExpr)
{
	this->assignType = assignType;
	this->pLeftValue = pLeftValue;
	this->pExpr = pExpr;
	this->hasOp = true;
	this->op = op;
}

//Destructor
CAssignStatement::~CAssignStatement()
{
	delete this->pLeftValue;
	delete this->pExpr;
}

//Public methods
void CAssignStatement::CollectSymbols(CCompiler &refCompiler)
{
	this->pExpr->CollectSymbols(refCompiler);
	this->pLeftValue->CollectSymbols(refCompiler);
}

void CAssignStatement::Compile(CProgramBuffer &refProgram) const
{
	this->pExpr->Compile(refProgram);
	this->pLeftValue->Compile(refProgram);

	if(this->hasOp)
	{
		refProgram.WriteByte(this->op);
		this->pLeftValue->Compile(refProgram);
	}

	switch(this->assignType)
	{
	case DAEDALUS_TYPE_FLOAT:
		{
			refProgram.WriteByte(OPCODE_ASSIGN_FLOAT);
		}
		break;
	case DAEDALUS_TYPE_FUNC:
		{
			refProgram.WriteByte(OPCODE_ASSIGN_FUNC);
		}
		break;
	case DAEDALUS_TYPE_INT:
		{
			refProgram.WriteByte(OPCODE_ASSIGN);
		}
		break;
	case DAEDALUS_TYPE_STRING:
		{
			refProgram.WriteByte(OPCODE_ASSIGN_STRING);
		}
		break;
	case DAEDALUS_TYPE_INSTANCE:
		{
			refProgram.WriteByte(OPCODE_ASSIGN_INSTANCE);
		}
		break;
	case DAEDALUS_TYPE_CLASS:
	default:
		ASSERT(0);
	}
}