//Class Header
#include "CCompiler.h"
//Global
#include <iostream>
//Libs
#include <SJCWinLib.h>
//Local
#include "AST\AGlobal.h"
#include "AST\AVariable.h"
#include "AST\CGlobals.h"
#include "AST\CInstanceList.h"
#include "OptAST/CClassVariable.h"
#include "Opcodes.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructor
CCompiler::CCompiler(const ICompilerCallback &refCallback) : refCallback(refCallback)
{
	this->pParser = new CParser(refCallback);
	this->failed = false;
	this->pInstanceHelp = new OptAST::CInstance(DAEDALUS_SYMBOL_INSTANCE_HELP, NULL, NULL, CWString(), 0);
}

//Destructor
CCompiler::~CCompiler()
{
	this->Release();
	delete this->pInstanceHelp;
}

//Private Functions
uint32 CCompiler::CalcSize(SVariables *pVariables, uint16 &refnVariables)
{
	uint32 size;

	size = 0;
	refnVariables = 0;
	while(pVariables)
	{
		size += this->GetSize(pVariables->pVariable);
		refnVariables++;
		
		pVariables = pVariables->pNext;
	}
	
	return size;
}

/*void CCompiler::Compile(SClass *pClass)
{
	uint32 classSymbolIndex, varSymbolIndex;
	SVariables *pVariables;
	SSymbolInfo attributeInfo;
	SCompileClassInfo cclassInfo;
	SCompileClassVariableInfo cclassVarInfo;
	
	classSymbolIndex = this->symbolInfo.Push(SSymbolInfo());
	cclassInfo.pVariables = new CArray<SCompileClassVariableInfo>;

	this->symbolInfo[classSymbolIndex].nEntries = 0;

	//Set size
	if(*pClass->pName == "C_INFO")
	{
		this->symbolInfo[classSymbolIndex].additionalInfo.classInfo.size = 0;
	}
	else
	{
		//subclass of AVob
		this->symbolInfo[classSymbolIndex].additionalInfo.classInfo.size = 288;
	}
	
	//Compile attributes
	attributeInfo.pName = NULL;
	attributeInfo.pValues = NULL;
	for(pVariables = pClass->pVariables; pVariables; pVariables = pVariables->pNext)
	{
		SSymbolInfo &refClassInfo = this->symbolInfo[classSymbolIndex]; //Important that this is set in EVERY iteration, because resizing the container can invalidate the reference

		attributeInfo.additionalInfo.classVarOffset = refClassInfo.additionalInfo.classInfo.size;
		
		if(pVariables->pVariable->pType->isArray)
		{
			attributeInfo.nEntries = pVariables->pVariable->pType->nArrayElements;
		}
		else
		{
			attributeInfo.nEntries = 1;
		}
		
		switch(pVariables->pVariable->pType->type)
		{
		case DAEDALUS_TYPE_FLOAT:
			{
				attributeInfo.type = DAEDALUS_TYPE_FLOAT;
				refClassInfo.additionalInfo.classInfo.size += 4 * attributeInfo.nEntries;
			}
			break;
		case DAEDALUS_TYPE_INT:
			{
				attributeInfo.type = DAEDALUS_TYPE_INT;
				refClassInfo.additionalInfo.classInfo.size += 4 * attributeInfo.nEntries;
			}
			break;
		case DAEDALUS_TYPE_STRING:
			{
				attributeInfo.type = DAEDALUS_TYPE_STRING;
				refClassInfo.additionalInfo.classInfo.size += 20 * attributeInfo.nEntries;
			}
			break;
		case DAEDALUS_TYPE_FUNC:
			{
				attributeInfo.type = DAEDALUS_TYPE_FUNC;
				refClassInfo.additionalInfo.classInfo.size += 4 * attributeInfo.nEntries;
			}
			break;
		default:
			ASSERT(0);
		}

		attributeInfo.flags = DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR;
		attributeInfo.parentIdx = classSymbolIndex;
		
		varSymbolIndex = this->symbolInfo.Push(attributeInfo);
		//refClassInfo might be invalidated from here on!!!

		this->symbolInfo[classSymbolIndex].nEntries++;
		
		cclassVarInfo.symbolIndex = varSymbolIndex;
		cclassVarInfo.pName = pVariables->pVariable->pName;

		cclassInfo.pVariables->Push(cclassVarInfo);
	}

	//Set class symbol infos...
	SSymbolInfo &refClassInfo = this->symbolInfo[classSymbolIndex];
	
	refClassInfo.pName = NULL;
	refClassInfo.type = DAEDALUS_TYPE_CLASS;
	refClassInfo.flags = 0;
	refClassInfo.additionalInfo.classInfo.offset = 0;
	refClassInfo.parentIdx = UINT32_MAX;

	this->classInfos.Insert(*pClass->pName, cclassInfo);
}*/

/*void CCompiler::Compile(SConstant *pConstant)
{
	if(pConstant->pType->isArray)
	{
		//don't check if exists
		//simply compile
		return;
	}
	
	switch(pConstant->pValue->type)
	{
	case CONSTANTVALUETYPE_FUNC:
		{
			//NOTHING HERE!!!
			ASSERT(0);
		}
		break;
	case CONSTANTVALUETYPE_FLOAT:
		//due to usage of union, we can treat floats and ints equally
	case CONSTANTVALUETYPE_INT:
		{
			this->definedConstantInts.Insert(*pConstant->pName, pConstant->pValue->value.i);
		}
		break;
	case CONSTANTVALUETYPE_STRING:
		{
			uint32 index;
			
			index = this->GetConstantStringSymbolIndex(*pConstant->pValue->value.pString);

			this->definedConstantStrings.Insert(*pConstant->pName, index);
		}
		break;
	default:
		ASSERT(0);
	}
}*/

/*void CCompiler::Compile(SConstValue *pConstValue)
{
	switch(pConstValue->type)
	{
	case CONSTANTVALUETYPE_FLOAT: //works also for float
	case CONSTANTVALUETYPE_INT:
		{
			this->program.Push(OPCODE_PUSHINT);
			this->AddUInt32ToProgram(pConstValue->value.i);
		}
		break;
	case CONSTANTVALUETYPE_STRING:
		{
			this->program.Push(OPCODE_PUSHVAR);
			this->AddUInt32ToProgram(this->GetConstantStringSymbolIndex(*pConstValue->value.pString));
		}
		break;
	default:
		ASSERT(0);
	}
}*/

/*void CCompiler::Compile(SExpression *pExpr, const CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	//compile expression in constructor

	switch(pExpr->type)
	{
	case EXPRESSIONTYPE_BITWISEAND:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_BITWISEAND);
		}
		break;
	case EXPRESSIONTYPE_BITWISEOR:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_BITWISEOR);
		}
		break;
	case EXPRESSIONTYPE_CALL:
		{
			this->CompileCall(*pExpr->value.call.pIdentifier, pExpr->value.call.pCallArgs, refLocalVariables, pClassInfo);
		}
		break;
	case EXPRESSIONTYPE_CONSTVALUE:
		{
			this->Compile(pExpr->value.pConstValue);
		}
		break;
	case EXPRESSIONTYPE_DIVIDE:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_DIVIDE);
		}
		break;
	case EXPRESSIONTYPE_EQUALS:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_EQUALS);
		}
		break;
	case EXPRESSIONTYPE_GREATEROREQUAL:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_GREATERTHANOREQUALTO);
		}
		break;
	case EXPRESSIONTYPE_GREATERTHAN:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_GREATERTHAN);
		}
		break;
	case EXPRESSIONTYPE_LEFTVALUE:
		{
			this->Compile(pExpr->value.pLeftValue, refLocalVariables, pClassInfo);
		}
		break;
	case EXPRESSIONTYPE_LESSOREQUAL:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_LESSTHANOREQUALTO);
		}
		break;
	case EXPRESSIONTYPE_LESSTHAN:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_LESSTHAN);
		}
		break;
	case EXPRESSIONTYPE_LOGICALAND:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_LOGICALAND);
		}
		break;
	case EXPRESSIONTYPE_LOGICALOR:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_LOGICALOR);
		}
		break;
	case EXPRESSIONTYPE_MINUS:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_SUBTRACT);
		}
		break;
	case EXPRESSIONTYPE_MULTIPLY:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_MULTIPLICATE);
		}
		break;
	case EXPRESSIONTYPE_NEGATE:
		{
			this->Compile(pExpr->value.pSubExpression, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_NOT);
		}
		break;
	case EXPRESSIONTYPE_NOTEQUALS:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_NOTEQUALS);
		}
		break;
	case EXPRESSIONTYPE_PLUS:
		{
			this->Compile(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);
			this->Compile(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_ADD);
		}
		break;
	case EXPRESSIONTYPE_UNARYMINUS:
		{
			this->Compile(pExpr->value.pSubExpression, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_UNARYMINUS);
		}
		break;
	default:
		ASSERT(0);
	}
}*/

