//Local
#include "CWorld.h"

namespace SJCPBLib
{
	//Classes
	class CZENBinarySafe
	{
		enum ECodedType
		{
			CODEDTYPE_STRING = 1, //followed by uint16 length and ascii data
			CODETYPE_INT = 2, //int32
			CODETYPE_FLOAT = 3, //float32
			CODETYPE_BYTE = 4,
			CODETYPE_SHORT = 5,
			CODETYPE_BOOL = 6, //aligned on 4 byte... spacer accepts -1
			CODETYPE_VECTOR3 = 7, //3 float32 aligned on 12 byte
			CODETYPE_COLOR = 8, //4 byte aligned... format???
			CODETYPE_RAW = 9, //followed by uint16 size and data
			CODETYPE_RAWFLOAT = 16, //followed by uint16 size and float32s...
			CODETYPE_ENUM = 17,
			CODETYPE_ID = 18, //'id' of a member variable
		};
		
		enum EChunkType
		{
			CHUNKTYPE_ILLEGAL,
			CHUNKTYPE_BINARY,
		};
	private:
		//Variables
		SChildEntry *pChilds;
		SJCLib::ASeekableInputStream &refInputStream;
		CWorld *pWorld;
	private:
		//Functions
		AVob *CreateVOB(const SJCLib::CString &refClassName);
		void ParseObjectTag(const SJCLib::CString &refObjectTag, SJCLib::CString &refObjectName);
		void ReadChilds();
		EChunkType ReadChunkTags();
		bool ReadCodedBool();
		int32 ReadCodedInt();
		void ReadCodedVector3();
		void ReadMeshAndBsp();
		void ReadoCWorld();
		SJCLib::CString ReadString();
		void ReadVOB(const SJCLib::CString &refObjectTag);
		void ReadWayNet();
		void ReadzCWayNet();
		void ReadzCWaypoint();

		//Inline
		inline SJCLib::CString ReadCodedString()
		{
			ASSERT(this->refInputStream.ReadByte() == CODEDTYPE_STRING);

			return this->ReadString();
		}
	public:
		//Constructor
		CZENBinarySafe(CWorld *pWorld, SJCLib::ASeekableInputStream &refInputStream);
		//Destructor
		~CZENBinarySafe();
		//Functions
		void Read();
	};

	void ReadZen(CWorld *pWorld, SJCLib::ASeekableInputStream &refInputStream);
}