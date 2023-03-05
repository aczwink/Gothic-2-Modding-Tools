#pragma once
//Libs
#include <SJCLib.h>

class CProgramBuffer : public SJCLib::AInputStream, public SJCLib::ASeekableOutputStream
{
private:
	//Members
	byte *pBuffer;
	uint32 bufferSize;
	byte *pCurrentRead;
	byte *pCurrentWrite;
	//Methods
	void Resize(uint32 additionalSize);
public:
	//Constructor
	CProgramBuffer();
	//Destructor
	~CProgramBuffer();
	//Methods
	void Close();
	void Flush();
	uint32 GetCurrentOffset() const;
	uint32 GetRemainingBytes() const;
	bool HitEnd() const;
	byte ReadByte();
	uint32 ReadBytes(void *pDestination, uint32 count);
	void SetCurrentOffset(uint64 offset);
	void Skip(uint32 nBytes);
	void WriteAt(uint32 offset, uint32 value);
	void WriteByte(byte b);
	uint32 WriteBytes(const void *pSource, uint32 count);
};