/*void CCompiler::Compile(SFunction *pFunction)
{
	uint32 symbolIndex, argIndex;
	SArguments *pArgs;
	SStatements *pStatements;
	SCompileVariableInfo argInfo;
	CArray<uint32> argsStack;
	CMap<CString, SCompileVariableInfo> localVariables; //maps local variable names to their symbol index

	symbolIndex = this->definedFunctions[*pFunction->pName];

	SSymbolInfo &refSymbolInfo = this->symbolInfo[symbolIndex];

	//Parameters
	argIndex = symbolIndex + 1;
	for(pArgs = pFunction->pArguments; pArgs; pArgs = pArgs->pNext)
	{
		argInfo.symbolIndex = argIndex;
		argInfo.type = *pArgs->pType;
		localVariables.Insert(*pArgs->pIdentifier, argInfo);
		
		argsStack.Push(argIndex);
		argIndex++;
	}

	//Set program offset
	refSymbolInfo.additionalInfo.funcInfo.programOffset = this->program.GetNoOfElements();

	//compile parameter passing...
	while(!argsStack.IsEmpty())
	{
		argIndex = argsStack.Pop();

		const SSymbolInfo &refArg = this->symbolInfo[argIndex];
		
		switch(refArg.type)
		{
		case DAEDALUS_TYPE_INT:
			this->program.Push(OPCODE_PUSHVAR);
			this->AddUInt32ToProgram(argIndex);
			this->program.Push(OPCODE_ASSIGN);
			break;
		case DAEDALUS_TYPE_STRING:
			this->program.Push(OPCODE_PUSHVAR);
			this->AddUInt32ToProgram(argIndex);
			this->program.Push(OPCODE_ASSIGN_STRING);
			break;
		case DAEDALUS_TYPE_CLASS:
			this->program.Push(OPCODE_PUSHINSTANCE);
			this->AddUInt32ToProgram(argIndex);
			this->program.Push(OPCODE_ASSIGN_INSTANCE);
			break;
		default:
			ASSERT(0);
		}
	}

	//compile function body
	pStatements = pFunction->pStatements;
	while(pStatements)
	{
		this->Compile(pStatements->pStatement, localVariables);
		
		pStatements = pStatements->pNext;
	}
}*/

/*void CCompiler::Compile(SInstance *pInstance)
{
	SStatements *pStatements;
	CString *pClassName;	
	
	const SCompileInstanceInfo &refInstanceInfo = this->instanceInfos[*pInstance->pNames->pName];
	SSymbolInfo &refSymbolInfo = this->symbolInfo[refInstanceInfo.symbolIndex];
	
	//Find base
	if(pInstance->pPrototypeName)
	{
		pClassName = this->prototypeInfos[*pInstance->pPrototypeName].pClassName;
	}
	else
	{
		pClassName = pInstance->pClassName;
	}

	const SCompileClassInfo &refClassInfo = this->classInfos[*pClassName];

	//Call prototype constructor if necessary
	if(pInstance->pPrototypeName)
	{
		this->program.Push(OPCODE_CALL);
		this->instanceCallOffsets.Insert(this->program.GetNoOfElements(), this->prototypeInfos[*pInstance->pPrototypeName].symbolIndex);
		this->AddUInt32ToProgram(0);
	}
}*/

/*EType CCompiler::Compile(SLeftValue *pLeftValue, const CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	//compile left value in function

	switch(pLeftValue->type)
	{
	case LEFTVALUETYPE_ARRAY:
		{
			return this->CompileIdentifier(*pLeftValue->pIdentifier, pLeftValue->pArrayIndex, pClassInfo);
		}
		break;
	case LEFTVALUETYPE_IDENTIFIER:
		{
			return this->CompileIdentifier(*pLeftValue->pIdentifier, refLocalVariables, pClassInfo);
		}
		break;
	case LEFTVALUETYPE_MEMBER:
		{
			return this->CompileMemberIdentifier(*pLeftValue->pIdentifier, *pLeftValue->pMemberIdentifier, NULL, refLocalVariables, pClassInfo);
		}
		break;
	case LEFTVALUETYPE_MEMBERARRAY:
		{
			return this->CompileMemberIdentifier(*pLeftValue->pIdentifier, *pLeftValue->pMemberIdentifier, pLeftValue->pArrayIndex, refLocalVariables, pClassInfo);
		}
		break;
	default:
		ASSERT(0);
	}

	ASSERT(0);
}*/

/*void CCompiler::Compile(SPrototype *pPrototype)
{
	SStatements *pStatements;
	CMap<CString, SCompileVariableInfo> localVariables;
	
	const SCompilePrototypeInfo &refInfo = this->prototypeInfos[*pPrototype->pName];
	SSymbolInfo &refSymbolInfo = this->symbolInfo[refInfo.symbolIndex];
	const SCompileClassInfo &refClassInfo = this->classInfos[*pPrototype->pClassName];
	
	//Set the program offset
	refSymbolInfo.additionalInfo.programOffset = this->program.GetNoOfElements();

	//Compile body
	for(pStatements = pPrototype->pStatements; pStatements; pStatements = pStatements->pNext)
	{
		this->Compile(pStatements->pStatement, localVariables, &refClassInfo);
	}
}*/

/*void CCompiler::Compile(SStatement *pStatement, CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	//compile function
	if(!pStatement)
		return;

	switch(pStatement->type)
	{
	case STATEMENTTYPE_ASSIGNEXPR:
		{
			this->CompileAssignment(pStatement->value.assign.pLeftValue, pStatement->value.assign.pExpr, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_CALL:
		{
			this->CompileCall(*pStatement->value.call.pFunctionName, pStatement->value.call.pArgs, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_DECLARATION:
		{
			uint16 i;
			SSymbolInfo info;
			SCompileVariableInfo varInfo;

			//Fill out symbol info
			info.flags = 0;
			info.parentIdx = UINT32_MAX;
			info.pName = NULL;
			info.type = pStatement->value.decl.pType->type;

			if(pStatement->value.decl.pType->isArray)
			{
				info.nEntries = pStatement->value.decl.pType->nArrayElements;
			}
			else
			{
				info.nEntries = 1;
			}

			info.pValues = (UValue *)this->garbageCollector.MemAlloc(info.nEntries * sizeof(*info.pValues));
			for(i = 0; i < info.nEntries; i++)
			{
				if(info.type == DAEDALUS_TYPE_STRING)
				{
					info.pValues[i].pStr = this->garbageCollector.AllocString();
				}
				else
				{
					info.pValues[i].i = 0;
				}
			}
			
			varInfo.symbolIndex = this->symbolInfo.Push(info);
			varInfo.type = *pStatement->value.decl.pType;
			
			refLocalVariables.Insert(*pStatement->value.decl.pIdentifier, varInfo);
		}
		break;
	case STATEMENTTYPE_IF:
		{
			SElseIfs elseIf;

			elseIf.pCondition = pStatement->value.ifStm.pConditionExpr;
			elseIf.pNestedStatements = pStatement->value.ifStm.pNestedStatements;
			elseIf.pNext = pStatement->value.ifStm.pElseIfs;

			this->Compile(&elseIf, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_RETURN:
		{
			this->program.Push(OPCODE_RETURN);
		}
		break;
	case STATEMENTTYPE_RETURNEXPR:
		{
			this->Compile(pStatement->value.pExpr, refLocalVariables, pClassInfo);
			this->program.Push(OPCODE_RETURN);
		}
		break;
	case STATEMENTTYPE_MINUSASSIGNEXPR:
	case STATEMENTTYPE_PLUSASSIGNEXPR:
		{
			//whatever fuck it now...
			this->program.Push(OPCODE_RETURN);
		}
		break;
	default:
		ASSERT(0);
	}
}*/


