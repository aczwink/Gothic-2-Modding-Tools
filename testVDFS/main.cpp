#include <SJCLib.h>
using namespace SJCLib;

static CFileInputStream input;

bool readCodedValue()
{
	byte type;

	type = input.ReadByte();
	switch(type)
	{
	case 1: //string
		{
			uint16 length;
			static char buf[1000];

			MemZero(buf, 1000);

			input.ReadUInt16(length);
			ASSERT(length < 1000);
			input.ReadBytes(buf, length);

			//stdOut << "string: " << buf << endl;

			if(MemCmp(buf, "[]", 3) == 0)
				return false;
		}
		break;
	case 2: //100% int signed
		{
			int32 tmp;

			input.ReadInt32(tmp);
		}
		break;
	case 3: //float32 on 4 byte
		{
			float32 f;

			input.ReadFloat32(f);
		}
		break;
	case 4: //byte
		{
			input.ReadByte();
		}
		break;
	case 5: //2 byte (signed?)
		{
			int16 i;

			input.ReadInt16(i);
			ASSERT(i >= 0);
		}
		break;
	case 6: //100% bool... spacer accepts -1
		{
			int32 tmp;

			input.ReadInt32(tmp);
			ASSERT(tmp == 0 || tmp == 1 || tmp == -1);
		}
		break;
	case 8: //4 byte aligned... color?
		{
			uint32 tmp;

			input.ReadUInt32(tmp);
		}
		break;
	case 9:
		{
			uint16 length;

			//type RAW... raw means hex representation of byte array

			input.ReadUInt16(length);
			input.Skip(length);
		}
		break;
	case 16: //raw float
		{
			uint16 length;
			float32 f;

			input.ReadUInt16(length);
			ASSERT((length & 1) == 0);

			for(uint32 i = 0; i < uint32(length / 4); i++)
			{
				input.ReadFloat32(f);
			}
		}
		break;
	case 17: //4 byte wide
		{
			uint32 tmp;

			input.ReadUInt32(tmp);
			if(!IN_RANGE(tmp, 0, 3) && tmp != 120 && tmp != 132198264)
			{
				ASSERT(0);
			}
		}
		break;
	case 18: //id? index?
		{
			uint32 tmp;

			//unknown usage, 4byte

			input.ReadUInt32(tmp);
			ASSERT(tmp < 65535);
		}
		break;
	default:
		ASSERT(0);
	}

	return true;
}

void readTags()
{
	CString line;

	while(true)
	{
		line = input.ReadString(0xA);
		if(line == "END")
			return;
	}
}

void readTagsEmptyLine()
{
	CString line;

	while(true)
	{
		line = input.ReadString(0xA);
		if(line.IsEmpty())
			return;
	}
}

void readMeshAndBspSubObjects(uint32 nObj)
{
	bool noCollDet, noLightmap, lodDontCollapse, forceOccluder, environmentalMapping, ignoreSunLight;
	byte materialGroup, texAniMapMode, waveMode, waveSpeed, alphaFunc;
	uint16 id, subId;
	uint32 currentOffset, entrySize, const242432;
	float32 smoothAngle, texAniFPS, waveMaxAmplitude, waveGridSize, defMappingAtX, defMappingAtY;
	CString identifier, textureName, texSize, texAniMapDir, detailObject;

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
	
	for(uint32 i = 0; i < nObj; i++)
	{
		uint32 u2;
		float32 f;

		identifier = input.ReadString();
		currentOffset = input.GetCurrentOffset();
		input.ReadUInt32(entrySize);
		input.ReadUInt16(id);
		input.ReadUInt16(subId);
		input.ReadUInt32(const242432); //a constant value
		ASSERT(const242432 == 2424832);
		ASSERT(input.ReadString() == "zCMaterial");
		ASSERT(input.ReadString() == identifier); //name?
		materialGroup = input.ReadByte();
		input.ReadUInt32(u2); //unknown value :S, probably a coded color value
		input.ReadFloat32(smoothAngle);
		textureName = input.ReadString();
		texSize = input.ReadString();
		input.ReadFloat32(texAniFPS);
		texAniMapMode = input.ReadByte();
		texAniMapDir = input.ReadString();
		noCollDet = input.ReadBool();
		noLightmap = input.ReadBool();
		lodDontCollapse = input.ReadBool();
		detailObject = input.ReadString();
		input.ReadFloat32(f); //unknown, detailObjectScale? (but somehow multiplicated with something...)
		forceOccluder = input.ReadBool();
		environmentalMapping = input.ReadBool();
		input.ReadFloat32(f); //unknown, environmentalMappingStrength? (but somehow multiplicated with something...)
		waveMode = input.ReadByte();
		waveSpeed = input.ReadByte();
		input.ReadFloat32(waveMaxAmplitude);
		input.ReadFloat32(waveGridSize);
		ignoreSunLight = input.ReadBool();
		alphaFunc = input.ReadByte();
		input.ReadFloat32(defMappingAtX);
		input.ReadFloat32(defMappingAtY);
		
		ASSERT(input.GetCurrentOffset() == currentOffset + entrySize);
	}
}

