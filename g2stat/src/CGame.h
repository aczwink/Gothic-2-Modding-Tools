#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "CDaedalusProgram.h"
#include "CWorld.h"

namespace SJCPBLib
{
	class CGame
	{
		struct SFileIndex
		{
			byte *pBuffer; //NULL if not in buffer (not cached)
			uint32 dataOffset;
			uint32 dataSize;
			SJCLib::ASeekableInputStream *pInputStream;
		};
	private:
		//Variables
		SJCLib::CString gameDir;
		SJCLib::CString playerName;
		SJCLib::CString defaultWorldName;
		SJCLib::CArray<SJCLib::CFileInputStream *> vdfFiles;
		SJCLib::CArray<SJCLib::CFileInputStream *> otherFiles; //files, loaded but not in vdfs archive
		SJCLib::CMap<SJCLib::CString, SFileIndex> fileTree;
		SJCLib::CArray<CWorld *> loadedWorlds; //to decide whether to call Startup_
		CWorld *pActiveWorld;
		CDaedalusProgram *pScripts;
		CNPC *pHero;
		//Constructor
		CGame();
		//Functions
		void FreeFile(const SJCLib::CString &refFilename);
		bool LoadConfig(const SJCLib::CString &refConfig, SJCLib::CArray<SJCLib::CString> &refModVDFFiles);
		byte *LoadFile(const SJCLib::CString &refFilename, uint32 &refFileSize);
		bool OpenArchive(const SJCLib::CWString &refVDFName);
		void ReadVDFSDirectory(SJCLib::CString path, uint32 &refCurrentEntry, uint32 nEntries, SJCLib::ASeekableInputStream &refInput);

		//Inline
		inline byte *LoadFile(const SJCLib::CString &refFilename)
		{
			uint32 fileSize;

			return this->LoadFile(refFilename, fileSize);
		}
	public:
		//Destructor
		~CGame();
		//Functions
		void EnterWorld(const SJCLib::CString &refWorldName);
		bool Init(SJCLib::CString gameDir, SJCLib::CString config);
		void LoadScripts(SJCLib::AInputStream &refInput);
		void StartNewGame();
		//Static
		inline static CGame &GetInstance()
		{
			static CGame instance;

			return instance;
		}

		//Inline
		inline CWorld *GetActiveWorld()
		{
			return this->pActiveWorld;
		}

		inline const SJCLib::CString &GetDefaultWorldName() const
		{
			return this->defaultWorldName;
		}
		
		inline CNPC *GetHero()
		{
			return this->pHero;
		}
		
		inline CDaedalusProgram *GetProgram()
		{
			return this->pScripts;
		}
	};
}