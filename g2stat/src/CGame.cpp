//Class Header
#include "CGame.h"
//Libs
#include <SJCWinLib.h>
//Local
#include "ZEN.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
using namespace SJCPBLib;
using namespace SJCPBLib::Daedalus;
//Definitions
#define VDFS_FLAGS_ISDIRECTORY 0x80000000
#define VDFS_FLAGS_LAST_ENTRY 0x40000000

//Constructor
CGame::CGame()
{
	this->pActiveWorld = NULL;
	this->pScripts = NULL;
	this->pHero = NULL;
}

//Destructor
CGame::~CGame()
{
	this->gameDir.Release();
	
	foreach(it, this->vdfFiles)
	{
		delete it.GetValue();
	}
	this->vdfFiles.Release();

	foreach(it, this->otherFiles)
	{
		delete it.GetValue();
	}
	this->otherFiles.Release();

	foreach(it, this->fileTree)
	{
		HeapDeleteSafe(it.GetValue().pBuffer);
	}
	this->fileTree.Release();

	foreach(it, this->loadedWorlds)
	{
		delete it.GetValue();
	}
	
	HeapDeleteSafe(this->pScripts);
	HeapDeleteSafe(this->pHero);
}

//Private Functions
void CGame::FreeFile(const SJCLib::CString &refFilename)
{
	auto &refIt = this->fileTree.Find(refFilename.ToLowercase());
	
	if(refIt.IsValid())
	{
		memfreesafe(refIt.GetValue().pBuffer);
	}
	else
	{
		ASSERT(0);
	}
}

bool CGame::LoadConfig(const CString &refConfig, CArray<CString> &refModVDFFiles)
{
	CIniFile input;
	CString tmp;
	
	input.Open(this->gameDir + "\\System\\" + refConfig + ".ini", true);
	
	this->playerName = input.GetStringValue("SETTINGS", "Player");
	this->defaultWorldName = input.GetStringValue("SETTINGS", "World");
	
	tmp = input.GetStringValue("FILES", "VDF");
	refModVDFFiles = tmp.Split("  ");
	
	return true;
}

byte *CGame::LoadFile(const SJCLib::CString &refFilename, uint32 &refFileSize)
{
	auto &refIt = this->fileTree.Find(refFilename.ToLowercase());

	if(refIt.IsValid())
	{
		SFileIndex &refFileIndex = refIt.GetValue();
		
		if(!refFileIndex.pBuffer)
		{
			//file is not cached... do it
			refFileIndex.pBuffer = (byte *)malloc(refFileIndex.dataSize);
			refFileIndex.pInputStream->SetCurrentOffset(refFileIndex.dataOffset);
			refFileIndex.pInputStream->ReadBytes(refFileIndex.pBuffer, refFileIndex.dataSize);
		}
		refFileSize = refFileIndex.dataSize;

		return refFileIndex.pBuffer;
	}
	else
	{
		CString filename;
		
		//file wasn't found... meaning it is not in an vdfs archive... check if the file exists outside

		filename = this->gameDir + "\\" + refFilename;
		
		if(FileExists(filename))
		{
			CFileInputStream *pInput;
			SFileIndex fi;
			
			pInput = new CFileInputStream;
			if(!pInput->Open(filename))
			{
				ASSERT(0);
			}

			fi.dataOffset = 0;
			fi.dataSize = pInput->GetSize();
			fi.pBuffer = NULL;
			fi.pInputStream = pInput;

			this->fileTree.Insert(refFilename.ToLowercase(), fi);
			this->otherFiles.Push(pInput);
			
			return this->LoadFile(refFilename, refFileSize); //recall... so that file can be cached
		}
	}
	
	return NULL;
}

bool CGame::OpenArchive(const CWString &refVDFName)
{
	uint32 i, nEntries, fileHeadersOffset;
	CFileInputStream *pInput;
	
	pInput = new CFileInputStream;
	if(!pInput->Open(this->gameDir + "\\Data\\" + refVDFName))
	{
		delete pInput;
		return false;
	}

	this->vdfFiles.Push(pInput);

	//256 byte comment
	pInput->Skip(0x100);
	//16 byte signature "PSVDSC_V2.00"
	pInput->Skip(0x10);

	pInput->ReadUInt32(nEntries); //files and directories
	pInput->Skip(4); //number of files
	pInput->Skip(4); //timestamp
	pInput->Skip(4); //size of archive
	pInput->ReadUInt32(fileHeadersOffset);
	pInput->Skip(4); //entry size

	ASSERT(pInput->GetCurrentOffset() == fileHeadersOffset);

	i = 0;
	this->ReadVDFSDirectory(CString(), i, nEntries, *pInput);
	
	return true;
}

