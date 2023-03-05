#pragma once
//SJC
#include <SJCLib.h>
//Local
#include "CType.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class ICompilerCallback
		{
		public:
			//Callbacks
			virtual void OnBeginParsing() const = NULL;
			virtual void OnEndParsing() const = NULL;
			virtual void OnEndProcessing() const = NULL;
			virtual void OnOpenFileFailed(const SJCLib::CWString &refFilename) const = NULL;
			virtual void OnParsingFailed(const SJCLib::CWString &refFilename) const = NULL;
			virtual void OnTypeMismatch(const CType &refFrom, const CType &refTo, const SJCLib::CWString &refFilename, uint32 lineNumber) const = NULL;
			virtual void OnUndefinedIdentifier(const SJCLib::CString &refIdentifier, const SJCLib::CWString &refFilename, uint32 lineNumber) const = NULL;
			virtual void OnUselessStatement(const SJCLib::CWString &refFilename, uint32 lineNumber) const = NULL;
		};
	}
}