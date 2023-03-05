//Main Header
#include "ZEN.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;

enum EZENType
{
	ZENTYPE_ILLEGAL,
	ZENTYPE_BINARY_SAFE,
};

//Local Functions
static EZENType ReadTags(ASeekableInputStream &refInputStream)
{
	EZENType type;
	CString line;
	
	type = ZENTYPE_ILLEGAL;
	
	while(!refInputStream.HitEnd())
	{
		line = refInputStream.ReadString('\n');
		
		if(line == "BIN_SAFE")
			type = ZENTYPE_BINARY_SAFE;
		
		if(line == "END")
			return type;
	}
	
	return ZENTYPE_ILLEGAL;
}

//Namespace Functions
void SJCPBLib::ReadZen(CWorld *pWorld, ASeekableInputStream &refInputStream)
{
	switch(ReadTags(refInputStream))
	{
	case ZENTYPE_BINARY_SAFE:
		{
			CZENBinarySafe &refReader = CZENBinarySafe(pWorld, refInputStream);
			
			refReader.Read();
		}
		break;
	}
}