void readTextures()
{
	byte signature[4];
	uint32 dataSize, nTextures, version, pixelFormat, pixelSize, width, height, nMipMaps;

	input.ReadUInt32(dataSize); //a kind of size.. unknown which
	//input.Skip(dataSize);
	//return;
	input.ReadUInt32(nTextures);

	for(uint32 i = 0; i < nTextures; i++)
	{
		input.ReadBytes(signature, 4);
		if(MemCmp(signature, "ZTEX", 4))
		{
			ASSERT(0);
		}
		input.ReadUInt32(version);
		ASSERT(version == 0);
		input.ReadUInt32(pixelFormat);
		input.ReadUInt32(width);
		input.ReadUInt32(height);
		input.ReadUInt32(nMipMaps);
		input.Skip(12);

		switch(pixelFormat)
		{
		case 8: //16bit - R5G6B5
			pixelSize = 2;
			break;
		default:
			ASSERT(0);
		}

		//skip over data
		input.Skip(width * height * nMipMaps * pixelSize);
	}
}

int main()
{
	uint32 version, nObj, unknownSizeValue, unknownCount, currentOffset, nObj2;
	
	//input.Open("C:\\Games\\Gothic 2\\_work\\data\\Worlds\\Addon\\AddonWorld.zen");
	//input.Open("C:\\Games\\Gothic 2\\_work\\data\\Worlds\\NewWorld\\DragonIsland.zen");
	//input.Open("C:\\Games\\Gothic 2\\_work\\data\\Worlds\\NewWorld\\NewWorld.zen");
	input.Open("C:\\Games\\Gothic 2\\_work\\data\\Worlds\\OldWorld\\OldWorld.zen"); //3848516
	readTags();

	input.ReadUInt32(version);
	ASSERT(version == 2);

	input.ReadUInt32(nObj);
	input.ReadUInt32(unknownSizeValue); //offset to the 'childs' stuff

	readCodedValue();
	readCodedValue();
	input.Skip(4);
	input.ReadUInt32(unknownCount); //'current offset' + unknownCount = before vob tree
	currentOffset = input.GetCurrentOffset();
	input.Skip(123);
	//last 4 byte seem to be the size of the following until end of materials, before textures

	//12962396
	//14909747

	readTags();
	readTagsEmptyLine();
	input.ReadUInt32(nObj2);
	readMeshAndBspSubObjects(nObj2);

	stdOut << "offset after materials: " << input.GetCurrentOffset() << endl;


	input.Skip(3); //don't know what that is...
	readTextures();

	stdOut << "offset after textures:" << input.GetCurrentOffset() << endl;

	//fucked from here...

	input.SetCurrentOffset(currentOffset + unknownCount);
	readCodedValue(); //is "[]"
	readCodedValue(); //VobTree
	for(uint32 i = 0; i < nObj;)
	{
		if(readCodedValue())
		{
			readCodedValue();
		}
		else
		{
			i++;
		}
	}

	stdOut << "offset:" << input.GetCurrentOffset() << endl;
	//13680943
	//13096051
	//14681129

	return 0;
}