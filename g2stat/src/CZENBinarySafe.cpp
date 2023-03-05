//Class Header
#include "ZEN.h"
//Global
#include <iostream>
//Local
#include "CTriggerChangeLevel.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;

//Constructor
CZENBinarySafe::CZENBinarySafe(CWorld *pWorld, ASeekableInputStream &refInputStream) : refInputStream(refInputStream)
{
	this->pWorld = pWorld;
	this->pChilds = NULL;
}

//Destructor
CZENBinarySafe::~CZENBinarySafe()
{
	HeapDeleteArraySafe(this->pChilds);
}

//Private Functions
AVob *CZENBinarySafe::CreateVOB(const CString &refClassName)
{
	if(refClassName == "oCItem")
	{
		return new CItem;
	}
	else if(refClassName == "oCTriggerChangeLevel")
	{
		return new CTriggerChangeLevel;
	}

	return NULL;
}

void CZENBinarySafe::ParseObjectTag(const CString &refObjectTag, CString &refObjectName)
{
	uint32 startPos, endPos;

	//Read the object name
	startPos = 0;
reparse:;
	while(startPos < refObjectTag.GetLength() && (refObjectTag[startPos] != '§' && !isalpha(refObjectTag[startPos])))
		startPos++;
	endPos = startPos;
	while(endPos < refObjectTag.GetLength() && (refObjectTag[endPos] == '§' || isalpha(refObjectTag[endPos]) || refObjectTag[endPos] == '_'))
		endPos++;

	refObjectName = refObjectTag.SubString(startPos, endPos - startPos);

	if(refObjectName == "visual")
	{
		//this is only a modifier...
		startPos = ++endPos;
		while(endPos < refObjectTag.GetLength() && refObjectTag[endPos] != ' ')
			endPos++;
		refObjectName = refObjectTag.SubString(startPos, endPos - startPos);
	}
	else if(refObjectName == "waypoint" || refObjectName == "wayl" || refObjectName == "wayr")
	{
		//skip
		startPos = endPos+1;
		goto reparse;
	}
}

void CZENBinarySafe::ReadChilds()
{
	uint16 keyLength, index;
	uint32 nEntries, i, value;
	
	this->refInputStream.ReadUInt32(nEntries);
	this->pChilds = new SChildEntry[nEntries];
	
	for(i = 0; i < nEntries; i++)
	{
		this->refInputStream.ReadUInt16(keyLength);
		this->refInputStream.ReadUInt16(index);
		this->refInputStream.ReadUInt32(value);
		
		this->pChilds[index].name = this->refInputStream.ReadString((uint32)keyLength);
	}
}

CZENBinarySafe::EChunkType CZENBinarySafe::ReadChunkTags()
{
	EChunkType type;
	CString line;

	type = CHUNKTYPE_ILLEGAL;
	
	while(!this->refInputStream.HitEnd())
	{
		line = this->refInputStream.ReadString((char)0xA);

		if(line == "BINARY")
			type = CHUNKTYPE_BINARY;
		
		if(line.IsEmpty())
			return type;
	}
	return CHUNKTYPE_ILLEGAL;
}

bool CZENBinarySafe::ReadCodedBool()
{
	int32 value;

	ASSERT(this->refInputStream.ReadByte() == CODETYPE_BOOL);
	this->refInputStream.ReadInt32(value);
	ASSERT(value == 0 || value == 1 || value == -1);

	return value != 0;
}

int32 CZENBinarySafe::ReadCodedInt()
{
	int32 value;

	ASSERT(this->refInputStream.ReadByte() == CODETYPE_INT);

	this->refInputStream.ReadInt32(value);
	
	return value;
}

void CZENBinarySafe::ReadCodedVector3()
{
	ASSERT(this->refInputStream.ReadByte() == CODETYPE_VECTOR3);
	this->refInputStream.Skip(12);
}

