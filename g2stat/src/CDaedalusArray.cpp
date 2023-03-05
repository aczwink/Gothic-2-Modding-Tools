/*//Class Header
#include "CDaedalusArray.h"
//Global
#include <iostream>
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

//Constructor
CDaedalusArray::CDaedalusArray(EType type, uint32 nElements)
{
	this->type = type;
	this->nElements = nElements;
	this->pValues = (UValue *)malloc(nElements * sizeof(*this->pValues));
	MemZero(this->pValues, nElements * sizeof(*this->pValues));
}

//Destructor
CDaedalusArray::~CDaedalusArray()
{
	this->Release();
}

//Operators
UValue &CDaedalusArray::operator[](uint32 index)
{
	return this->pValues[index];
}

//Public Functions
void CDaedalusArray::Release()
{
	if(this->type == TYPE_STRING)
	{
		repeat(this->nElements, i)
		{
			HeapDeleteSafe(this->pValues[i].pString);
		}
	}
	
	free(this->pValues);
}

CString CDaedalusArray::ToString() const
{
	CString result;
	SType type;

	result = '{';

	type.isArray = false;
	type.nArrayElements = 0;
	type.pIdentifier = NULL;
	type.type = this->type;
	
	repeat(this->nElements, i)
	{
		result += ::ToString(this->pValues[i], type) + ", ";
	}
	if(result.GetLength() >= 3)
		result = result.SubString(0, result.GetLength()-2);
	
	return result + '}';
}*/