#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "CItem.h"
#include "CNPC.h"

namespace SJCPBLib
{
	struct SChildEntry
	{
		SJCLib::CString name;
	};
	
	class CWorld
	{
	private:
		//Variables
		SJCLib::CString name;
		SJCLib::CArray<AVob *> vobs;
	public:
		//Constructor
		CWorld(const SJCLib::CString &refWorldName);
		//Destructor
		~CWorld();
		//Functions
		void InsertVob(AVob *pVob);
		//Inline
		inline const SJCLib::CString &GetName() const
		{
			return this->name;
		}

		inline const SJCLib::CArray<AVob *> &GetVobs() const
		{
			return this->vobs;
		}
	};
}