/*void CCompiler::CompileCall(const CString &refFuncName, SCallArgs *pArgs, const CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	uint32 funcIndex, externalSymbolIndex;
	
	for(; pArgs; pArgs = pArgs->pNext)
	{
		this->Compile(pArgs->pExpr, refLocalVariables, pClassInfo);
	}
	
	if(this->IsExternal(refFuncName, externalSymbolIndex))
	{
		this->program.Push(OPCODE_CALLEXTERNAL);
		this->AddUInt32ToProgram(externalSymbolIndex);
	}
	else
	{
		if(!this->definedFunctions.Contains(refFuncName))
		{
			//cyclic reference
			stdOut << "UNDEFINED FUNC ->    " << refFuncName << endl;
			ASSERT(0);
		}
		funcIndex = this->definedFunctions[refFuncName];
		
		this->program.Push(OPCODE_CALL);
		this->funcCallOffsets.Insert(this->program.GetNoOfElements(), funcIndex);
		this->AddUInt32ToProgram(0);
	}
}*/

/*EType CCompiler::CompileIdentifier(const CString &refIdentifier, const CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	//Might be the constant "NULL", constant "NOFUNC"
	if(refIdentifier == "NULL" || refIdentifier == "NOFUNC")
	{
		this->program.Push(OPCODE_PUSHINT);
		this->AddUInt32ToProgram(0);

		return DAEDALUS_TYPE_INT;
	}

	//Might be a integer constant
	auto &refIt = this->definedConstantInts.Find(refIdentifier);
	if(refIt.IsValid())
	{
		this->program.Push(OPCODE_PUSHINT);
		this->AddUInt32ToProgram(refIt.GetValue());
		
		return DAEDALUS_TYPE_INT;
	}

	//Might be a string constant
	auto &refItStr = this->definedConstantStrings.Find(refIdentifier);
	if(refItStr.IsValid())
	{
		this->program.Push(OPCODE_PUSHVAR);
		this->AddUInt32ToProgram(refItStr.GetValue());

		return DAEDALUS_TYPE_STRING;
	}

	//Might be a local variable
	auto &refItLocalVar = refLocalVariables.Find(refIdentifier);
	if(refItLocalVar.IsValid())
	{
		const SSymbolInfo &refInfo = this->symbolInfo[refItLocalVar.GetValue().symbolIndex];
		
		switch(refInfo.type)
		{
		case DAEDALUS_TYPE_FLOAT:
		case DAEDALUS_TYPE_INT:
		case DAEDALUS_TYPE_STRING:
			{
				this->program.Push(OPCODE_PUSHVAR);
				this->AddUInt32ToProgram(refItLocalVar.GetValue().symbolIndex);
			}
			break;
		case DAEDALUS_TYPE_CLASS:
			{
				this->program.Push(OPCODE_PUSHINSTANCE);
				this->AddUInt32ToProgram(refItLocalVar.GetValue().symbolIndex);
			}
			break;
		default:
			ASSERT(0);
		}
		
		return refInfo.type;
	}


	//Cyclic reference is the only possible leftover
	ASSERT(0);
	return DAEDALUS_TYPE_VOID;
}*/

/*EType CCompiler::CompileIdentifier(const CString &refIdentifier, const SArrayIndex *pArrayIndex, const SCompileClassInfo *pClassInfo)
{
	//Might be a attribute
	if(pClassInfo)
	{
		foreach(it, *pClassInfo->pVariables)
		{
			if(*it.GetValue().pName == refIdentifier)
			{
				this->program.Push(OPCODE_PUSH_ARRAY_VAR);
				this->AddUInt32ToProgram(it.GetValue().symbolIndex);
				this->program.Push(pArrayIndex->index);

				ASSERT(!pArrayIndex->isIdentifier);
				
				return this->symbolInfo[it.GetValue().symbolIndex].type;
			}
		}
	}

	//Might be a global variable
	auto &refItGlobalVar = this->globalVariables.Find(refIdentifier);
	if(refItGlobalVar.IsValid())
	{
		this->program.Push(OPCODE_PUSH_ARRAY_VAR);
		this->AddUInt32ToProgram(refItGlobalVar.GetValue().symbolIndex);
		this->program.Push(pArrayIndex->index);

		ASSERT(!pArrayIndex->isIdentifier);
		
		return this->symbolInfo[refItGlobalVar.GetValue().symbolIndex].type;
	}
	
	ASSERT(0);
}*/

/*EType CCompiler::CompileMemberIdentifier(const CString &refReferenceName, const CString &refMemberName, const SArrayIndex *pArrayIndex, const CMap<CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo)
{
	//Might be a local variable
	auto &refItLocalVar = refLocalVariables.Find(refReferenceName);
	if(refItLocalVar.IsValid())
	{
		this->program.Push(OPCODE_SET_INSTANCE);
		this->AddUInt32ToProgram(refItLocalVar.GetValue().symbolIndex);

		pClassInfo = &this->classInfos[*refItLocalVar.GetValue().type.pIdentifier];
		
		goto ok;
	}

	//Might be a global variable
	auto &refItGlobalVar = this->globalVariables.Find(refReferenceName);
	if(refItGlobalVar.IsValid())
	{
		this->program.Push(OPCODE_SET_INSTANCE);
		this->AddUInt32ToProgram(refItGlobalVar.GetValue().symbolIndex);
		
		pClassInfo = &this->classInfos[*refItGlobalVar.GetValue().type.pIdentifier];
		
		goto ok;
	}

	//Might be an instance
	auto &refItInstance = this->instanceInfos.Find(refReferenceName);
	if(refItInstance.IsValid())
	{
		this->program.Push(OPCODE_SET_INSTANCE);
		this->AddUInt32ToProgram(refItInstance.GetValue().symbolIndex);
		
		pClassInfo = &this->classInfos[*refItInstance.GetValue().pClassName];
		
		goto ok;
	}
	
	ASSERT(0);
	return DAEDALUS_TYPE_VOID;

ok:;
	foreach(it, *pClassInfo->pVariables)
	{
		if(*it.GetValue().pName == refMemberName)
		{
			if(pArrayIndex)
			{
				this->program.Push(OPCODE_PUSH_ARRAY_VAR);
				this->AddUInt32ToProgram(it.GetValue().symbolIndex);
				this->program.Push(pArrayIndex->index & 0xFF);
			}
			else
			{
				this->program.Push(OPCODE_PUSHVAR);
				this->AddUInt32ToProgram(it.GetValue().symbolIndex);
			}

			return this->symbolInfo[it.GetValue().symbolIndex].type;
		}
	}

	ASSERT(0);
	return DAEDALUS_TYPE_VOID;
}*/

