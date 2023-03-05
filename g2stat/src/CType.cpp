//Class Header
#include "CType.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Constructor
CType::CType() : ANode(CWString(), 0)
{
}

CType::CType(const CType &refSource) : ANode(CWString(), 0)
{
	this->className = refSource.className;
	this->isArray = refSource.isArray;
	this->nElements = refSource.nElements;
	this->type = refSource.type;
}

CType::CType(EType type) : ANode(CWString(), 0)
{
	ASSERT(type != DAEDALUS_TYPE_INSTANCE);

	this->isArray = false;
	this->nElements = 1;
	this->type = type;
}

CType::CType(const CString &refClassName) : ANode(CWString(), 0)
{
	this->isArray = false;
	this->nElements = 1;
	this->type = DAEDALUS_TYPE_INSTANCE;
	this->className = refClassName;
}

//Public methods
uint32 CType::GetSize() const
{
	uint32 size;

	switch(this->type)
	{
	case DAEDALUS_TYPE_FLOAT:
	case DAEDALUS_TYPE_INT:
	case DAEDALUS_TYPE_FUNC:
		size = 4;
		break;
	case DAEDALUS_TYPE_STRING:
		size = 20;
		break;
	default:
		ASSERT(0);
	}

	return size * this->nElements;
}

bool CType::IsConvertableTo(const CType &refOther, bool &refNeedCast) const
{
	//implicit conversions

	//instance -> int
	if(this->type == DAEDALUS_TYPE_INSTANCE && refOther.type == DAEDALUS_TYPE_INT)
	{
		refNeedCast = true;
		return true;
	}

	//instance -> func
	//funcs and ints are treated equal. instance can be converted to int, which can be converted to func
	if(this->type == DAEDALUS_TYPE_INSTANCE && refOther.type == DAEDALUS_TYPE_FUNC)
	{
		refNeedCast = true;
		return true;
	}

	//int -> float
	if(this->type == DAEDALUS_TYPE_INT && refOther.type == DAEDALUS_TYPE_FLOAT)
	{
		refNeedCast = true;
		return true;
	}
	
	//type -> type[] is ok, it means type[0], or other way around (type[] -> type)
	refNeedCast = false;
	if(this->type == refOther.type && ((!this->isArray && refOther.isArray) || (this->isArray && !refOther.isArray)))
	{
		if(this->type == DAEDALUS_TYPE_INSTANCE)
			return this->className == refOther.className;
		return true;
	}
	
	//check for equality
	if(this->type == refOther.type && this->nElements == refOther.nElements)
	{
		if(this->type == DAEDALUS_TYPE_INSTANCE)
			return this->className.IsEmpty() || refOther.className.IsEmpty() || this->className == refOther.className;
		return true;
	}
	
	return false;
}

CString CType::ToString() const
{
	CString result;

	switch(this->type)
	{
	case DAEDALUS_TYPE_FLOAT:
		result = "float";
		break;
	case DAEDALUS_TYPE_INT:
		result = "int";
		break;
	case DAEDALUS_TYPE_STRING:
		result = "string";
		break;
	case DAEDALUS_TYPE_FUNC:
		result = "func";
		break;
	case DAEDALUS_TYPE_INSTANCE:
		result = this->className;
		break;
	default:
		ASSERTMSG(0, CString(this->type));
	}

	if(this->isArray)
	{
		result += '[' + CString(this->nElements) + ']';
	}
	
	return result;
}