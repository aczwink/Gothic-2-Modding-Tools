//Class Header
#include "ASymbol.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;

//Private methods
const CString &ASymbol::GetData(uint16 index) const
{
	static SJCLib::CString emptyString;
	
	return emptyString;
}

//Protected methods
void ASymbol::WriteSymbol(AOutputStream &refOutput, const CString &refName, uint32 offSizeRet, uint16 nEntries, EType type, uint8 flags, uint32 programOffset, uint32 parentSymbolIndex) const
{
	uint16 i;
	
	if(refName.GetC_Str())
	{
		refOutput.WriteUInt32(1);
		refOutput.WriteString(refName.ToUppercase());
		refOutput.WriteByte('\n');
	}
	else
	{
		refOutput.WriteUInt32(0);
	}
	
	refOutput.WriteUInt32(offSizeRet);
	refOutput.WriteByte(nEntries & 0xFF);
	refOutput.WriteByte(((nEntries >> 8) & 0xF) | (type << 4));
	
	refOutput.WriteByte(flags);
	refOutput.WriteByte(0); //reserved
	refOutput.WriteUInt32(0); //fileIndex
	refOutput.WriteUInt32(0); //lineStart
	refOutput.WriteUInt32(0); //lineCount
	refOutput.WriteUInt32(0); //charStart
	refOutput.WriteUInt32(0); //charCount
	
	if(!(flags & DAEDALUS_BINARY_PROPERTYFLAGS_CLASSVAR))
	{
		switch(type)
		{
		case DAEDALUS_TYPE_FLOAT:
			{
				for(i = 0; i < nEntries; i++)
				{
					refOutput.WriteFloat32(0);
				}
			}
			break;
		case DAEDALUS_TYPE_INT:
			{
				for(i = 0; i < nEntries; i++)
				{
					refOutput.WriteInt32(0);
				}
			}
			break;
		case DAEDALUS_TYPE_STRING:
			{
				for(i = 0; i < nEntries; i++)
				{
					refOutput.WriteString(this->GetData(i));
					refOutput.WriteByte('\n');
				}
			}
			break;
		case DAEDALUS_TYPE_CLASS:
			{
				refOutput.WriteUInt32(0); //hm... the classOffset is always 0?
			}
			break;
		case DAEDALUS_TYPE_FUNC:
		case DAEDALUS_TYPE_PROTOTYPE:
		case DAEDALUS_TYPE_INSTANCE:
			{
				refOutput.WriteUInt32(programOffset);
			}
			break;
		}
	}
	
	refOutput.WriteUInt32(parentSymbolIndex);
}