#pragma once
//Libs
#include <SJCLib.h>

namespace SJCPBLib
{
	class AVob
	{
	public:
		//Destructor
		virtual ~AVob(){}
		//Overwriteable
		virtual bool SetInt(const SJCLib::CString &refMember, int32 value);
		virtual bool SetString(const SJCLib::CString &refMember, const SJCLib::CString &refValue);
	};
}