/*void CCompiler::CreateSymbol(SFunction *pFunction)
{
	uint16 i;
	uint32 index, argIndex;
	SArguments *pArgs;
	SSymbolInfo symbolInfo, argInfo;

	//Fill out symbol info
	symbolInfo.flags = 0;
	symbolInfo.nEntries = 0; //number of arguments
	symbolInfo.parentIdx = UINT32_MAX;
	symbolInfo.pName = pFunction->pName;
	symbolInfo.type = DAEDALUS_TYPE_FUNC;
	symbolInfo.additionalInfo.funcInfo.returnType = pFunction->returnType;

	for(pArgs = pFunction->pArguments; pArgs; pArgs = pArgs->pNext)
	{
		symbolInfo.nEntries++;
	}
	
	index = this->symbolInfo.Push(symbolInfo);
	this->definedFunctions.Insert(*pFunction->pName, index);

	//Create argument symbols
	for(pArgs = pFunction->pArguments; pArgs; pArgs = pArgs->pNext)
	{
		argInfo.flags = 0;
		argInfo.nEntries = 0;
		argInfo.parentIdx = UINT32_MAX;
		argInfo.pName = NULL;
		argInfo.pValues = NULL;
		argInfo.type = pArgs->pType->type;
		
		if(pArgs->pType->isArray)
		{
			argInfo.nEntries = pArgs->pType->nArrayElements;
		}
		else
		{
			argInfo.nEntries = 1;
		}

		argInfo.pValues = (UValue *)this->garbageCollector.MemAlloc(argInfo.nEntries * sizeof(*argInfo.pValues));

		for(i = 0; i < argInfo.nEntries; i++)
		{
			if(argInfo.type == DAEDALUS_TYPE_STRING)
			{
				argInfo.pValues[i].pStr = this->garbageCollector.AllocString();
			}
			else
			{
				argInfo.pValues[i].i = 0;
			}
		}
		
		argIndex = this->symbolInfo.Push(argInfo);
	}
}*/

/*void CCompiler::CreateSymbol(SInstance *pInstance)
{
	uint32 index;
	SSymbolInfo info;
	SCompileInstanceInfo cinfo;
	
	//Fill out SSymbolInfo
	info.flags = 0;
	info.nEntries = 0;
	info.parentIdx = UINT32_MAX;
	info.pName = pInstance->pNames->pName;
	info.type = DAEDALUS_TYPE_INSTANCE;

	index = this->symbolInfo.Push(info);

	//Fill out SCompileInstanceInfo
	cinfo.symbolIndex = index;
	cinfo.pClassName = pInstance->pClassName;
	
	this->instanceInfos.Insert(*info.pName, cinfo);

	if(pInstance->isGlobalInstance)
	{
		SCompileVariableInfo globalVarInfo;

		MemZero(&globalVarInfo, sizeof(globalVarInfo));

		globalVarInfo.type.pIdentifier = pInstance->pClassName;
		globalVarInfo.type.type = DAEDALUS_TYPE_CLASS;
		globalVarInfo.symbolIndex = index;
		
		this->globalVariables.Insert(*info.pName, globalVarInfo);
	}
}*/

/*void CCompiler::CreateSymbol(SPrototype *pPrototype)
{
	uint32 index;
	SSymbolInfo info;
	SCompilePrototypeInfo cinfo;
	
	//Fill out symbol info
	info.flags = 0;
	info.nEntries = 0;
	info.parentIdx = UINT32_MAX;
	info.pName = NULL;
	info.pValues = NULL;
	info.type = DAEDALUS_TYPE_PROTOTYPE;
	
	index = this->symbolInfo.Push(info);

	//Fill out prototype info
	cinfo.symbolIndex = index;
	cinfo.pClassName = pPrototype->pClassName;
	
	this->prototypeInfos.Insert(*pPrototype->pName, cinfo);
}*/

void CCompiler::CreateSymbolTable()
{
	foreach(it, this->constants)
	{
		if(it.GetValue()->GetReferenceCount() == 0)
		{
			//unreferenced constants are not compiled
			continue;
		}
		
		it.GetValue()->CollectSymbols(*this);
	}
	
	foreach(it, this->classes)
	{
		if(it.GetValue()->GetReferenceCount() == 0)
		{
			//unreferenced classes are not compiled
			continue;
		}
		
		it.GetValue()->CollectSymbols(*this);
	}

	foreach(it, this->functions)
	{
		//functions may be called in a world... so they need to be compiled even if they are not referenced in scripts
		it.GetValue()->CollectSymbols(*this);
	}
	
	foreach(it, this->prototypes)
	{
		if(it.GetValue()->GetReferenceCount() == 0)
		{
			//unreferenced prototypes are not compiled
			continue;
		}
		
		it.GetValue()->CollectSymbols(*this);
	}
	
	foreach(it, this->instances)
	{
		//instances may occur in a world... so they need to be compiled even if they are not referenced in scripts
		it.GetValue()->CollectSymbols(*this);
	}

	foreach(it, this->globalVariables)
	{
		if(it.GetValue()->GetReferenceCount() == 0)
		{
			//unreferenced global variables are not compiled
			continue;
		}
		
		it.GetValue()->CollectSymbols(*this);
	}

	this->pInstanceHelp->CollectSymbols(*this);
}

/*void CCompiler::CreateSymbolTable(SGlobals *pFirst)
{
	SGlobals *pGlobal;

	for(pGlobal = pFirst; pGlobal; pGlobal = pGlobal->pNext)
	{
		switch(pGlobal->type)
		{
		/*case GLOBALTYPE_VARIABLE:
			{
				SVariableInfo *pInfo;

				pInfo = this->pPreproc->GetGlobalVariableInfo(*pGlobal->value.pVariable->pName);
				if(pInfo->nReferences == 0)
					break;

				this->CompileGlobalVariable(pGlobal->value.pVariable);
			}
			break;
		}
	}
}*/

uint32 CCompiler::GetSize(SVariable *pVariable)
{
	if(pVariable->pType->isArray)
	{
		ASSERT(0);
	}

	switch(pVariable->pType->type)
	{
	case DAEDALUS_TYPE_FLOAT:
	case DAEDALUS_TYPE_INT:
		return 4;
	default:
		ASSERT(0);
	}

	ASSERT(0);
	return UINT32_MAX;
}

/*bool CCompiler::IsExternal(const CString &refFuncName, uint32 &refOutSymbolIndex)
{
	auto &refIt = this->externals.Find(refFuncName);
	if(refIt.IsValid())
	{
		refOutSymbolIndex = refIt.GetValue();
		return true;
	}
	
	return false;
}*/

bool CCompiler::ProcessUnprocessedClass(const CString &refName)
{
	const auto &refIt = this->unprocessedClasses.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::CClass *pClass;
		
		pClass = refIt.GetValue();
		this->unprocessedClasses.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		pClass->Process(*this, this->refCallback);
		
		delete pClass;
		
		return true;
	}
	return false;
}

bool CCompiler::ProcessUnprocessedConstant(const CString &refName)
{
	const auto &refIt = this->unprocessedConstants.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::AConstant *pConstant;
		
		pConstant = refIt.GetValue();
		this->unprocessedConstants.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		pConstant->Process(*this, this->refCallback);
		
		delete pConstant;
		
		return true;
	}

	return false;
}

bool CCompiler::ProcessUnprocessedFunction(const CString &refName)
{
	const auto &refIt = this->unprocessedFunctions.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::CFunction *pFunction;
		
		pFunction = refIt.GetValue();
		this->unprocessedFunctions.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		if(!pFunction->Process(*this, this->refCallback))
			this->failed = true;
		
		delete pFunction;
		
		return true;
	}

	return false;
}

bool CCompiler::ProcessUnprocessedGlobalVariable(const CString &refName)
{
	const auto &refIt = this->unprocessedGlobalVariables.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::AVariable *pVariable;
		
		pVariable = refIt.GetValue();
		this->unprocessedGlobalVariables.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		pVariable->Process(*this, this->refCallback);

		delete pVariable;
		
		return true;
	}

	return false;
}

bool CCompiler::ProcessUnprocessedInstance(const CString &refName)
{
	const auto &refIt = this->unprocessedInstances.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::AInstance *pInstance;
		
		pInstance = refIt.GetValue();
		this->unprocessedInstances.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		if(!pInstance->Process(*this, this->refCallback))
			this->failed = true;
		
		delete pInstance;
		
		return true;
	}
	
	return false;
}

bool CCompiler::ProcessUnprocessedPrototype(const CString &refName)
{
	const auto &refIt = this->unprocessedPrototypes.Find(refName.ToLowercase());
	if(refIt.IsValid())
	{
		AST::CPrototype *pPrototype;
		
		pPrototype = refIt.GetValue();
		this->unprocessedPrototypes.Delete(refIt.GetKey());//delete first to avoid cyclic processing
		if(!pPrototype->Process(*this, this->refCallback))
			this->failed = true;
		
		delete pPrototype;
		
		return true;
	}

	return false;
}

