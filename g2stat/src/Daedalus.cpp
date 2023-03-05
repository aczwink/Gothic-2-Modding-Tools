//Main Header
#include "Daedalus.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Namespace Functions
CString Daedalus::ValueToString(const SConstant &refConstant)
{
	CString result;

	if(refConstant.pType->isArray)
	{
		uint32 i;
		SConstValues *pValues;
		
		result = '{';
		pValues = refConstant.pArray;
		for(i = 0; i < refConstant.pNArrayElements->index; i++)
		{
			result += ValueToString(*pValues->pValue, refConstant.pType->type) + ", ";
			pValues = pValues->pNext;
		}

		return result.SubString(0, result.GetLength()-2) + '}';
	}
	
	return ValueToString(*refConstant.pValue, refConstant.pType->type);
}

CString Daedalus::ValueToString(const SConstValue &refConstValue, EType type)
{
	switch(type)
	{
	case DAEDALUS_TYPE_FLOAT:
		return CString(refConstValue.value.f);
	case DAEDALUS_TYPE_FUNC:
		return refConstValue.value.pIdentifier ? *refConstValue.value.pIdentifier : "NULL";
	case DAEDALUS_TYPE_INT:
		return CString(refConstValue.value.i);
	case DAEDALUS_TYPE_STRING:
		return '"' + *refConstValue.value.pString + '"';
	}

	ASSERT(0);
	return CString();
}

CString Daedalus::ToString(const SType &refType)
{
	CString result;
	
	switch(refType.type)
	{
	case DAEDALUS_TYPE_FLOAT:
		result = "float";
		break;
	case DAEDALUS_TYPE_FUNC:
		result = "func";
		break;
	case DAEDALUS_TYPE_INT:
		result = "int";
		break;
	case DAEDALUS_TYPE_STRING:
		result = "string";
		break;
	default:
		stdOut << refType.type << endl;
		ASSERT(0);
	}
	
	if(refType.isArray)
	{
		result += "[" + CString(refType.nArrayElements) + "]";
	}
	
	return result;
}

CString Daedalus::ToString(const SFunction &refFunc)
{
	SArguments *pArgs;
	CString result;
	
	switch(refFunc.returnType)
	{
	case DAEDALUS_TYPE_INT:
		result = "int";
		break;
	case DAEDALUS_TYPE_STRING:
		result = "string";
		break;
	case DAEDALUS_TYPE_VOID:
		result = "void";
		break;
	}

	result += " " + *refFunc.pName + "(";

	for(pArgs = refFunc.pArguments; pArgs; pArgs = pArgs->pNext)
	{
		const SType &refType = *pArgs->pType;

		if(refType.isArray)
		{
			ASSERT(0);
		}

		switch(refType.type)
		{
		case DAEDALUS_TYPE_FLOAT:
			result += "float";
			break;
		case DAEDALUS_TYPE_INT:
			result += "int";
			break;
		case DAEDALUS_TYPE_STRING:
			result += "string";
			break;
		case DAEDALUS_TYPE_CLASS:
			result += *refType.pIdentifier;
			break;
		default:
			ASSERT(0);
		}

		result += ' ' + *pArgs->pIdentifier + ", ";
	}

	if(refFunc.pArguments)
		result = result.SubString(0, result.GetLength()-2);
	
	return result + ");";
}