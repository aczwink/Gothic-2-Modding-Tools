/*//Class Header
#include "CDaedalusCompiler.h"
//Global
#include <iostream>
//SJCWinLib
#include <SJCWinLib.h>
//Local
#include "CDaedalusArray.h"
#include "CDaedalusParser.h"
#include "CInstance.h"
#include "CVariable.h"
#include "CException.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
//Definitions
#define FILEPOS(x) (*(x)->pFileName + ":" + CString((x)->lineNumber))

//Constructor
CDaedalusCompiler::CDaedalusCompiler(const IDaedalusCallback *pCallback)
{
	this->compiledSuccessfully = false;
	this->pCallback = (IDaedalusCallback *)pCallback;
}

//Destructor
CDaedalusCompiler::~CDaedalusCompiler()
{
	this->Release();
}

//Private Functions
bool CDaedalusCompiler::Compile(SArrayIndex *pArrayIndex)
{
	ASSERT(0);
	//hm... brauch ich die noch?!
	ASSERT(pArrayIndex);

	if(pArrayIndex->isIdentifier)
	{
		ASSERT(this->definedConstants.Contains(*pArrayIndex->pIdentifier));
		
		//this->constants[this->definedConstants[*pArrayIndex->pIdentifier]].references++;
	}
	else
	{
		ASSERT(0);
	}
	
	return true;
}

void CDaedalusCompiler::Compile(SClass *pClass)
{
	CClass *pClassData;
	
	pClassData = new CClass(*pClass->pName, *pClass->pFilename, pClass->lineNumber);

	//Add to list first, so that it can be deleted if compiling variables fails
	this->classes.Insert(*pClass->pName, pClassData);
	this->classesCaseMap.Insert(pClassData->GetName().ToLowercase(), pClassData->GetName());
	
	this->Compile(pClass->pVariables, *pClassData);
}

bool CDaedalusCompiler::Compile(SConstant *pConstant)
{
	uint32 index;
	EType type;
	UValue value;
	CConstant *pConst;

	pConst = new CConstant(*pConstant->pType, *pConstant->pName, *pConstant->pFilename, pConstant->lineNumber);
	
	if(pConstant->isArray)
	{
		uint32 nElements, i;
		EType currentType;
		UValue currentValue;
		SConstValues *pConstValues;

		if(!this->EvalArrayIndex(pConstant->pNArrayElements, nElements))
			return false;
		value.pArray = new CDaedalusArray(pConst->type.type, nElements);
		
		pConstValues = pConstant->pArray;
		i = 0;
		while(pConstValues)
		{
			if(!this->EvalConstValue(pConstValues->pValue, currentType, currentValue))
			{
				delete value.pArray;
				return false;
			}
			if(!this->IsTypeConversionCorrect(currentType, pConst->type.type))
			{
				delete value.pArray;
				return false;
			}

			(*value.pArray)[i++] = currentValue;
			pConstValues = pConstValues->pNext;
		}

		pConst->type.isArray = true;
		pConst->type.nArrayElements = nElements;
	}
	else
	{
		if(!this->EvalConstValue(pConstant->pValue, type, value))
			return false;
		
		if(!this->IsTypeConversionCorrect(type, pConstant->pType->type))
		{
			ASSERT(0);
		}
		if(type == TYPE_INT && pConstant->pType->type == TYPE_FLOAT)
		{
			value.f = (float)value.i;
		}
	}
	pConst->value = value;
	
	index = this->constants.Push(pConst);	
	this->definedConstants.Insert(*pConstant->pName, index);
	this->constantsCaseMap.Insert(pConstant->pName->ToLowercase(), *pConstant->pName);
	
	return true;
}

bool CDaedalusCompiler::Compile(SConstValue *pConstValue, EType &refOutType)
{
	uint32 index;
	CConstant *pConstant;
	SType type;
	
	if(!pConstValue)
		return false;

	type.isArray = false;
	type.nArrayElements = 0;
	type.pIdentifier = NULL;
	
	switch(pConstValue->type)
	{
	case CONSTANTVALUETYPE_FLOAT:
		{
			if(this->constantFloats.Contains(pConstValue->value.f))
			{
				index = this->constantFloats[pConstValue->value.f];
			}
			else
			{
				type.type = TYPE_FLOAT;
				pConstant = new CConstant(type, CString(), CString(), UINT32_MAX);
				pConstant->value.f = pConstValue->value.f;
				index = this->constants.Push(pConstant);

				this->constantFloats.Insert(pConstValue->value.f, index);
			}
		}
		break;
	case CONSTANTVALUETYPE_IDENTIFIER: //this must be a previously defined constant
		{
			if(!this->constantsCaseMap.Contains(*pConstValue->value.pIdentifier))
				return false;
			
			index = this->definedConstants[this->constantsCaseMap[*pConstValue->value.pIdentifier]];
			
			this->constants[index]->nReferences++;
		}
		break;
	case CONSTANTVALUETYPE_INT:
		{
			if(this->constantInts.Contains(pConstValue->value.i))
			{
				index = this->constantInts[pConstValue->value.i];
			}
			else
			{
				type.type = TYPE_INT;
				pConstant = new CConstant(type, CString(), CString(), UINT32_MAX);
				pConstant->value.i = pConstValue->value.i;
				index = this->constants.Push(pConstant);

				this->constantInts.Insert(pConstValue->value.i, index);
			}
		}
		break;
	case CONSTANTVALUETYPE_STRING:
		{
			auto it = this->constantStrings.Find(*pConstValue->value.pString);

			if(it.IsValid())
			{
				index = it.GetValue();
			}
			else
			{
				type.type = TYPE_STRING;
				pConstant = new CConstant(type, CString(), CString(), UINT32_MAX);
				pConstant->value.pString = new CString;
				*pConstant->value.pString = *pConstValue->value.pString;
				index = this->constants.Push(pConstant);

				this->constantStrings.Insert(*pConstValue->value.pString, index);
			}
		}
		break;
	default:
		ASSERT(0);
	}
	
	refOutType = this->constants[index]->type.type;
	
	//this->program.Push(OPCODE_LDC);
	this->program.Push(index);
	
	return true;
}

bool CDaedalusCompiler::Compile(SExpression *pExpr, CClass *pClassData, EType &refOutType)
{
	ASSERT(pExpr);

	switch(pExpr->type)
	{
	case EXPRESSIONTYPE_CONSTVALUE:
		{
			if(!this->Compile(pExpr->value.pConstValue, refOutType))
				return false;
		}
		break;
	case EXPRESSIONTYPE_LEFTVALUE:
		{
			if(!this->Compile(pExpr->value.pLeftValue, pClassData))
				return false;
		}
		break;
	case EXPRESSIONTYPE_UNARYMINUS:
		{
			EType subType;
			
			if(!this->Compile(pExpr->value.pSubExpression, pClassData, subType))
				return false;
			switch(subType)
			{
			case TYPE_FLOAT:
				{
					//some kind of fminus opcode here
				}
				break;
			default:
				ASSERT(0);
			}
		}
		break;
	default:
		ASSERT(0);
	}

	return true;
}

bool CDaedalusCompiler::Compile(SFunction *pFunction)
{
	CFunction *pFunc;
	int32 index;

	pFunc = new CFunction(pFunction->returnValue, *pFunction->pName, *pFunction->pFileName, pFunction->lineNumber);
	
	if(this->functions.Contains(*pFunction->pName))
	{
		stdOut << *pFunction->pName << endl;
		ASSERT(false);
	}
	
	index = this->uncompiledFunctions.Find(pFunction);
	if(index == -1)
	{
		ASSERT(false);
	}
	this->uncompiledFunctions.Delete(index);
	
	pFunc->programOffset = this->program.GetNoOfElements();

	if(!this->Compile(pFunction->pStatements, *pFunc))
	{
		ASSERT(false);
	}
	
	pFunc->nOpcodes = this->program.GetNoOfElements() - pFunc->programOffset;

	this->functions.Insert(*pFunction->pName, pFunc);
	
	return true;
}

bool CDaedalusCompiler::Compile(SInstance *pInst)
{
	uint32 offset, length;
	SNames *pNames;
	CInstance *pInstance;
	CClass *pClass;

	pClass = NULL;
	pNames = pInst->pNames;
	
	if(this->IsPrototypeDefined(*pInst->pClassName))
	{
		pClass = this->GetPrototype(*pInst->pClassName);
	}
	else if(this->IsClassDefined(*pInst->pClassName))
	{
		pClass = this->GetClass(*pInst->pClassName);
	}
	else
	{
		ASSERT(0);
	}

	pClass->nReferences++;

	offset = this->program.GetNoOfElements();
	this->CompileConstruct(pClass);
	this->Compile(pInst->pStatements, pClass);
	length = this->program.GetNoOfElements() - offset;
	
	while(pNames)
	{
		pInstance = new CInstance(*pNames->pName, pClass, *pInst->pFileName, pInst->lineNumber);

		pInstance->programOffset = offset;
		pInstance->nOpcodes = length;
		
		this->instances.Insert(pInstance->GetName(), pInstance);
		
		pNames = pNames->pNext;
	}
	
	return true;
}

bool CDaedalusCompiler::Compile(SLeftValue *pLeftValue, CClass *pClassData)
{
	ASSERT(pLeftValue);

	switch(pLeftValue->type)
	{
	case LEFTVALUETYPE_ARRAY:
		{
			if(pClassData) //check if we are in instance context
			{
				foreach(it, pClassData->variables)
				{
					ASSERT(0);
					/*if(it.GetValue().isArray && *it.GetValue().pName == *pLeftValue->pIdentifier)
					{
						uint32 index;

						//push 'this'
						this->program.Push(OPCODE_PUSH);
						this->program.Push(1); //BSP dependant
						this->program.Push(0); //this pointer lays at BSP
						
						//select the member
						this->program.Push(OPCODE_SELECT);
						this->program.Push(0); //SP dependant
						this->program.Push(0); //SP+0
						this->program.Push(it.GetIndex());

						//select the value
						this->program.Push(OPCODE_SELECT);
						this->program.Push(0); //SP dependant
						this->program.Push(0); //SP+0

						if(!this->EvalArrayIndex(pLeftValue->pArrayIndex, index))
							return false;

						this->program.Push(index);

						return true;
					}*/
