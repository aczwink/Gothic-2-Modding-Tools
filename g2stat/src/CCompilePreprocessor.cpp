/*//Class Header
#include "CCompilePreprocessor.h"
//Local
#include "CClass.h"
#include "CInstance.h"
#include "CVariable.h"
#include "DaedalusErrors.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructor
CCompilePreprocessor::CCompilePreprocessor(const ICallback *pCallback)
{
	this->pCurrentScriptText = NULL;
	this->pFirstAST = NULL;
	this->pCurrentLastGlobal = NULL;
}

//Destructor
CCompilePreprocessor::~CCompilePreprocessor()
{
	memfreesafe(this->pCurrentScriptText);
}

//Private Functions
void CCompilePreprocessor::AddGlobal(SGlobals *pGlobal)
{
	if(this->pFirstAST == NULL)
	{
		this->pFirstAST = pGlobal;
		this->pCurrentLastGlobal = pGlobal;
		return;
	}

	this->pCurrentLastGlobal->pNext = pGlobal;
	this->pCurrentLastGlobal = pGlobal;
}

EType CCompilePreprocessor::CheckIdentifier(CString &refIdentifier, bool &refIsExternal, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	SConstantInfo *pInfo;
	SClassInfo *pOtherClassInfo;
	SFunctionInfo *pFuncInfo;
	SInstanceInfo *pInstanceInfo;
	SVariableInfo *pVarInfo;

reprocess:;
	refIsExternal = false;
	//Might be an attribute
	if(pClassInfo)
	{
		SVariables *pVariables;
		
		for(pVariables = pClassInfo->pVariables; pVariables; pVariables = pVariables->pNext)
		{
			if(pVariables->pVariable->pName->ToLowercase() == refIdentifier.ToLowercase())
			{
				//overwrite name to avoid case problems
				refIdentifier = *pVariables->pVariable->pName;

				return pVariables->pVariable->pType->type;
			}
		}
	}

	//Might be a constant
	//pInfo = this->GetConstantInfo(refIdentifier);
	pInfo = NULL;
	ASSERT(0);
	if(pInfo)
	{
		pInfo->nReferences++;
		refIdentifier = *pInfo->pName; //overwrite name to avoid case problems
		
		return pInfo->type;
	}

	//Might be a local variable
	auto &refItLocalVar = refLocalVariables.Find(refIdentifier.ToLowercase());
	if(refItLocalVar.IsValid())
	{
		refIdentifier = *refItLocalVar.GetValue().pIdentifier; //overwrite name to avoid case problems

		return refItLocalVar.GetValue().pType->type;
	}

	//Might be a global variable
	pVarInfo = this->GetGlobalVariableInfo(refIdentifier);
	if(pVarInfo)
	{
		pVarInfo->nReferences++;

		//overwrite name to avoid case problems
		refIdentifier = *pVarInfo->pName;
		
		return pVarInfo->pType->type;
	}

	//Might be an instance
	pInstanceInfo = this->GetInstanceInfo(refIdentifier);
	if(pInstanceInfo)
	{
		pInstanceInfo->nReferences++;

		//overwrite name to avoid case problems
		refIdentifier = *pInstanceInfo->pName;

		return DAEDALUS_TYPE_INSTANCE;
	}

	//Might be a function
	pFuncInfo = this->GetFunctionInfo(refIdentifier);
	if(pFuncInfo)
	{
		pFuncInfo->nReferences++;

		//overwrite name to avoid case problems
		refIdentifier = *pFuncInfo->pName;
		
		return DAEDALUS_TYPE_FUNC;
	}

	//Might be an external
	/*
	auto &refItExternal = this->externalsMap.Find(refIdentifier.ToLowercase());
	if(refItExternal.IsValid())
	{
		refIsExternal = true;
		//overwrite name to avoid case problems
		refIdentifier = refItExternal.GetValue();
		
		return (EType)GetExternals()[refIdentifier].external.offSizeRet;
	}
	* /
	ASSERT(0);

	//Might be a class
	pOtherClassInfo = this->GetClassInfo(refIdentifier);
	if(pOtherClassInfo)
	{
		pOtherClassInfo->nReferences++;

		//overwrite name to avoid case problems
		refIdentifier = *pOtherClassInfo->pName;

		return DAEDALUS_TYPE_CLASS;
	}
	
	//Might be an unprocessed...
	if(this->ProcessUnprocessed(refIdentifier))
	{
		goto reprocess;
	}

	ASSERT(0);
	return DAEDALUS_TYPE_VOID;
}

EType CCompilePreprocessor::CheckMemberIdentifier(CString &refReferenceName, CString &refMemberName, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	SInstanceInfo *pInstanceInfo;
	SVariableInfo *pVarInfo;
	SVariables *pVariables;

reprocess:;
	//Might be a local variable
	auto &refItLocalVar = refLocalVariables.Find(refReferenceName.ToLowercase());
	if(refItLocalVar.IsValid())
	{
		//overwrite name to avoid case problems
		refReferenceName = *refItLocalVar.GetValue().pIdentifier;

		if(refItLocalVar.GetValue().pType->type != DAEDALUS_TYPE_CLASS)
		{
			ASSERT(0);
		}

		pClassInfo = this->GetClassInfo(*refItLocalVar.GetValue().pType->pIdentifier);
		
		goto referenceOk;
	}

	//Might be a global variable
	pVarInfo = this->GetGlobalVariableInfo(refReferenceName);
	if(pVarInfo)
	{
		pVarInfo->nReferences++;

		//overwrite name to avoid case problems
		refReferenceName = *pVarInfo->pName;

		if(pVarInfo->pType->type != DAEDALUS_TYPE_CLASS)
		{
			ASSERT(0);
		}

		pClassInfo = this->GetClassInfo(*pVarInfo->pType->pIdentifier);
		
		goto referenceOk;
	}
	
	//Might be an instance
	pInstanceInfo = this->GetInstanceInfo(refReferenceName);
	if(pInstanceInfo)
	{
		pInstanceInfo->nReferences++;
		
		//overwrite name to avoid case problems
		refReferenceName = *pInstanceInfo->pName;
		pClassInfo = this->GetClassInfo(*pInstanceInfo->pClassName);
		
		goto referenceOk;
	}

	//Might be the "slf" keyword
	if(refReferenceName == "slf")
	{
		//pClassInfo is current class
		goto referenceOk;
	}

	//Might be an unprocessed...
	if(this->ProcessUnprocessed(refReferenceName))
	{
		goto reprocess;
	}
	
	ASSERT(false);

referenceOk:;
	//Now check the member
	for(pVariables = pClassInfo->pVariables; pVariables; pVariables = pVariables->pNext)
	{
		if(pVariables->pVariable->pName->ToLowercase() == refMemberName.ToLowercase())
		{
			//overwrite name to avoid case problems
			refMemberName = *pVariables->pVariable->pName;
			return pVariables->pVariable->pType->type;
		}
	}
	
	ASSERT(0);
	return DAEDALUS_TYPE_VOID;
}

void CCompilePreprocessor::EvalArrayIndex(SArrayIndex *pArrayIndex)
{
	ASSERT(pArrayIndex);
	
	if(pArrayIndex->isIdentifier)
	{
		SConstantInfo *pInfo;
		
		this->CheckIdentifier(*pArrayIndex->pIdentifier, CMap<CString, SLocalVarInfo>(), NULL);
		//pInfo = this->GetConstantInfo(*pArrayIndex->pIdentifier);
		pInfo = NULL;
		ASSERT(0);
		if(!pInfo)
		{
			ASSERT(0);
		}
		pInfo->nReferences++;
		if(pInfo->pValue->type != CONSTANTVALUETYPE_INT)
			ASSERT(0);

		//this->pParser->MemFree(pArrayIndex->pIdentifier);
		pArrayIndex->index = pInfo->pValue->value.i;
		pArrayIndex->isIdentifier = false;
	}
}

void CCompilePreprocessor::EvalConstValue(SConstValue *pConstValue, EType &refOutType)
{
	EType typeLeft, typeRight;
	SConstValue *pLeft, *pRight;
	
	pLeft = pConstValue->value.binaryOp.pLeft;
	pRight = pConstValue->value.binaryOp.pRight;
	
	switch(pConstValue->type)
	{
	case CONSTANTVALUETYPE_BITWISEOR:
		{
			this->EvalConstValue(pLeft, typeLeft);
			this->EvalConstValue(pRight, typeRight);
			
			if(typeLeft != DAEDALUS_TYPE_INT)
				ASSERT(0);
			if(typeRight != DAEDALUS_TYPE_INT)
				ASSERT(0);
			
			refOutType = DAEDALUS_TYPE_INT;
			pConstValue->type = CONSTANTVALUETYPE_INT;
			pConstValue->value.i = pLeft->value.i | pRight->value.i;

			//this->pParser->MemFree(pLeft);
			//this->pParser->MemFree(pRight);
		}
		break;
	case CONSTANTVALUETYPE_DIVIDE:
		{
			this->EvalConstValue(pLeft, typeLeft);
			this->EvalConstValue(pRight, typeRight);
			
			if(typeLeft != DAEDALUS_TYPE_INT)
				ASSERT(0);
			if(typeRight != DAEDALUS_TYPE_INT)
				ASSERT(0);
			
			refOutType = DAEDALUS_TYPE_INT;
			pConstValue->type = CONSTANTVALUETYPE_INT;
			pConstValue->value.i = pLeft->value.i / pRight->value.i;

			//this->pParser->MemFree(pLeft);
			//this->pParser->MemFree(pRight);
		}
		break;
	case CONSTANTVALUETYPE_FLOAT:
		{
			refOutType = DAEDALUS_TYPE_FLOAT;
		}
		break;
	case CONSTANTVALUETYPE_IDENTIFIER:
		{
			SConstantInfo *pConstantInfo;
			SFunctionInfo *pFunctionInfo;

reprocess:;
			//pConstantInfo = this->GetConstantInfo(*pConstValue->value.pIdentifier);
			pConstantInfo = NULL;
			ASSERT(0);
			if(pConstantInfo)
			{
				pConstantInfo->nReferences++;
				
				ASSERT(!pConstantInfo->isArray);

				switch(pConstantInfo->pValue->type)
				{
				case CONSTANTVALUETYPE_INT:
					{
						//this->pParser->MemFree(pConstValue->value.pIdentifier);
						pConstValue->type = CONSTANTVALUETYPE_INT;
						pConstValue->value.i = pConstantInfo->pValue->value.i;
						refOutType = DAEDALUS_TYPE_INT;
					}
					break;
				case CONSTANTVALUETYPE_FLOAT:
					{
						//this->pParser->MemFree(pConstValue->value.pIdentifier);
						pConstValue->type = CONSTANTVALUETYPE_FLOAT;
						pConstValue->value.f = pConstantInfo->pValue->value.f;
						refOutType = DAEDALUS_TYPE_FLOAT;
					}
					break;
				case CONSTANTVALUETYPE_STRING:
					{
						pConstValue->type = CONSTANTVALUETYPE_STRING;
						*pConstValue->value.pString = *pConstantInfo->pValue->value.pString;
						refOutType = DAEDALUS_TYPE_STRING;
					}
					break;
				default:
					ASSERT(0);
				}

				break;
			}

			pFunctionInfo = this->GetFunctionInfo(*pConstValue->value.pIdentifier);
			if(pFunctionInfo)
			{
				pFunctionInfo->nReferences++;
				
				refOutType = DAEDALUS_TYPE_FUNC;
				pConstValue->type = CONSTANTVALUETYPE_FUNC;
				
				break;
			}

			if(this->ProcessUnprocessed(*pConstValue->value.pIdentifier))
			{
				goto reprocess;
			}
		}
		break;
	case CONSTANTVALUETYPE_INT:
		{
			refOutType = DAEDALUS_TYPE_INT;
		}
		break;
	case CONSTANTVALUETYPE_MULTIPLY:
		{
			this->EvalConstValue(pLeft, typeLeft);
			this->EvalConstValue(pRight, typeRight);
			
			if(typeLeft != DAEDALUS_TYPE_INT)
				ASSERT(0);
			if(typeRight != DAEDALUS_TYPE_INT)
				ASSERT(0);
			
			refOutType = DAEDALUS_TYPE_INT;
			pConstValue->type = CONSTANTVALUETYPE_INT;
			pConstValue->value.i = pLeft->value.i * pRight->value.i;

			//this->pParser->MemFree(pLeft);
			//this->pParser->MemFree(pRight);
		}
		break;
	case CONSTANTVALUETYPE_PLUS:
		{
			this->EvalConstValue(pLeft, typeLeft);
			this->EvalConstValue(pRight, typeRight);
			
			if(typeLeft != DAEDALUS_TYPE_INT)
				ASSERT(0);
			if(typeRight != DAEDALUS_TYPE_INT)
				ASSERT(0);
			
			refOutType = DAEDALUS_TYPE_INT;
			pConstValue->type = CONSTANTVALUETYPE_INT;
			pConstValue->value.i = pLeft->value.i + pRight->value.i;

			//this->pParser->MemFree(pLeft);
			//this->pParser->MemFree(pRight);
		}
		break;
	case CONSTANTVALUETYPE_SHIFTLEFT:
		{
			this->EvalConstValue(pLeft, typeLeft);
			this->EvalConstValue(pRight, typeRight);
			
			if(typeLeft != DAEDALUS_TYPE_INT)
				ASSERT(0);
			if(typeRight != DAEDALUS_TYPE_INT)
				ASSERT(0);
			
			refOutType = DAEDALUS_TYPE_INT;
			pConstValue->type = CONSTANTVALUETYPE_INT;
			pConstValue->value.i = pLeft->value.i << pRight->value.i;

			//this->pParser->MemFree(pLeft);
			//this->pParser->MemFree(pRight);
		}
		break;
	case CONSTANTVALUETYPE_STRING:
		{
			refOutType = DAEDALUS_TYPE_STRING;
		}
		break;
	default:
		ASSERT(0);
	}
}

bool CCompilePreprocessor::IsTypeConversionCorrect(EType from, EType to)
{
	if(from == DAEDALUS_TYPE_INT && to == DAEDALUS_TYPE_FLOAT)
		return true;
	if(from == DAEDALUS_TYPE_CLASS && to == DAEDALUS_TYPE_INSTANCE)
		return true;
	if(from == DAEDALUS_TYPE_INSTANCE && to == DAEDALUS_TYPE_CLASS)
		return true;
	
	return from == to;
}

void CCompilePreprocessor::Process(SCallArgs *pArgs, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	for(; pArgs; pArgs = pArgs->pNext)
	{
		this->Process(pArgs->pExpr, refLocalVariables, pClassInfo);
	}
}

void CCompilePreprocessor::Process(SElseIfs *pElseIfs, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	CMap<CString, SLocalVarInfo> nestedLocalVariables;

	if(!pElseIfs)
		return;
	
	nestedLocalVariables = refLocalVariables;
	
	if(pElseIfs->pCondition)
		this->Process(pElseIfs->pCondition, refLocalVariables, pClassInfo);
	this->Process(pElseIfs->pNestedStatements, nestedLocalVariables, pClassInfo);
	this->Process(pElseIfs->pNext, refLocalVariables, pClassInfo);
}

EType CCompilePreprocessor::Process(SExpression *pExpr, const SJCLib::CMap<SJCLib::CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	EType left, right;
	
	switch(pExpr->type)
	{
	case EXPRESSIONTYPE_BITWISEAND:
	case EXPRESSIONTYPE_BITWISEOR:
	case EXPRESSIONTYPE_DIVIDE:
	case EXPRESSIONTYPE_EQUALS:
	case EXPRESSIONTYPE_GREATEROREQUAL:
	case EXPRESSIONTYPE_GREATERTHAN:
	case EXPRESSIONTYPE_LESSOREQUAL:
	case EXPRESSIONTYPE_LESSTHAN:
	case EXPRESSIONTYPE_LOGICALAND:
	case EXPRESSIONTYPE_LOGICALOR:
	case EXPRESSIONTYPE_MINUS:
	case EXPRESSIONTYPE_MULTIPLY:
	case EXPRESSIONTYPE_NOTEQUALS:
	case EXPRESSIONTYPE_PLUS:
		{
			left = this->Process(pExpr->value.binaryOp.pLeft, refLocalVariables, pClassInfo);
			right = this->Process(pExpr->value.binaryOp.pRight, refLocalVariables, pClassInfo);

			ASSERT(left == right);

			return left;
		}
		break;
	case EXPRESSIONTYPE_CALL:
		{
			return this->ProcessCall(*pExpr->value.call.pIdentifier, pExpr->value.call.pCallArgs, refLocalVariables, pClassInfo);
		}
		break;
	case EXPRESSIONTYPE_CONSTVALUE:
		{
			this->EvalConstValue(pExpr->value.pConstValue, left);

			return left;
		}
		break;
	case EXPRESSIONTYPE_LEFTVALUE:
		{
			return this->Process(pExpr->value.pLeftValue, refLocalVariables, pClassInfo);
		}
		break;
	case EXPRESSIONTYPE_NEGATE:
		{
			return this->Process(pExpr->value.pSubExpression, refLocalVariables, pClassInfo);
		}
		break;
	}

	ASSERT(0);
	return DAEDALUS_TYPE_VOID;
}

EType CCompilePreprocessor::Process(SLeftValue *pLeftValue, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	EType retType;

	switch(pLeftValue->type)
	{
	case LEFTVALUETYPE_ARRAY:
		{
			retType = this->CheckIdentifier(*pLeftValue->pIdentifier, refLocalVariables, pClassInfo);
			this->EvalArrayIndex(pLeftValue->pArrayIndex);
		}
		break;
	case LEFTVALUETYPE_IDENTIFIER:
		{
			retType = this->CheckIdentifier(*pLeftValue->pIdentifier, refLocalVariables, pClassInfo);
		}
		break;
	case LEFTVALUETYPE_MEMBER:
		{
			retType = this->CheckMemberIdentifier(*pLeftValue->pIdentifier, *pLeftValue->pMemberIdentifier, refLocalVariables, pClassInfo);
		}
		break;
	case LEFTVALUETYPE_MEMBERARRAY:
		{
			retType = this->CheckMemberIdentifier(*pLeftValue->pIdentifier, *pLeftValue->pMemberIdentifier, refLocalVariables, pClassInfo);
			this->EvalArrayIndex(pLeftValue->pArrayIndex);
		}
		break;
	}

	return retType;
}

void CCompilePreprocessor::Process(SVariables *pVariables)
{
	SNames *pNames;
	SVariable *pVariable;
	SVariables *pNew, *pCurrent;
	SType *pType;
	
	for(; pVariables; pVariables = pVariables->pNext)
	{
		if(pVariables->pVariable->pType->isArray)
		{
			this->EvalArrayIndex(pVariables->pVariable->pArraySize);
			pVariables->pVariable->pType->nArrayElements = pVariables->pVariable->pArraySize->index;
			//this->pParser->MemFree(pVariables->pVariable->pArraySize);
			
			continue; //array has no multi name
		}

		if(pVariables->pVariable->pNames->pNext)
		{
			pCurrent = pVariables;
			for(pNames = pCurrent->pVariable->pNames->pNext; pNames; pNames = pNames->pNext)
			{
				//pNew = (SVariables *)this->pParser->MemAlloc(sizeof(*pNew));
				//pVariable = (SVariable *)this->pParser->MemAlloc(sizeof(*pVariable));
				//pType = (SType *)this->pParser->MemAlloc(sizeof(*pType));
				pVariable = NULL;
				pType = NULL;
				pNames->pName = NULL;
				pNew = NULL;
				ASSERT(0);
				
				pVariable->pName = pNames->pName;
				pVariable->pType = pType;
				*pType = *pCurrent->pVariable->pType;

				pNew->pVariable = pVariable;
				pNew->pNext = pVariables->pNext;
				pVariables->pNext = pNew;

				pVariables = pVariables->pNext; //go to next variable
			}
			pCurrent->pVariable->pName = pCurrent->pVariable->pNames->pName;
			pCurrent->pVariable->pNames = NULL;
		}
		else
		{
			pVariables->pVariable->pName = pVariables->pVariable->pNames->pName;
		}
	}
}

void CCompilePreprocessor::Process(SStatement *pStatement, CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	switch(pStatement->type)
	{
	case STATEMENTTYPE_ASSIGNEXPR:
	case STATEMENTTYPE_PLUSASSIGNEXPR:
		{
			this->Process(pStatement->value.assign.pExpr, refLocalVariables, pClassInfo);
			this->Process(pStatement->value.assign.pLeftValue, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_CALL:
		{
			this->ProcessCall(*pStatement->value.call.pFunctionName, pStatement->value.call.pArgs, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_DECLARATION:
		{
			SLocalVarInfo varInfo;

			varInfo.pIdentifier = pStatement->value.decl.pIdentifier;
			varInfo.pType = pStatement->value.decl.pType;

			if(pStatement->value.decl.pType->type == DAEDALUS_TYPE_CLASS)
			{
				this->CheckIdentifier(*pStatement->value.decl.pType->pIdentifier, refLocalVariables, NULL);
			}
			
			refLocalVariables.Insert(pStatement->value.decl.pIdentifier->ToLowercase(), varInfo);
		}
		break;
	case STATEMENTTYPE_IF:
		{
			SElseIfs elseIf;

			elseIf.pCondition = pStatement->value.ifStm.pConditionExpr;
			elseIf.pNestedStatements = pStatement->value.ifStm.pNestedStatements;
			elseIf.pNext = pStatement->value.ifStm.pElseIfs;

			this->Process(&elseIf, refLocalVariables, pClassInfo);
		}
		break;
	case STATEMENTTYPE_RETURNEXPR:
		{
			this->Process(pStatement->value.pExpr, refLocalVariables, pClassInfo);
		}
		break;
	}
}

void CCompilePreprocessor::Process(SStatements *pStatements, CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	for(; pStatements; pStatements = pStatements->pNext)
	{
		if(!pStatements->pStatement)
			continue;
		
		this->Process(pStatements->pStatement, refLocalVariables, pClassInfo);
	}
}

EType CCompilePreprocessor::ProcessCall(CString &refFuncName, SCallArgs *pArgs, const CMap<CString, SLocalVarInfo> &refLocalVariables, const SClassInfo *pClassInfo)
{
	bool isExternal;
	uint32 index;
	EType type;
	
	this->CheckIdentifier(refFuncName, isExternal, refLocalVariables, pClassInfo);
	
	index = 0;
	for(; pArgs; pArgs = pArgs->pNext)
	{
		type = this->Process(pArgs->pExpr, refLocalVariables, pClassInfo);
		if(isExternal)
		{
			const SSymbol &refArgSymbol = GetExternals()[refFuncName].args[index];
			
			if(!this->IsTypeConversionCorrect(type, refArgSymbol.type))
			{
				ASSERT(0);
			}
		}
		index++;
	}

	if(isExternal)
	{
		return (EType)GetExternals()[refFuncName].external.offSizeRet;
	}
	return this->GetFunctionInfo(refFuncName)->pFunction->returnType;
}

void CCompilePreprocessor::ProcessFunction(SGlobals *pGlobal)
{
	SArguments *pArgs;
	SFunction *pFunction;
	SFunctionInfo info;
	SLocalVarInfo varInfo;
	CMap<CString, SLocalVarInfo> localVariables;
	
	pFunction = pGlobal->value.pFunction;

	ASSERT(!this->IsFunctionDefined(*pFunction->pName));

	info.nReferences = 0;
	info.pName = pFunction->pName;
	info.pFunction = pFunction;
	
	//this->unprocessedFunctions.Delete(pFunction->pName->ToLowercase());
	ASSERT(0);
	this->functionInfoMap.Insert(pFunction->pName->ToLowercase(), info);

	for(pArgs = pFunction->pArguments; pArgs; pArgs = pArgs->pNext)
	{
		if(pArgs->pType->type == DAEDALUS_TYPE_CLASS)
			this->CheckIdentifier(*pArgs->pType->pIdentifier, localVariables, NULL);
		
		varInfo.pIdentifier = pArgs->pIdentifier;
		varInfo.pType = pArgs->pType;
		
		localVariables.Insert(pArgs->pIdentifier->ToLowercase(), varInfo);
	}

	this->Process(pFunction->pStatements, localVariables);

	this->AddGlobal(pGlobal);

	//stdOut << "Unprocessed functions left: " << this->unprocessedFunctions.GetNoOfElements() << endl;
}

void CCompilePreprocessor::ProcessInstance(SGlobals *pGlobal)
{
	SNames *pNames, *pNewNames;
	SInstance *pInstance, *pNewInstance;
	SGlobals *pNewGlobal;
	SClassInfo *pClassInfo;
	SPrototypeInfo *pProtoInfo;
	SInstanceInfo info;
	CArray<SGlobals *> newGlobals;
	CMap<CString, SLocalVarInfo> localVariables;
	
	pInstance = pGlobal->value.pInstance;
	
	info.nReferences = 0;
	info.pClassName = pInstance->pClassName;
	
	//Process names
	for(pNames = pInstance->pNames->pNext; pNames; pNames = pNames->pNext)
	{
		//pNewGlobal = (SGlobals *)this->pParser->MemAlloc(sizeof(*pNewGlobal));
		//pNewInstance = (SInstance *)this->pParser->MemAlloc(sizeof(*pNewInstance));
		///pNewNames = (SNames *)this->pParser->MemAlloc(sizeof(*pNewNames));
		pNewGlobal = NULL;
		pNewInstance = NULL;
		pNewNames = NULL;
		ASSERT(0);

		pNewGlobal->pNext = NULL;
		pNewGlobal->type = GLOBALTYPE_INSTANCE;
		pNewGlobal->value.pInstance = pNewInstance;
		
		pNewInstance->isGlobalInstance = pInstance->isGlobalInstance;
		pNewInstance->lineNumber = pInstance->lineNumber;
		pNewInstance->pClassName = pInstance->pClassName;
		pNewInstance->pFileName = pInstance->pFileName;
		pNewInstance->pNames = pNewNames;
		pNewInstance->pStatements = NULL; //hm... what is that here??!!!
		pNewInstance->pPrototypeName = pInstance->pPrototypeName;

		pNewNames->pName = pNames->pName;
		pNewNames->pNext = NULL;

		info.pName = pNewNames->pName;
		
		//this->unprocessedInstances.Delete(pNewNames->pName->ToLowercase());
		ASSERT(0);
		this->instanceInfoMap.Insert(pNewNames->pName->ToLowercase(), info);
		newGlobals.Push(pNewGlobal);
	}
	pInstance->pNames->pNext = NULL;

	info.pName = pInstance->pNames->pName;
	
	//this->unprocessedInstances.Delete(pInstance->pNames->pName->ToLowercase());
	ASSERT(0);
	this->instanceInfoMap.Insert(pInstance->pNames->pName->ToLowercase(), info);
	
	//Process base
reprocess:;
	pProtoInfo = this->GetPrototypeInfo(*pInstance->pClassName);
	if(pProtoInfo)
	{
		pProtoInfo->nReferences++;
		pClassInfo = this->GetClassInfo(*pProtoInfo->pClassName);

		pInstance->pPrototypeName = pProtoInfo->pName;
	}
	else
	{
		pClassInfo = this->GetClassInfo(*pInstance->pClassName);
		if(pClassInfo)
		{
			pClassInfo->nReferences++;
		}
		else
		{
			//haven't processed the base...
			bool ret = this->ProcessUnprocessed(*pInstance->pClassName);
			if(!ret)
			{
				ASSERT(0);
			}
			goto reprocess;
		}
	}

	*pInstance->pClassName = *pClassInfo->pName; //overwrite name to avoid case problems
	
	this->Process(pInstance->pStatements, localVariables, pClassInfo);

	foreach(it, newGlobals)
	{
		this->AddGlobal(it.GetValue());
	}
	this->AddGlobal(pGlobal);

	//stdOut << "Unprocessed instances left: " << this->unprocessedInstances.GetNoOfElements() << endl;
}

void CCompilePreprocessor::ProcessPrototype(SGlobals *pGlobal)
{
	SPrototype *pPrototype;
	SClassInfo *pClassInfo;
	SPrototypeInfo info;
	CMap<CString, SLocalVarInfo> localVariables;
	
	pPrototype = pGlobal->value.pPrototype;
	
	ASSERT(!this->IsPrototypeDefined(*pPrototype->pName));
	pClassInfo = this->GetClassInfo(*pPrototype->pClassName);
	ASSERT(pClassInfo);
	if(pClassInfo)
	{
		pClassInfo->nReferences++;
	}

	info.nReferences = 0;
	info.pName = pPrototype->pName;
	info.pClassName = pPrototype->pClassName;

	this->prototypeInfoMap.Insert(pPrototype->pName->ToLowercase(), info);
	
	*pPrototype->pClassName = *pClassInfo->pName; //overwrite name to avoid case problems
	
	this->Process(pPrototype->pStatements, localVariables, pClassInfo);
	
	this->AddGlobal(pGlobal);
}

void CCompilePreprocessor::ProcessVariable(SGlobals *pGlobal)
{
	SGlobals *pNewGlobal;
	SVariable *pVariable, *pNewVariable;
	SVariableInfo info;
	
	pVariable = pGlobal->value.pVariable;

	info.nReferences = 0;
	info.pType = pVariable->pType;
	
	if(pVariable->pType->isArray)
	{
		this->EvalArrayIndex(pVariable->pArraySize);
		pVariable->pType->nArrayElements = pVariable->pArraySize->index;
		
		info.pName = pVariable->pName;

		//this->globalVarInfoMap.Insert(pVariable->pName->ToLowercase(), info);
		ASSERT(0);
		this->AddGlobal(pGlobal);
		//this->unprocessedVariables.Delete(pVariable->pName->ToLowercase());
		ASSERT(0);
	}
	else
	{
		SNames *pNames;

		for(pNames = pVariable->pNames->pNext; pNames; pNames = pNames->pNext)
		{
			//pNewGlobal = (SGlobals *)this->pParser->MemAlloc(sizeof(*pNewGlobal));
			//pNewVariable = (SVariable *)this->pParser->MemAlloc(sizeof(*pNewVariable));
			pNewGlobal = NULL;
			pNewVariable = NULL;
			ASSERT(0);

			pNewGlobal->type = GLOBALTYPE_VARIABLE;
			pNewGlobal->pNext = NULL;
			pNewGlobal->value.pVariable = pNewVariable;

			pNewVariable->pName = pNames->pName;
			pNewVariable->pType = pVariable->pType;

			info.pName = pNames->pName;

			//this->globalVarInfoMap.Insert(pNames->pName->ToLowercase(), info);
			ASSERT(0);
			this->AddGlobal(pNewGlobal);
			//this->unprocessedVariables.Delete(pNames->pName->ToLowercase());
			ASSERT(0);
		}
		pVariable->pName = pVariable->pNames->pName;

		info.pName = pVariable->pName;

		if(pVariable->pType->type == DAEDALUS_TYPE_CLASS)
		{
			this->CheckIdentifier(*pVariable->pType->pIdentifier, CMap<CString, SLocalVarInfo>(), NULL);
		}

		//this->globalVarInfoMap.Insert(pVariable->pName->ToLowercase(), info);
		ASSERT(0);
		this->AddGlobal(pGlobal);
		//this->unprocessedVariables.Delete(pVariable->pName->ToLowercase());
		ASSERT(0);
	}
}

bool CCompilePreprocessor::ProcessUnprocessed(const CString &refIdentifier)
{
	//Might be a prototype, check this early cause should take few time
	/*foreach(it, this->unprocessedPrototypes)
	{
		if(it.GetValue()->value.pPrototype->pName->ToLowercase() == refIdentifier.ToLowercase())
		{
			pGlobal = it.GetValue();
			this->unprocessedPrototypes.Delete(it.GetIndex());
			this->ProcessPrototype(pGlobal);
			
			return true;
		}
	}

	//Might be a class
	auto &refItClass = this->unprocessedClasses.Find(refIdentifier.ToLowercase());
	if(refItClass.IsValid())
	{
		pGlobal = refItClass.GetValue();
		this->ProcessClass(pGlobal);

		return true;
	}

	//Might be a function
	auto &refItFunc =  this->unprocessedFunctions.Find(refIdentifier.ToLowercase());
	if(refItFunc.IsValid())
	{
		pGlobal = refItFunc.GetValue();
		this->ProcessFunction(pGlobal);
		
		return true;
	}

	//Might be an instance
	auto &refItInstance = this->unprocessedInstances.Find(refIdentifier.ToLowercase());
	if(refItInstance.IsValid())
	{
		pGlobal = refItInstance.GetValue();
		this->ProcessInstance(pGlobal);
		
		return true;
	}

	//Might be a variable
	auto &refItVar = this->unprocessedVariables.Find(refIdentifier.ToLowercase());
	if(refItVar.IsValid())
	{
		this->ProcessVariable(refItVar.GetValue());

		return true;
	}* /
	ASSERT(0);
	
	return false;
}

//Public Functions
bool CCompilePreprocessor::EvalExpression(SExpression &refExpr, UValue &refOutValue)
{
	switch(refExpr.type)
	{
	case EXPRESSIONTYPE_CONSTVALUE:
		{
			switch(refExpr.value.pConstValue->type)
			{
			case CONSTANTVALUETYPE_INT:
				refOutValue.i = refExpr.value.pConstValue->value.i;
				break;
			default:
				ASSERT(0);
			}

			return true;
		}
		break;
	case EXPRESSIONTYPE_LEFTVALUE:
		return this->EvalLeftValue(*refExpr.value.pLeftValue, refOutValue);
		break;
	case EXPRESSIONTYPE_MINUS:
		{
			if(this->EvalExpression(*refExpr.value.pSubExpression, refOutValue))
			{
				refOutValue.i = -refOutValue.i;
				return true;
			}
		}
		break;
	default:
		ASSERT(0);
	}

	return false;
}

bool CCompilePreprocessor::EvalLeftValue(SLeftValue &refLeftValue, UValue &refOutValue)
{
	SConstantInfo *pConstInfo;

	switch(refLeftValue.type)
	{
	case LEFTVALUETYPE_IDENTIFIER:
		{
			//Might be a constant
			//pConstInfo = this->GetConstantInfo(*refLeftValue.pIdentifier);
			pConstInfo = NULL;
			ASSERT(0);
			
			if(pConstInfo)
			{
				ASSERT(!pConstInfo->isArray);
				switch(pConstInfo->pValue->type)
				{
				case CONSTANTVALUETYPE_INT:
					refOutValue.i = pConstInfo->pValue->value.i;
					return true;
				default:
					ASSERT(0);
				}
			}
		}
		break;
	default:
		ASSERT(0);
	}

	return false;
}

SClassInfo *CCompilePreprocessor::GetClassInfo(const CString &refIdentifier)
{
	/*auto it = this->classInfoMap.Find(refIdentifier.ToLowercase());
	
	if(it.IsValid())
	{
		return &it.GetValue();
	}* /
	ASSERT(0);
	
	return NULL;
}

SFunctionInfo *CCompilePreprocessor::GetFunctionInfo(const CString &refIdentifier)
{
	auto it = this->functionInfoMap.Find(refIdentifier.ToLowercase());
	
	if(it.IsValid())
	{
		return &it.GetValue();
	}
	
	return NULL;
}

SInstanceInfo *CCompilePreprocessor::GetInstanceInfo(const CString &refIdentifier)
{
	auto it = this->instanceInfoMap.Find(refIdentifier.ToLowercase());
	
	if(it.IsValid())
	{
		return &it.GetValue();
	}
	
	return NULL;
}

SPrototypeInfo *CCompilePreprocessor::GetPrototypeInfo(const CString &refIdentifier)
{
	auto it = this->prototypeInfoMap.Find(refIdentifier.ToLowercase());
	
	if(it.IsValid())
	{
		return &it.GetValue();
	}
	
	return NULL;
}

SVariableInfo *CCompilePreprocessor::GetGlobalVariableInfo(const CString &refIdentifier)
{
	/*auto it = this->globalVarInfoMap.Find(refIdentifier.ToLowercase());
	
	if(it.IsValid())
	{
		return &it.GetValue();
	}* /
	ASSERT(0);
	
	return NULL;
}*/