void CCompiler::PutExternal(OptAST::CExternal *pExternal)
{
	this->functions.Insert(pExternal->GetName().ToLowercase(), pExternal);
}

void CCompiler::PutExternals()
{
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_OutputSVM_Overlay", EXTERNAL_AI_OUTPUTSVM_OVERLAY, CType("C_NPC"), CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_PlayAni", EXTERNAL_AI_PLAYANI, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_PrintScreen", EXTERNAL_AI_PRINTSCREEN, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_RemoveWeapon", EXTERNAL_AI_REMOVEWEAPON, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StandUp", EXTERNAL_AI_STANDUP, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StopFX", EXTERNAL_AI_STOPFX, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StopProcessInfos", EXTERNAL_AI_STOPPROCESSINFOS, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Teleport", EXTERNAL_AI_TELEPORT, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_UseItemToState", EXTERNAL_AI_USEITEMTOSTATE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Wait", EXTERNAL_AI_WAIT, CType("C_NPC"), CType(DAEDALUS_TYPE_FLOAT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Doc_Create", EXTERNAL_DOC_CREATE));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Doc_CreateMap", EXTERNAL_DOC_CREATEMAP));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_PrintLine", EXTERNAL_DOC_PRINTLINE, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_PrintLines", EXTERNAL_DOC_PRINTLINES, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetFont", EXTERNAL_DOC_SETFONT, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetLevel", EXTERNAL_DOC_SETLEVEL, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetLevelCoords", EXTERNAL_DOC_SETLEVELCOORDS, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetMargins", EXTERNAL_DOC_SETMARGINS, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetPage", EXTERNAL_DOC_SETPAGE, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_SetPages", EXTERNAL_DOC_SETPAGES, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Doc_Show", EXTERNAL_DOC_SHOW, CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Info_AddChoice", -910, CType("C_INFO"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_FUNC)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Info_ClearChoices", -978, CType("C_INFO")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "IntroduceChapter", EXTERNAL_INTRODUCECHAPTER, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_ApplyOverlayMDSTimed", EXTERNAL_MDL_APPLYOVERLAYMDSTIMED, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_FLOAT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetBodyState", EXTERNAL_NPC_GETBODYSTATE, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetDistToWP", EXTERNAL_NPC_GETDISTTOWP, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType("C_NPC"), "Npc_GetLookAtTarget", EXTERNAL_NPC_GETLOOKATTARGET, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasItems", EXTERNAL_NPC_HASITEMS, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsPlayer", EXTERNAL_NPC_ISPLAYER, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_OwnedByNpc", -314, CType("C_Item"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_PerceiveAll", EXTERNAL_NPC_PERCEIVEALL, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_StopAni", EXTERNAL_NPC_STOPANI, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "PlayVideoEx", EXTERNAL_PLAYVIDEOEX, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "PrintScreen", EXTERNAL_PRINTSCREEN, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_GetPlayerPortalGuild", EXTERNAL_WLD_GETPLAYERPORTALGUILD));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_IsTime", EXTERNAL_WLD_ISTIME, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_PlayEffect", EXTERNAL_WLD_PLAYEFFECT, CType(DAEDALUS_TYPE_STRING), CType(CString()), CType(CString()), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_SetTime", EXTERNAL_WLD_SETTIME, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_SpawnNpcRange", EXTERNAL_WLD_SPAWNNPCRANGE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_FLOAT)));
	
	
	
	//0 arguments
	//int()
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "InfoManager_HasFinished", -922));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_GetDay", -923));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_GetFormerPlayerPortalGuild", -924));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_IsRaining", -926));
	//void()
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "ExitSession", -927));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Game_InitGerman", -928));

	//1 argument
	//C_Item(C_NPC)
	this->PutExternal(new OptAST::CExternal(CType("C_Item"), "Npc_GetEquippedArmor", -930, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType("C_Item"), "Npc_GetEquippedMeleeWeapon", -931, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType("C_Item"), "Npc_GetEquippedRangedWeapon", -932, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType("C_Item"), "Npc_GetReadiedWeapon", -934, CType("C_NPC")));
	//C_NPC(int)
	this->PutExternal(new OptAST::CExternal(CType("C_NPC"), "Hlp_GetNpc", EXTERNAL_HLP_GETNPC, CType(DAEDALUS_TYPE_INT)));
	//float(int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_FLOAT), "IntToFloat", -929, CType(DAEDALUS_TYPE_INT)));
	//int(int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_Random", EXTERNAL_HLP_RANDOM, CType(DAEDALUS_TYPE_INT)));
	//int(string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "PlayVideo", EXTERNAL_PLAYVIDEO, CType(DAEDALUS_TYPE_STRING)));
	//int(instance)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_GetInstanceID", EXTERNAL_HLP_GETINSTANCEID, CType(CString())));
	//int(C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_IsValidNpc", EXTERNAL_HLP_ISVALIDNPC, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_CanSeeSource", -6, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetActiveSpell", -935, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetActiveSpellCat", -936, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetActiveSpellIsScroll", -937, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetDistToPlayer", -939, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetLastHitSpellCat", -940, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetLastHitSpellID", -941, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetNextTarget", -942, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetPortalGuild", -943, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetStateTime", -944, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetTarget", -945, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetTrueGuild", -946, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasEquippedArmor", -947, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasEquippedMeleeWeapon", -948, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasEquippedRangedWeapon", -949, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasEquippedWeapon", -950, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsDead", EXTERNAL_NPC_ISDEAD, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsDrawingSpell", -12, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsDrawingWeapon", -951, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsInPlayersRoom", -952, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_RefuseTalk", -954, CType("C_NPC")));
	//int(C_Item)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_IsValidItem", -5, CType("C_Item")));
	//string(C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_STRING), "Npc_GetDetectedMob", -955, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_STRING), "Npc_GetNearestWP", -956, CType("C_NPC")));
	//string(int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_STRING), "IntToString", EXTERNAL_INTTOSTRING, CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_AlignToFP", -957, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_AlignToWP", -958, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Attack", -959, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_ContinueRoutine", -960, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Dodge", -961, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_DrawWeapon", -962, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_EquipBestArmor", -963, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_EquipBestMeleeWeapon", -964, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_EquipBestRangedWeapon", -965, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Flee", -966, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_ProcessInfos", -967, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_ReadyMeleeWeapon", -968, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_ReadyRangedWeapon", -969, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StandUpQuick", -972, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StopLookAt", -973, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StopPointAt", -974, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_UnequipArmor", -976, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_UnequipWeapons", -977, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_ClearAIQueue", -979, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_clearInventory", -980, CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetToFistMode", EXTERNAL_NPC_SETTOFISTMODE, CType("C_NPC")));
	//void(string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Print", EXTERNAL_PRINT, CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "PrintDebug", EXTERNAL_PRINTDEBUG, CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Snd_Play", EXTERNAL_SND_PLAY, CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_StopEffect", -300, CType(DAEDALUS_TYPE_STRING)));

	//2 arguments
	//C_Item(C_NPC, int)
	this->PutExternal(new OptAST::CExternal(CType("C_Item"), "Npc_GetInvItem", -301, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	//int(C_NPC, func)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsInRoutine", -302, CType("C_NPC"), CType(DAEDALUS_TYPE_FUNC)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsInState", EXTERNAL_NPC_ISINSTATE, CType("C_NPC"), CType(DAEDALUS_TYPE_FUNC)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_WasInState", -304, CType("C_NPC"), CType(DAEDALUS_TYPE_FUNC)));
	//int(C_NPC, C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_CanSeeNpc", -305, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_CanSeeNpcFreeLOS", -306, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetAttitude", -306, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetDistToNpc", -309, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetHeightToNpc", -311, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetPermAttitude", -312, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsDetectedMobOwnedByNpc", -313, CType("C_NPC"), CType("C_NPC")));
	//int(C_NPC, C_Item)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetDistToItem", -308, CType("C_NPC"), CType("C_Item")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetHeightToItem", -310, CType("C_NPC"), CType("C_Item")));
	//int(C_Item, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_IsItem", -315, CType("C_Item"), CType(DAEDALUS_TYPE_INT)));
	//int(C_NPC, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_CheckInfo", -316, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_GetTalentSkill", EXTERNAL_NPC_GETTALENTSKILL, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_HasBodyFlag", -318, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsInFightMode", EXTERNAL_NPC_ISINFIGHTMODE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_KnowsInfo", EXTERNAL_NPC_KNOWSINFO, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_SetActiveSpellInfo", -322, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_SetTrueGuild", -323, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_DetectItem", -324, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Npc_IsOnFP", -326, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_GetMobState", -327, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_IsFPAvailable", -328, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_IsMobAvailable", -329, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_IsNextFPAvailable", -330, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	//int(int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_GetGuildAttitude", -331, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	//int(string, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Mob_HasItems", -332, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	//int(string, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Hlp_StrCmp", -333, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING)));
	//string(string, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_STRING), "ConcatStrings", EXTERNAL_CONCATSTRINGS, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING)));
	//void(C_NPC, float)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_SetModelFatness", EXTERNAL_MDL_SETMODELFATNESS, CType("C_NPC"), CType(DAEDALUS_TYPE_FLOAT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetPercTime", -10, CType("C_NPC"), CType(DAEDALUS_TYPE_FLOAT)));
	//void(C_NPC, C_Item)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_EquipArmor", -983, CType("C_NPC"), CType("C_Item")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_GotoItem", -985, CType("C_NPC"), CType("C_Item")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_TakeItem", -989, CType("C_NPC"), CType("C_Item")));
	//void(C_NPC, C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_FinishingMove", -984, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_GotoNpc", -986, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_LookAtNpc", -987, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_PointAtNpc", -988, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_TurnToNpc", -990, CType("C_NPC"), CType("C_NPC")));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetTarget", -991, CType("C_NPC"), CType("C_NPC")));
	//void(C_NPC, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_SetWalkmode", -992, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_UseItem", -993, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Waitms", -994, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "CreateInvItem", EXTERNAL_CREATEINVITEM, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "EquipItem", EXTERNAL_EQUIPITEM, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_PercDisable", -4, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_RemoveInvItem", -100, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetAttitude", EXTERNAL_NPC_SETATTITUDE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetRefuseTalk", -102, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetStateTime", -103, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetTempAttitude", EXTERNAL_NPC_SETTEMPATTITUDE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetToFightMode", EXTERNAL_NPC_SETTOFIGHTMODE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_GotoFP", -14, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_GotoNextFP", -995, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_GotoWP", -996, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_PointAt", -998, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_ApplyOverlayMds", EXTERNAL_MDL_APPLYOVERLAYMDS, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_RemoveOverlayMDS", -9, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_SetVisual", EXTERNAL_MDL_SETVISUAL, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_ExchangeRoutine", EXTERNAL_NPC_EXCHANGEROUTINE, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_PlayAni", -900, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Snd_Play3D", -902, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	//void(int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Perc_SetRange", -904, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	//void(int, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "PrintDebugInstCh", -907, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_InsertItem", EXTERNAL_WLD_INSERTITEM, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_InsertNpc", EXTERNAL_WLD_INSERTNPC, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	//void(string, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Log_CreateTopic", EXTERNAL_LOG_CREATETOPIC, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Log_SetTopicStatus", EXTERNAL_LOG_SETTOPICSTATUS, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_AssignRoomToGuild", EXTERNAL_WLD_ASSIGNROOMTOGUILD, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	//void(string, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Log_AddEntry", EXTERNAL_LOG_ADDENTRY, CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING)));

	//3 arguments
	//int(C_NPC, string, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "AI_UseMob", -200, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	//int(C_NPC, func, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "AI_SetNpcsToState", -202, CType("C_NPC"), CType(DAEDALUS_TYPE_FUNC), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, C_NPC, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_Output", EXTERNAL_AI_OUTPUT, CType("C_NPC"), CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_OutputSVM", EXTERNAL_AI_OUTPUTSVM, CType("C_NPC"), CType("C_NPC"), CType(DAEDALUS_TYPE_STRING)));
	//void(C_NPC, int, func)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_PercEnable", -206, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_FUNC)));
	//void(C_NPC, int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_ReadySpell", -207, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "CreateInvItems", EXTERNAL_CREATEINVITEMS, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_ChangeAttribute", EXTERNAL_NPC_CHANGEATTRIBUTE, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_RemoveInvItems", EXTERNAL_NPC_REMOVEINVITEMS, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SetTalentSkill", EXTERNAL_NPC_SETTALENTSKILL, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, string, float)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_ApplyRandomAniFreq", -909, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_FLOAT)));
	//void(C_NPC, string, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_PlayAniBS", -911, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, string, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_ApplyRandomAni", -912, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_STRING)));
	//void(int, int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_SetGuildAttitude", EXTERNAL_WLD_SETGUILDATTITUDE, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	//int(C_NPC, int, func, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_INT), "Wld_DetectNpc", -915, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_FUNC), CType(DAEDALUS_TYPE_INT)));
	//void(int, int, string, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_SetMobRoutine", EXTERNAL_WLD_SETMOBROUTINE, CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, float, float, float)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_SetModelScale", EXTERNAL_MDL_SETMODELSCALE, CType("C_NPC"), CType(DAEDALUS_TYPE_FLOAT), CType(DAEDALUS_TYPE_FLOAT), CType(DAEDALUS_TYPE_FLOAT)));
	//void(C_NPC, func, int, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "AI_StartState", -11, CType("C_NPC"), CType(DAEDALUS_TYPE_FUNC), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING)));
	//void(C_NPC, int, C_NPC, C_NPC)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Npc_SendPassivePerc", -501, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType("C_NPC"), CType("C_NPC")));
	//void(C_NPC, string, float, float)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_StartFaceAni", -502, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_FLOAT), CType(DAEDALUS_TYPE_FLOAT)));
	//void(C_NPC, int, func, int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Wld_DetectNpcEx", -503, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_FUNC), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
	//void(C_NPC, int, int, int, int, func, string)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "TA_Min", EXTERNAL_TA_MIN, CType("C_NPC"), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_FUNC), CType(DAEDALUS_TYPE_STRING)));
	//void(C_NPC, string, int, int, string, int, int, int)
	this->PutExternal(new OptAST::CExternal(CType(DAEDALUS_TYPE_VOID), "Mdl_SetVisualBody", EXTERNAL_MDL_SETVISUALBODY, CType("C_NPC"), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_STRING), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT), CType(DAEDALUS_TYPE_INT)));
}

