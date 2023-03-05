//Class Header
#include "CProgramBuffer.h"
//Global
#include <iostream>
//Namespaces
using namespace SJCLib;

//Constructor
CProgramBuffer::CProgramBuffer()
{
	this->bufferSize = 1024;
	this->pBuffer = (byte *)malloc(this->bufferSize);
	this->pCurrentRead = this->pBuffer;
	this->pCurrentWrite = this->pBuffer;
}

//Destructor
CProgramBuffer::~CProgramBuffer()
{
	this->Close();
}

//Private methods
void CProgramBuffer::Resize(uint32 additionalSize)
{
	uint32 offset, readOffset;

	offset = this->GetCurrentOffset();
	readOffset = (uint32)(this->pCurrentRead - this->pBuffer);

	if(this->bufferSize - offset < additionalSize)
	{
		this->bufferSize *= 2;
		this->pBuffer = (byte *)realloc(this->pBuffer, this->bufferSize);
		this->pCurrentRead = this->pBuffer + readOffset;
		this->pCurrentWrite = this->pBuffer + offset;
	}
}

//Public methods
void CProgramBuffer::Close()
{
	memfree(this->pBuffer);
	this->pBuffer = NULL;
	this->pCurrentRead = NULL;
	this->pCurrentWrite = NULL;
	this->bufferSize = 0;
}

void CProgramBuffer::Flush()
{
	//stream is always flushed
}

uint32 CProgramBuffer::GetCurrentOffset() const
{
	return (uint32)(this->pCurrentWrite - this->pBuffer);
}

uint32 CProgramBuffer::GetRemainingBytes() const
{
	return (uint32)(this->pCurrentWrite - this->pCurrentRead);
}

bool CProgramBuffer::HitEnd() const
{
	return this->pCurrentWrite <= this->pBuffer + this->bufferSize;
}

byte CProgramBuffer::ReadByte()
{
	return *this->pCurrentRead++;
}

uint32 CProgramBuffer::ReadBytes(void *pDestination, uint32 count)
{
	if(count > this->pCurrentWrite - this->pCurrentRead)
		count = (uint32)(this->pCurrentWrite - this->pCurrentRead);
	
	MemCopy(pDestination, this->pCurrentRead, count);
	this->pCurrentRead += count;
	return count;
}

void CProgramBuffer::SetCurrentOffset(uint64 offset)
{
	this->pCurrentWrite = this->pBuffer + offset;
}

void CProgramBuffer::Skip(uint32 nBytes)
{
	this->pCurrentRead += nBytes;
}

void CProgramBuffer::WriteAt(uint32 offset, uint32 value)
{
	MemCopy(this->pBuffer + offset, &value, sizeof(value));
}

void CProgramBuffer::WriteByte(byte b)
{
	this->Resize(1);

	*this->pCurrentWrite++ = b;
}

uint32 CProgramBuffer::WriteBytes(const void *pSource, uint32 count)
{
	this->Resize(count);
	MemCopy(this->pCurrentWrite, pSource, count);
	this->pCurrentWrite += count;

	return count;
}