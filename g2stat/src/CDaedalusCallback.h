//Local
#include "ICompilerCallback.h"
//Namespaces
using namespace SJCLib;
using namespace SJCPBLib;
using namespace Daedalus;

class CDaedalusCallback : public ICompilerCallback
{
private:
	//Methods
	void PrintError(const CWString &refMessage) const;
	void PrintError(const CString &refMessage, const CWString &refFilename, uint32 lineNumber) const;
	void PrintWarning(const CString &refMessage, const CWString &refFilename, uint32 lineNumber) const;
public:
	//Callbacks
	void OnBeginParsing() const;
	void OnEndParsing() const;
	void OnEndProcessing() const;
	void OnOpenFileFailed(const CWString &refFilename) const;
	void OnParsingFailed(const CWString &refFilename) const;
	void OnTypeMismatch(const CType &refFrom, const CType &refTo, const SJCLib::CWString &refFilename, uint32 lineNumber) const;
	void OnUndefinedIdentifier(const CString &refIdentifier, const CWString &refFilename, uint32 lineNumber) const;
	void OnUselessStatement(const CWString &refFilename, uint32 lineNumber) const;
};