//Public Functions
void CCompiler::Compile()
{
	HeapDeleteSafe(this->pParser); //can't parse more input now!
	
	this->CreateSymbolTable();

	//classes don't need to be compiled
	
	foreach(it, this->prototypes)
	{
		it.GetValue()->Compile(this->programBuffer);
	}
	
	foreach(it, this->instances)
	{
		it.GetValue()->Compile(this->programBuffer);
	}

	foreach(it, this->functions)
	{
		it.GetValue()->Compile(this->programBuffer);
	}
}

/*void CCompiler::Compile(CCompilePreprocessor &refCompileProc)
{
	SGlobals *pGlobal;
	SSymbolInfo externalSymbolInfo, instanceHelpSymbolInfo;
	
	this->pPreproc = &refCompileProc;

	//Put externals
	externalSymbolInfo.pName = NULL;
	externalSymbolInfo.nEntries = 0;
	externalSymbolInfo.flags = 0;
	externalSymbolInfo.pValues = NULL;
	externalSymbolInfo.parentIdx = UINT32_MAX;
	
	foreach(it, GetExternals())
	{
		externalSymbolInfo.type = it.GetValue().external.type;
		externalSymbolInfo.additionalInfo.funcInfo.returnType = (EType)it.GetValue().external.offSizeRet;
		externalSymbolInfo.additionalInfo.funcInfo.programOffset = it.GetValue().external.data.programOffset;
		
		this->externals.Insert(it.GetKey(), this->symbolInfo.Push(externalSymbolInfo));
	}
	
	//Create the symbol table first
	this->CreateSymbolTable(refCompileProc.GetAST());
	
	//Compile anything
	for(pGlobal = refCompileProc.GetAST(); pGlobal; pGlobal = pGlobal->pNext)
	{
		switch(pGlobal->type)
		{
		case GLOBALTYPE_CONSTANT:
			{
				SConstantInfo *pInfo;

				//pInfo = this->pPreproc->GetConstantInfo(*pGlobal->value.pConstant->pName);
				pInfo = NULL;
				ASSERT(0);
				if(pInfo->nReferences == 0)
					break;

				this->Compile(pGlobal->value.pConstant);
			}
			break;
		case GLOBALTYPE_FUNCTION:
			{
				//functions may be called in a world... so they need to be compiled even if they are not referenced in scripts
				this->Compile(pGlobal->value.pFunction);
			}
			break;
		case GLOBALTYPE_INSTANCE:
			{
				//instances may occur in a world... so they need to be compiled even if they are not referenced in scripts
				this->Compile(pGlobal->value.pInstance);
			}
			break;
		case GLOBALTYPE_PROTOTYPE:
			{
				SPrototypeInfo *pInfo;

				pInfo = this->pPreproc->GetPrototypeInfo(*pGlobal->value.pPrototype->pName);
				if(pInfo->nReferences == 0)
					break;

				this->Compile(pGlobal->value.pPrototype);
			}
			break;
		case GLOBALTYPE_VARIABLE:
			{
				SVariableInfo *pInfo;

				pInfo = this->pPreproc->GetGlobalVariableInfo(*pGlobal->value.pVariable->pName);
				if(pInfo->nReferences == 0)
					break;

				this->CompileGlobalVariable(pGlobal->value.pVariable);
			}
			break;
		default:
			ASSERT(0);
		}
	}

	//Set the call program offsets
	foreach(it, this->funcCallOffsets)
	{
		this->SetUInt32InProgram(it.GetKey(), this->symbolInfo[it.GetValue()].additionalInfo.funcInfo.programOffset);
	}
	foreach(it, this->instanceCallOffsets)
	{
		this->SetUInt32InProgram(it.GetKey(), this->symbolInfo[it.GetValue()].additionalInfo.programOffset);
	}
	this->funcCallOffsets.Release();
	this->instanceCallOffsets.Release();
}*/
	