void CZENBinarySafe::ReadMeshAndBsp()
{
	uint32 chunkSize;

	this->refInputStream.Skip(4);
	this->refInputStream.ReadUInt32(chunkSize); //size of the rest of the chunk (after this size field)

	/*
	mesh data: (full data in "krximpexp")
	
	this->refInputStream.Skip(119); //unknown data
	this->pInput->ReadUInt32(materialPoolSize); //size of the materials section
	ASSERT(this->ReadChunkTags() == CHUNKTYPE_BINARY);
	this->pInput->ReadUInt32(nObjects);
	
	this->ReadMaterials(nObjects);
	this->pInput->Skip(3); //don't know what that is...
	this->pInput->ReadUInt32(unknownSize); //seems to be a bit larger than the textures themselves
	this->pInput->ReadUInt32(nTextures);
	//textures in ZTEX format
	
	//rest is unknown
	*/

	//ReadMaterials:
	/*bool noCollDet, noLightmap, lodDontCollapse, forceOccluder, environmentalMapping, ignoreSunLight;
	byte materialGroup, texAniMapMode, waveMode, waveSpeed, alphaFunc;
	uint16 id, subId;
	uint32 currentOffset, entrySize, const242432;
	float32 smoothAngle, texAniFPS, waveMaxAmplitude, waveGridSize, defMappingAtX, defMappingAtY;
	CString identifier, textureName, texSize, texAniMapDir, detailObject;
	*/
	/*
		materialGroup:
			0 = UNDEF
			1 = METAL
			2 = STONE
			3 = WOOD
			4 = EARTH
			5 = WATER
			6 = SNOW

		texAniMapMode:
			0 = NONE
			1 = LINEAR

		waveMode:
			0 = NONE
			1 = AMBIENT_GROUND
			2 = GROUND
			3 = AMBIENT_WALL
			4 = WALL
			5 = ENV
			6 = AMBIENT_WIND
			7 = WIND

		waveSpeed:
			0 = NONE
			1 = SLOW
			2 = NORMAL
			3 = FAST

		alphaFunc:
			0 = MAT_DEFAULT
			1 = NONE
			2 = BLEND
			3 = ADD
			4 = SUB
			5 = MUL
			6 = MUL2
	*/
	/*
	for(uint32 i = 0; i < nMaterials; i++)
	{
		uint32 u2;
		float32 f;

		identifier = this->pInput->ReadString();
		currentOffset = this->pInput->GetCurrentOffset();
		this->pInput->ReadUInt32(entrySize);
		this->pInput->ReadUInt16(id);
		this->pInput->ReadUInt16(subId);
		this->pInput->ReadUInt32(const242432); //a constant value
		ASSERT(const242432 == 2424832);
		ASSERT(this->pInput->ReadString() == "zCMaterial");
		ASSERT(this->pInput->ReadString() == identifier); //name?
		materialGroup = this->pInput->ReadByte();
		this->pInput->ReadUInt32(u2); //unknown value :S, probably a coded color value
		this->pInput->ReadFloat32(smoothAngle);
		textureName = this->pInput->ReadString();
		texSize = this->pInput->ReadString();
		this->pInput->ReadFloat32(texAniFPS);
		texAniMapMode = this->pInput->ReadByte();
		texAniMapDir = this->pInput->ReadString();
		noCollDet = this->pInput->ReadBool();
		noLightmap = this->pInput->ReadBool();
		lodDontCollapse = this->pInput->ReadBool();
		detailObject = this->pInput->ReadString();
		this->pInput->ReadFloat32(f); //unknown, detailObjectScale? (but somehow multiplicated with something...)
		forceOccluder = this->pInput->ReadBool();
		environmentalMapping = this->pInput->ReadBool();
		this->pInput->ReadFloat32(f); //unknown, environmentalMappingStrength? (but somehow multiplicated with something...)
		waveMode = this->pInput->ReadByte();
		waveSpeed = this->pInput->ReadByte();
		this->pInput->ReadFloat32(waveMaxAmplitude);
		this->pInput->ReadFloat32(waveGridSize);
		ignoreSunLight = this->pInput->ReadBool();
		alphaFunc = this->pInput->ReadByte();
		this->pInput->ReadFloat32(defMappingAtX);
		this->pInput->ReadFloat32(defMappingAtY);
		
		ASSERT(this->pInput->GetCurrentOffset() == currentOffset + entrySize);
	}*/
	
	this->refInputStream.Skip(chunkSize);
	
	ASSERT(this->ReadCodedString() == "[]"); //here must be the end of object...*/
}