/*				}
			}
		}
		break;
	case LEFTVALUETYPE_IDENTIFIER:
		{
			if(pClassData) //if we are in instance context
			{
				int32 index;

				index = pClassData->GetVariableIndex(*pLeftValue->pIdentifier);
				if(index != -1)
				{
					return true;
				}
			}

			auto it = this->constantsCaseMap.Find(pLeftValue->pIdentifier->ToLowercase());
			
			if(it.IsValid())
			{
				this->constants[this->definedConstants[it.GetValue()]]->nReferences++;
				
				//this->program.Push(OPCODE_LDC);
				this->program.Push(this->definedConstants[it.GetValue()]);

				return true;
			}
			
			//last chance... it is a function which gets defined later
			if(this->functionIndexMap.Contains(pLeftValue->pIdentifier->ToLowercase()))
			{
				return true;
			}
		}
		break;
		default:
		ASSERT(0);
	}

	return false;
}

void CDaedalusCompiler::Compile(SPrototype *pProto)
{
	CClass *pClass;
	CPrototype *pPrototype;

	if(!this->IsClassDefined(*pProto->pClassName))
	{
		ASSERT(0);
	}
	pClass = this->GetClass(*pProto->pClassName);
	
	pClass->nReferences++;
	
	pPrototype = new CPrototype(*pProto->pName, pClass, *pProto->pFileName, pProto->lineNumber);

	this->prototypes.Insert(pPrototype->GetName(), pPrototype);
	this->prototypesCaseMap.Insert(pPrototype->GetName().ToLowercase(), pPrototype->GetName());
}

bool CDaedalusCompiler::Compile(SStatement *pStatement, CClass *pClassData)
{
	ASSERT(pStatement);

	switch(pStatement->type)
	{
	case STATEMENTTYPE_ASSIGNEXPR:
		{
			if(!this->CompileAssignment(pStatement->value.assign.pLeftValue, pStatement->value.assign.pExpr, pClassData))
				return false;
		}
		break;
		default:
		ASSERT(0);
	}

	return true;
}

bool CDaedalusCompiler::Compile(SStatement *pStatement, CFunction &refFunction)
{
	if(pStatement)
	{
	}
	return true;
}

bool CDaedalusCompiler::Compile(SStatements *pStatements, CClass *pClassData)
{
	return true;
	while(pStatements)
	{
		if(!this->Compile(pStatements->pStatement, pClassData))
			return false;
		
		pStatements = pStatements->pNext;
	}

	return true;
}

bool CDaedalusCompiler::Compile(SStatements *pStatements, CFunction &refFunction)
{
	while(pStatements)
	{
		if(!this->Compile(pStatements->pStatement, refFunction))
			return false;
		
		pStatements = pStatements->pNext;
	}
	
	return true;
}

bool CDaedalusCompiler::Compile(SVariable *pVariable)
{
	uint32 nArrayElements;
	
	if(pVariable->isArray)
	{
		ASSERT(0);
		if(!this->EvalArrayIndex(pVariable->pArraySize, nArrayElements))
			return false;
	}
	else
	{
		ASSERT(0);
	}
	
	return true;
}

bool CDaedalusCompiler::Compile(SVariable *pVariable, CClass &refClassData)
{
	uint32 nArrayElements;
	CVariable *pVar;
	SType type;
	
	ASSERT(pVariable);
	
	if(pVariable->isArray)
	{
		if(!this->EvalArrayIndex(pVariable->pArraySize, nArrayElements))
		{
			this->pCallback->OnError(DAEDALUS_ERROR_COMPILE_ARRAYINDEX, FILEPOS(pVariable->pArraySize));
			throw Daedalus::CException();
		}
		
		type.type = pVariable->pType->type;
		type.isArray = true;
		type.nArrayElements = nArrayElements;
		type.pIdentifier = NULL;
		
		pVar = new CVariable(type, *pVariable->pName);
		refClassData.variables.Push(pVar);
	}
	else
	{
		SNames *pNames;

		pNames = pVariable->pNames;
		while(pNames)
		{
			pVar = new CVariable(*pVariable->pType, *pNames->pName);
			refClassData.variables.Push(pVar);

			pNames = pNames->pNext;
		}
	}
	
	return true;
}

bool CDaedalusCompiler::Compile(SVariables *pVariables, CClass &refClassData)
{
	while(pVariables)
	{
		if(!this->Compile(pVariables->pVariable, refClassData))
			return false;

		pVariables = pVariables->pNext;
	}

	return true;
}

bool CDaedalusCompiler::CompileAssignment(SLeftValue *pLeftValue, SExpression *pExpr, CClass *pClassData)
{
	EType rightSideType;
	
	ASSERT(pLeftValue);
	ASSERT(pExpr);
	
	if(!this->Compile(pExpr, pClassData, rightSideType))
		return false;

	switch(pLeftValue->type)
	{
	case LEFTVALUETYPE_ARRAY:
		{
			if(pClassData) //check if the array is a class variable
			{
				int32 index;
				uint32 arrayIndex;

				index = pClassData->GetVariableIndex(*pLeftValue->pIdentifier);
				if(index != -1)
				{
					//push 'this'
					//this->program.Push(OPCODE_PUSH);
					this->program.Push(1); //BSP dependant
					this->program.Push(0); //this pointer lays at BSP
					
					//select the member
					//this->program.Push(OPCODE_SELECT);
					this->program.Push(0); //SP dependant
					this->program.Push(0); //SP+0
					this->program.Push(index);
					
					//assign
					//this->program.Push(OPCODE_MOVEARRAY);
					this->program.Push(0); //both SP dependant
					this->program.Push(-2); //SP-2
					this->program.Push(0); //SP

					if(!this->EvalArrayIndex(pLeftValue->pArrayIndex, arrayIndex))
						return false;

					this->program.Push(arrayIndex);
					
					//this->program.Push(OPCODE_POP); //pop member
					//this->program.Push(OPCODE_POP); //pop 'this'
					//this->program.Push(OPCODE_POP); //pop right side
					
					return true;
				}
				
				return false;
			}
		}
		break;
	case LEFTVALUETYPE_IDENTIFIER:
		{
			if(pClassData) //check if we are in instance context
			{
				int32 index;
				
				index = pClassData->GetVariableIndex(*pLeftValue->pIdentifier);
				if(index != -1)
				{
					//push 'this'
					//this->program.Push(OPCODE_PUSH);
					this->program.Push(1); //BSP dependant
					this->program.Push(0); //this pointer lays at BSP
					
					//this->program.Push(OPCODE_MOVEARRAY);
					this->program.Push(0); //both SP dependant
					this->program.Push(-1); //SP-1
					this->program.Push(0); //SP
					this->program.Push(index); //index is offset of variable
					
					//this->program.Push(OPCODE_POP); //pop 'this'
					//this->program.Push(OPCODE_POP); //pop right side
					
					return true;
				}
				
				return false;
			}
		}
		break;
	default:
		ASSERT(0);
	}

	return true;
}

bool CDaedalusCompiler::CompileConstruct(CClass *pClass)
{
	//Create the object
	//this->program.Push(OPCODE_CREATEARRAY);
	this->program.Push(pClass->GetVariables().GetNoOfElements());

	foreach(it, pClass->GetVariables())
	{
		if(it.GetValue()->GetType().isArray)
		{
			//Create member arrays
			if(it.GetValue()->GetType().type == TYPE_STRING)
			{
				//this->program.Push(OPCODE_CREATESTRINGARRAY);
			}
			else
			{
				//this->program.Push(OPCODE_CREATEARRAY);
			}
			this->program.Push(it.GetValue()->GetType().nArrayElements);
		}
		else if(it.GetValue()->GetType().type == TYPE_STRING)
		{
			//this->program.Push(OPCODE_CREATESTRING);
		}
		else
		{
			continue;
		}
		
		//mova SP-1, SP, index
		//this->program.Push(OPCODE_MOVEARRAY);
		this->program.Push(0); //both are SP
		this->program.Push(-1);
		this->program.Push(0);
		this->program.Push(it.GetIndex());
		
		//this->program.Push(OPCODE_POP);
	}

	return true;
}

bool CDaedalusCompiler::EvalConstValue(SConstValue *pConstValue, EType &refOutType, UValue &refOutValue)
{
UValue leftVal, rightVal;
	
	ASSERT(pConstValue);

	switch(pConstValue->type)
	{
	case CONSTANTVALUETYPE_MULTIPLY:
		{
			if(!this->EvalConstValue(pConstValue->value.binaryOp.pLeft, typeLeft, leftVal))
				return false;
			if(!this->EvalConstValue(pConstValue->value.binaryOp.pRight, typeRight, rightVal))
				return false;
			if(typeLeft != TYPE_INT)
				ASSERT(0);
			if(typeRight != TYPE_INT)
				ASSERT(0);

			refOutType = TYPE_INT;
			refOutValue.i = leftVal.i * rightVal.i;
		}
		break;
	default:
		ASSERT(false);
	}
	return true;
}

bool CDaedalusCompiler::Preprocess(SGlobals *pGlobal)
{
	uint32 functionId;

	functionId = 0;
	while(pGlobal)
	{
		if(pGlobal->type == GLOBALTYPE_FUNCTION)
		{
			this->functionIndexMap.Insert(pGlobal->value.pFunction->pName->ToLowercase(), functionId++);
		}
		
		pGlobal = pGlobal->pNext;
	}

	return true;
}

//Public Functions
void CDaedalusCompiler::Compile(CString inputSrcFile, CDaedalusProgram &refOutProgram)
{

	//Compile!
	foreach(it, globalsToCompile)
	{
		switch(it.GetValue()->type)
		{
		case GLOBALTYPE_CLASS:
			{
				this->Compile(it.GetValue()->value.pClass);
				
				static int compiledClasses = 0;
				compiledClasses++;
				if(compiledClasses == 1000)
					goto asd;
			}
			break;
		case GLOBALTYPE_CONSTANT:
			{
				this->Compile(it.GetValue()->value.pConstant);
			}
			break;
		case GLOBALTYPE_INSTANCE:
			{
				this->Compile(it.GetValue()->value.pInstance);
				
				static int compiledInstances = 0;
				compiledInstances++;
				if(compiledInstances == 1)
					goto asd;
			}
			break;
		case GLOBALTYPE_VARIABLE:
			{
				//this->Compile(it.GetValue()->value.pVariable);
			}
			break;
		default:
			stdOut << it.GetValue()->type << endl;
			ASSERT(0);
		}
	}
	asd:;
	
	//Copy info to program
	//refOutProgram.pProgram = (Opcode *)malloc(sizeof(*refOutProgram.pProgram) * this->program.GetNoOfElements());
	repeat(this->program.GetNoOfElements(), i)
	{
		refOutProgram.pProgram[i] = this->program[i];
	}

	refOutProgram.pConstants = (UValue *)malloc(sizeof(*refOutProgram.pConstants) * this->constants.GetNoOfElements());
	foreach(it, this->constants)
	{
		refOutProgram.pConstants[it.GetIndex()] = it.GetValue()->value;
	}

	//Copy to program class
	refOutProgram.classes = this->classes;
	refOutProgram.constants = this->constants;
	refOutProgram.functions = this->functions;
	refOutProgram.instances = this->instances;
	refOutProgram.prototypes = this->prototypes;

	this->compiledSuccessfully = true;
	
	//Clean Up
	this->pCallback->OnCleanup();
	this->Release();
}

void CDaedalusCompiler::Release()
{
	this->constantFloats.Release();
	this->constantInts.Release();
	this->constantsCaseMap.Release();
	this->constantStrings.Release();
	this->definedConstants.Release();
	this->classesCaseMap.Release();
	this->functionIndexMap.Release();
	this->program.Release();
	this->uncompiledFunctions.Release();

	if(!this->compiledSuccessfully)
	{
		foreach(it, this->classes)
		{
			delete it.GetValue();
		}

		foreach(it, this->constants)
		{
			delete it.GetValue();
		}

		foreach(it, this->functions)
		{
			delete it.GetValue();
		}
		
		foreach(it, this->instances)
		{
			delete it.GetValue();
		}
		
		foreach(it, this->prototypes)
		{
			delete it.GetValue();
		}
	}
	
	this->classes.Release();
	this->constants.Release();
	this->functions.Release();
	this->instances.Release();
	this->prototypes.Release();
}*/