OptAST::CClass *CCompiler::FindClass(const CString &refIdentifier)
{
	auto &refIt = this->classes.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}

OptAST::CConstant *CCompiler::FindConstant(const CString &refIdentifier)
{
	auto &refIt = this->constants.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}

OptAST::CFunction *CCompiler::FindFunction(const CString &refIdentifier)
{
	auto &refIt = this->functions.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}

OptAST::CGlobalVariable *CCompiler::FindGlobalVariable(const CString &refIdentifier)
{
	auto &refIt = this->globalVariables.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}

OptAST::CInstance *CCompiler::FindInstance(const CString &refIdentifier)
{
	auto &refIt = this->instances.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	return NULL;
}

OptAST::CPrototype *CCompiler::FindPrototype(const CString &refIdentifier)
{
	auto &refIt = this->prototypes.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}

/*CVariable *CCompiler::FindVariable(const CString &refIdentifier)
{
	auto &refIt = this->globalVariableMap.Find(refIdentifier.ToLowercase());
	
	if(refIt.IsValid())
		return refIt.GetValue();
	
	return NULL;
}*/

uint32 CCompiler::GetConstantStringSymbolIndex(const CString &refString, const ASymbol *pSymbol)
{
	uint32 index;
	
	auto &refIt = this->constantStringsMap.Find(refString);

	if(refIt.IsValid())
		return refIt.GetValue();
	
	index = this->AddSymbol(pSymbol);
	this->constantStringsMap[refString] = index;
	
	return index;
}

bool CCompiler::Process(const CString &refInputSrcFile)
{
	byte *pCurrentScriptText;
	AST::CGlobals *pNode;
	AST::AConstant *pConstant;
	AST::CClass *pClass;
	AST::CPrototype *pPrototype;
	AST::CFunction *pFunction;
	AST::CInstanceList *pInstance;
	AST::AVariable *pVariable;
	CString currentLine;
	CWString path, currentFilePath, currentFileName;
	CFileInputStream input, currentFile;
	CFiniteSet<CWString> parsedFiles;
	
	if(!input.Open(refInputSrcFile))
	{
		this->refCallback.OnOpenFileFailed(refInputSrcFile);
		return false;
	}
	
	path = GetFilePath(refInputSrcFile) + '\\';
	
	this->refCallback.OnBeginParsing();
	
	while(!input.HitEnd())
	{
		currentLine = input.ReadString('\n');
		currentLine.Replace('\r', "");
		
		if(currentLine.IsEmpty())
			continue;

		currentFilePath = GetFilePath(path + currentLine) + '\\';
		
		CArray<CWString> &refFiles = SJCWinLib::ListFiles(currentFilePath, GetFullFileName(path + currentLine), true);

		foreach(it, refFiles)
		{
			currentFileName = currentFilePath + it.GetValue();
			
			if(parsedFiles.Contains(currentFileName.ToLowercase())) //if we parsed this file before, ignore it
				continue;
			
			if(!currentFile.Open(currentFileName))
			{
				this->refCallback.OnOpenFileFailed(currentFileName);
				return false;
			}
			
			pCurrentScriptText = (byte *)malloc(currentFile.GetSize()+1);
			currentFile.ReadBytes(pCurrentScriptText, currentFile.GetSize());
			pCurrentScriptText[currentFile.GetSize()] = '\0';
			currentFile.Close();
			
			if(!this->pParser->Parse(pCurrentScriptText, GetFilePath(currentLine) + '\\' + it.GetValue()))
			{
				memfree(pCurrentScriptText);
				this->refCallback.OnParsingFailed(currentFileName);
				return false;
			}
			memfree(pCurrentScriptText);
			
			parsedFiles.Insert(currentFileName.ToLowercase());
			
			pNode = this->pParser->GetAST();
			const CArray<AST::AGlobal *> &refGlobals = pNode->GetGlobals();
			
			for(uint32 i = 0; i < refGlobals.GetNoOfElements(); i++)
			{
				if(pConstant = dynamic_cast<AST::AConstant *>(refGlobals[i]))
				{
					ASSERT(!this->unprocessedConstants.Contains(pConstant->GetName().ToLowercase()));
					
					this->unprocessedConstants.Insert(pConstant->GetName().ToLowercase(), pConstant);
				}
				else if(pClass = dynamic_cast<AST::CClass *>(refGlobals[i]))
				{
					ASSERT(!this->unprocessedClasses.Contains(pClass->GetName().ToLowercase()));
					
					this->unprocessedClasses.Insert(pClass->GetName().ToLowercase(), pClass);
				}
				else if(pPrototype = dynamic_cast<AST::CPrototype *>(refGlobals[i]))
				{
					ASSERT(!this->prototypes.Contains(pPrototype->GetName().ToLowercase()));
					
					this->unprocessedPrototypes.Insert(pPrototype->GetName().ToLowercase(), pPrototype);
				}
				else if(pFunction = dynamic_cast<AST::CFunction *>(refGlobals[i]))
				{
					ASSERT(!this->unprocessedFunctions.Contains(pFunction->GetName().ToLowercase()));

					this->unprocessedFunctions.Insert(pFunction->GetName().ToLowercase(), pFunction);
				}
				else if(pInstance = dynamic_cast<AST::CInstanceList *>(refGlobals[i]))
				{
					pInstance->Unfold(*this);
				}
				else if(pVariable = dynamic_cast<AST::AVariable *>(refGlobals[i]))
				{
					pVariable->Unfold(*this);
				}
				else
				{
					const auto &bla = refGlobals[i];
					
					ASSERTMSG(0, "here");
				}
			}
		}
	}
	
	//Finished parsing...
	input.Close();
	this->refCallback.OnEndParsing();
	parsedFiles.Release(); //not needed anymore
	
	this->PutExternals();
	
	while(!this->unprocessedConstants.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedConstants.Begin();
		
		this->ProcessUnprocessedConstant(refIt.GetKey());
	}
	
	while(!this->unprocessedClasses.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedClasses.Begin();
		
		this->ProcessUnprocessedClass(refIt.GetKey());
	}

	while(!this->unprocessedPrototypes.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedPrototypes.Begin();
		
		this->ProcessUnprocessedPrototype(refIt.GetKey());
	}
	
	while(!this->unprocessedGlobalVariables.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedGlobalVariables.Begin();
		
		this->ProcessUnprocessedGlobalVariable(refIt.GetKey());
	}
	
	while(!this->unprocessedFunctions.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedFunctions.Begin();
		
		this->ProcessUnprocessedFunction(refIt.GetKey());
	}
	
	while(!this->unprocessedInstances.IsEmpty())
	{
		if(this->failed)
			return false;

		const auto &refIt = this->unprocessedInstances.Begin();
		
		this->ProcessUnprocessedInstance(refIt.GetKey());
	}
	
	//Clean Up
	this->refCallback.OnEndProcessing();
	return true;
}