void CGame::ReadVDFSDirectory(CString path, uint32 &refCurrentEntry, uint32 nEntries, ASeekableInputStream &refInput)
{
	char buffer[64];
	uint32 i, offset, size, flags, attributes;
	CString name;
	CLinkedList<CString> pathQueue;

	for(; refCurrentEntry < nEntries; refCurrentEntry++)
	{
		refInput.ReadBytes(buffer, 64); //name, truncated with 0x20 bytes...
		for(i = 0; i < 64 && buffer[i] != 0x20; i++);

		name = CString(buffer, i);

		refInput.ReadUInt32(offset);
		refInput.ReadUInt32(size);
		refInput.ReadUInt32(flags);
		ASSERT((flags & 0x3FFFFFFF) == 0);
		
		refInput.ReadUInt32(attributes);
		
		if(flags & VDFS_FLAGS_ISDIRECTORY)
		{
			pathQueue.InsertTail(name);
		}
		else
		{
			SFileIndex fi;
			
			fi.pBuffer = NULL;
			fi.dataOffset = offset;
			fi.dataSize = size;
			fi.pInputStream = &refInput;

			this->fileTree.Insert((path + name).ToLowercase(), fi);
		}
		
		if(flags & VDFS_FLAGS_LAST_ENTRY)
		{
			break;
		}
	}
	
	foreach(it, pathQueue)
	{
		this->ReadVDFSDirectory(path + *it + "\\", refCurrentEntry, nEntries, refInput);
	}
}

//Public Functions
void CGame::EnterWorld(const CString &refWorldName)
{
	uint32 zenDataSize;
	byte *pZenData;

	//check if world is already loaded
	foreach(it, this->loadedWorlds)
	{
		if(it.GetValue()->GetName() == refWorldName)
		{
			this->pActiveWorld = it.GetValue();
			this->pScripts->ExecuteFunction("Init_" + this->pActiveWorld->GetName());
			return;
		}
	}
	
	//load world
	pZenData = this->LoadFile("_work\\data\\Worlds\\" + refWorldName, zenDataSize);
	if(!pZenData)
		ASSERT(0);
	this->pActiveWorld = new CWorld(GetFileName(refWorldName).ToCString());
	ReadZen(this->pActiveWorld, CBufferInputStream(pZenData, zenDataSize));
	this->FreeFile("_work\\data\\Worlds\\" + refWorldName);
	
	this->pScripts->ExecuteFunction("Startup_" + this->pActiveWorld->GetName());
	this->loadedWorlds.Push(this->pActiveWorld);

	this->pScripts->ExecuteFunction("Init_" + this->pActiveWorld->GetName());
}

bool CGame::Init(CString gameDir, CString config)
{
	CArray<CString> modVDFFileNames;
	
	if(!(FileExists(gameDir) && IsDirectory(gameDir) && FileExists(gameDir + "\\System") && IsDirectory(gameDir + "\\System") && FileExists(gameDir + "\\System\\Gothic2.exe")))
		return false;
	
	this->gameDir = gameDir;

	//load the default config first
	if(!this->LoadConfig("GothicGame", modVDFFileNames))
		return false;
	//overwrite with mod config values
	if(config != "GothicGame")
	{
		if(!this->LoadConfig(config, modVDFFileNames))
			return false;
	}
	
	//Read VDF data files
	const CArray<CWString> &refVDFFiles = ListFiles(gameDir + "\\Data\\", L"*.vdf", false);
	foreach(it, refVDFFiles)
	{
		if(!this->OpenArchive(*it))
			return false;
	}
	//overwrite with mod VDFs
	foreach(it, modVDFFileNames)
	{
		if(!this->OpenArchive("modvdf\\" + it.GetValue()))
			return false;
	}
	
	return true;
}

void CGame::LoadScripts(AInputStream &refInput)
{
	HeapDeleteSafe(this->pScripts);
	this->pScripts = new CDaedalusProgram(refInput);
}

void CGame::StartNewGame()
{
	byte *pBuffer;
	uint32 bufferSize;
	
	//Read scripts if none are loaded
	if(!this->pScripts)
	{
		pBuffer = this->LoadFile("_work\\data\\Scripts\\_compiled\\Gothic.dat", bufferSize);
		this->LoadScripts(CBufferInputStream(pBuffer, bufferSize));
		this->FreeFile("_work\\data\\Scripts\\_compiled\\Gothic.dat");
	}

	//create the hero
	this->pHero = new CNPC(this->playerName);
	this->pScripts->SetHero(this->pHero);
	
	//enter default world
	this->EnterWorld(this->defaultWorldName);
}