void CZENBinarySafe::ReadoCWorld()
{
	CString objectTag, objectName;
	
	objectTag = this->ReadCodedString();
	this->ParseObjectTag(objectTag, objectName);

	ASSERT(objectName == "oCWorld");
	
	while(!this->refInputStream.HitEnd())
	{
		objectTag = this->ReadCodedString();
		this->ParseObjectTag(objectTag, objectName);

		if(objectTag == "[]")
			break;
		
		if(objectName == "MeshAndBsp")
		{
			this->ReadMeshAndBsp();
		}
		else if(objectName == "VobTree")
		{
			this->ReadVOB(objectName);
		}
		else if(objectName == "WayNet")
		{
			this->ReadWayNet();
		}
		else if(objectName == "EndMarker")
		{
			ASSERT(this->ReadCodedString() == "[]");
		}
	}
}

CString CZENBinarySafe::ReadString()
{
	uint16 length;
	
	this->refInputStream.ReadUInt16(length);
	return this->refInputStream.ReadString((uint32)length);
}

void CZENBinarySafe::ReadVOB(const CString &refObjectTag)
{
	uint32 id;
	AVob *pVob;
	CString className, str;
	
	this->ParseObjectTag(refObjectTag, className);
	
	pVob = this->CreateVOB(className);
	
	while(true)
	{
		switch(this->refInputStream.ReadByte())
		{
		case CODEDTYPE_STRING:
			{
				str = this->ReadString();
				
				if(str == "[]")
				{
					this->pWorld->InsertVob(pVob);
					return; //end of object
				}
				
				//This is a subobject
				this->ReadVOB(str);
			}
			break;
		case CODETYPE_ID:
			{
				this->refInputStream.ReadUInt32(id);

				switch(this->refInputStream.ReadByte())
				{
				case CODEDTYPE_STRING:
					{
						uint16 length;

						this->refInputStream.ReadUInt16(length);

						const CString &refStr = this->refInputStream.ReadString((uint32)length);

						if(pVob)
							pVob->SetString(this->pChilds[id].name, refStr);
					}
					break;
				case CODETYPE_INT:
					{
						int32 value;

						this->refInputStream.ReadInt32(value);
						
						if(pVob)
							pVob->SetInt(this->pChilds[id].name, value);
					}
					break;
				case CODETYPE_FLOAT:
					{
						float32 value;

						this->refInputStream.ReadFloat32(value);
					}
					break;
				case CODETYPE_BYTE:
					{
						byte b;

						b = this->refInputStream.ReadByte();
					}
					break;
				case CODETYPE_SHORT:
					{
						int16 value;
						
						this->refInputStream.ReadInt16(value);
					}
					break;
				case CODETYPE_BOOL:
					{
						uint32 value;

						this->refInputStream.ReadUInt32(value);
						ASSERT(value == 0 || value == 1 || value == -1);
						//return value != 0;
					}
					break;
				case CODETYPE_VECTOR3:
					{
						this->refInputStream.Skip(12);
					}
					break;
				case CODETYPE_COLOR:
					{
						uint32 value;
						
						this->refInputStream.ReadUInt32(value);
					}
					break;
				case CODETYPE_RAW:
					{
						uint16 size;
						byte buffer[400];
						
						this->refInputStream.ReadUInt16(size);
						if(size > sizeof(buffer))
						{
							ASSERT(0);
						}
						this->refInputStream.ReadBytes(buffer, size);
						
						//if(pVob)
						//refReader.SetRaw(this->pChilds[id].name, buffer, size);
					}
					break;
				case CODETYPE_RAWFLOAT:
					{
						uint16 length;
						uint32 i;
						float32 f;
						
						this->refInputStream.ReadUInt16(length);
						ASSERT((length & 1) == 0);
						length /= 4;
						
						for(i = 0; i < length; i++)
						{
							this->refInputStream.ReadFloat32(f); //skip it...
						}
					}
					break;
				case CODETYPE_ENUM:
					{
						uint32 value;

						this->refInputStream.ReadUInt32(value);
					}
					break;
				default:
					{
						uint32 offset;

						offset = this->refInputStream.GetCurrentOffset();
						ASSERT(0);
					}
				}
			}
			break;
		default:
			ASSERT(0);
		}
	}
}