bool CCompiler::ProcessAttribute(CString &refName, OptAST::CClass *pClass)
{
	const CLinkedList<OptAST::CClassVariable *> &refAttributes = pClass->GetVariables();
	for(OptAST::CClassVariable *pVariable : refAttributes)
	{
		if(refName.ToLowercase() == pVariable->GetName().ToLowercase())
		{
			refName = pVariable->GetName(); //overwrite name to avoid case problems
			return true;
		}
	}

	return false;
}

bool CCompiler::ProcessClass(const CString &refName)
{
	const CString &refLowerCaseName = refName.ToLowercase();
	
	const auto &refIt = this->classes.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		OptAST::CClass *pClass;
		
		pClass = refIt.GetValue();
		pClass->IncrementRefCount();
		
		return true;
	}

	if(this->ProcessUnprocessedClass(refLowerCaseName))
	{
		this->FindClass(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

bool CCompiler::ProcessConstant(const CString &refName)
{
	const CString &refLowerCaseName = refName.ToLowercase();

	const auto &refIt = this->constants.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		OptAST::CConstant *pConstant;
		
		pConstant = refIt.GetValue();
		pConstant->IncrementRefCount();
		
		return true;
	}

	if(this->ProcessUnprocessedConstant(refLowerCaseName))
	{
		this->FindConstant(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

bool CCompiler::ProcessFunction(const CString &refName)
{
	const CString &refLowerCaseName = refName.ToLowercase();
	
	const auto &refIt = this->functions.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		OptAST::CFunction *pFunction;
		
		pFunction = refIt.GetValue();
		pFunction->IncrementRefCount();
		
		return true;
	}
	
	if(this->ProcessUnprocessedFunction(refLowerCaseName))
	{
		this->FindFunction(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

bool CCompiler::ProcessGlobalVariable(const CString &refName)
{
	OptAST::CGlobalVariable *pVariable;
	
	const CString &refLowerCaseName = refName.ToLowercase();
	
	const auto &refIt = this->globalVariables.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		pVariable = refIt.GetValue();
		pVariable->IncrementRefCount();
		
		return true;
	}
	
	if(this->ProcessUnprocessedGlobalVariable(refLowerCaseName))
	{
		this->FindGlobalVariable(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

bool CCompiler::ProcessInstance(const CString &refName)
{
	const CString &refLowerCaseName = refName.ToLowercase();
	
	const auto &refIt = this->instances.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		OptAST::CInstance *pInstance;
		
		pInstance = refIt.GetValue();
		pInstance->IncrementRefCount();
		
		return true;
	}
	
	if(this->ProcessUnprocessedInstance(refLowerCaseName))
	{
		this->FindInstance(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

/*bool CCompiler::ProcessIdentifier(CString &refIdentifier, CClass *pClass)
{
	//Might be a class variable
	if(pClass)
	{
		//Might be the "slf" keyword (???)
		if(refIdentifier == "slf")
			return true;
		
		for(AVariable *pVariable : pClass->GetVariables()->GetList())
		{
			if(pVariable->GetName().ToLowercase() == refIdentifier.ToLowercase())
			{
				refIdentifier = pVariable->GetName(); //overwrite name to avoid case problems
				return true;
			}
		}
	}

	//Might be a constant
	if(this->ProcessConstant(refIdentifier))
		return true;
	//Might be a prototype
	if(this->ProcessPrototype(refIdentifier))
		return true;
	//Might be a function
	if(this->ProcessFunction(refIdentifier))
		return true;
	//Might be an instance
	if(this->ProcessInstance(refIdentifier))
		return true;
	//Might be a variable
	if(this->ProcessVariable(refIdentifier))
		return true;
	//Might be a class
	if(this->ProcessClass(refIdentifier))
		return true;
	
	ASSERT(0);
	return false;
}*/

bool CCompiler::ProcessPrototype(const CString &refName)
{
	const CString &refLowerCaseName = refName.ToLowercase();

	const auto &refIt = this->prototypes.Find(refLowerCaseName);
	if(refIt.IsValid())
	{
		OptAST::CPrototype *pPrototype;
		
		pPrototype = refIt.GetValue();
		pPrototype->IncrementRefCount();
		
		return true;
	}
	
	if(this->ProcessUnprocessedPrototype(refLowerCaseName))
	{
		this->FindPrototype(refLowerCaseName)->IncrementRefCount();
		return true;
	}
	
	return false;
}

void CCompiler::Release()
{
	HeapDeleteSafe(this->pParser); //make sure the parser is killed
	
	foreach(it, this->classes)
		delete it.GetValue();
	this->classes.Release();
	
	foreach(it, this->unprocessedClasses)
		delete it.GetValue();
	this->unprocessedClasses.Release();
	
	foreach(it, this->constants)
		delete it.GetValue();
	this->constants.Release();

	foreach(it, this->unprocessedConstants)
		delete it.GetValue();
	this->unprocessedConstants.Release();
	
	foreach(it, this->functions)
		delete it.GetValue();
	this->functions.Release();

	foreach(it, this->unprocessedFunctions)
		delete it.GetValue();
	this->unprocessedFunctions.Release();
	
	foreach(it, this->globalVariables)
		delete it.GetValue();
	this->globalVariables.Release();

	foreach(it, this->unprocessedGlobalVariables)
		delete it.GetValue();
	this->unprocessedGlobalVariables.Release();
	
	foreach(it, this->instances)
		delete it.GetValue();
	this->instances.Release();

	foreach(it, this->unprocessedInstances)
		delete it.GetValue();
	this->unprocessedInstances.Release();
	
	foreach(it, this->prototypes)
		delete it.GetValue();
	this->prototypes.Release();

	foreach(it, this->unprocessedPrototypes)
		delete it.GetValue();
	this->unprocessedPrototypes.Release();
	
	this->symbolList.Release();
	this->constantStringsMap.Release();
}

void CCompiler::WriteOutput(AOutputStream &refOutputStream)
{
	uint32 i;
	
	//header
	refOutputStream.WriteByte(0x32); //version
	refOutputStream.WriteUInt32(this->symbolList.GetNoOfElements()); //number of symbols
	
	//sortTable
	for(i = 0; i < this->symbolList.GetNoOfElements(); i++)
	{
		refOutputStream.WriteUInt32(i);
	}

	for(const ASymbol *pSymbol : this->symbolList)
	{
		pSymbol->WriteSymbol(refOutputStream);
	}
	
	//Write the program
	refOutputStream.WriteUInt32(this->programBuffer.GetRemainingBytes());
	this->programBuffer.FlushTo(refOutputStream);

	this->programBuffer.Close(); //don't need the program anymore
}