void CZENBinarySafe::ReadWayNet()
{
	CString objectTag, className;
	
	while(true)
	{
		objectTag = this->ReadCodedString();
		
		if(objectTag == "[]")
			break;
		this->ParseObjectTag(objectTag, className);
		if(className == "zCWayNet")
		{
			this->ReadzCWayNet();
		}
		else
		{
			ASSERT(0);
		}
	}
}

void CZENBinarySafe::ReadzCWayNet()
{
	uint32 id;
	CString className, str;
	
	while(true)
	{
		switch(this->refInputStream.ReadByte())
		{
		case CODEDTYPE_STRING:
			{
				str = this->ReadString();
				
				if(str == "[]")
					return; //end of object
				this->ParseObjectTag(str, className);

				if(className == "zCWayNet")
				{
					this->ReadzCWayNet();
				}
				else if(className == "zCWaypoint")
				{
					this->ReadzCWaypoint();
				}
				else if(className == "§")
				{
					ASSERT(this->ReadCodedString() == "[]");
				}
				else
				{
					ASSERT(0);
				}
			}
			break;
		case CODETYPE_ID:
			{
				this->refInputStream.ReadUInt32(id);

				CString &refName = this->pChilds[id].name;

				if(refName == "waynetVersion")
				{
					this->ReadCodedInt();
				}
				else if(refName == "numWaypoints")
				{
					this->ReadCodedInt();
				}
				else if(refName == "numWays")
				{
					this->ReadCodedInt();
				}
				else
				{
					ASSERT(0);
				}
			}
			break;
		default:
			ASSERT(0);
		}
	}
}

void CZENBinarySafe::ReadzCWaypoint()
{
	uint32 id;
	CString className, str;
	
	while(true)
	{
		switch(this->refInputStream.ReadByte())
		{
		case CODEDTYPE_STRING:
			{
				str = this->ReadString();
				
				if(str == "[]")
					return; //end of object
				this->ParseObjectTag(str, className);
				
				if(className == "zCWayNet")
				{
					this->ReadzCWayNet();
				}
				else if(className == "zCWaypoint")
				{
					this->ReadzCWaypoint();
				}
				else
				{
					ASSERT(0);
				}
			}
			break;
		case CODETYPE_ID:
			{
				this->refInputStream.ReadUInt32(id);

				CString &refName = this->pChilds[id].name;

				if(refName == "wpName")
				{
					this->ReadCodedString();
				}
				else if(refName == "waterDepth")
				{
					this->ReadCodedInt();
				}
				else if(refName == "underWater")
				{
					this->ReadCodedBool();
				}
				else if(refName == "position")
				{
					this->ReadCodedVector3();
				}
				else if(refName == "direction")
				{
					this->ReadCodedVector3();
				}
				else
				{
					ASSERT(0);
				}
			}
			break;
		default:
			ASSERT(0);
		}
	}
}

//Public Functions
void CZENBinarySafe::Read()
{
	uint32 version, nObjects, offsetToChilds, currentOffset;
	
	this->refInputStream.ReadUInt32(version);
	ASSERT(version == 2);
	this->refInputStream.ReadUInt32(nObjects);
	this->refInputStream.ReadUInt32(offsetToChilds); //offset to the childs section

	//read the childs first
	currentOffset = this->refInputStream.GetCurrentOffset();
	this->refInputStream.SetCurrentOffset(offsetToChilds);
	this->ReadChilds();

	//read world
	this->refInputStream.SetCurrentOffset(currentOffset);
	this->ReadoCWorld(); //there should be only the oCWorld object in the zen file
	
	ASSERT(this->refInputStream.GetCurrentOffset() == offsetToChilds);
}