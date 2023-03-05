//Class Header
#include "CDaedalusCallback.h"

//Private methods
void CDaedalusCallback::PrintError(const CWString &refMessage) const
{
	stdErr << "ERROR: " << refMessage << endl;
}

void CDaedalusCallback::PrintError(const CString &refMessage, const CWString &refFilename, uint32 lineNumber) const
{
	stdErr << "ERROR at (" << refFilename << ':' << lineNumber << "): " << refMessage << endl;
}

void CDaedalusCallback::PrintWarning(const CString &refMessage, const CWString &refFilename, uint32 lineNumber) const
{
	stdErr << "WARNING at (" << refFilename << ':' << lineNumber << "): " << refMessage << endl;
}

//Local Functions
/*static CString ErrorCodeToString(EErrorCode errorCode, const CString &refParam1)
{
	switch(errorCode)
	{
	case DAEDALUS_ERROR_COMPILE_ARRAYINDEX:
		return "Couldn't compile array index at " + refParam1;
	case DAEDALUS_ERROR_PARSING_FAILED:
	}

	ASSERT(0);
	return CString();
}
*/

//Callbacks
void CDaedalusCallback::OnBeginParsing() const
{
	stdOut << "Step I: Parsing scripts..." << endl;
}

void CDaedalusCallback::OnEndParsing() const
{
	stdOut << "Scripts successfully parsed!" << endl << endl;
	stdOut << "Step II: Processing scripts..." << endl;
}

void CDaedalusCallback::OnEndProcessing() const
{
	stdOut << "Done processing. Cleaning up..." << endl << endl;
}

/*void CDaedalusCallback::OnError(EErrorCode errorCode, const CString &refParam1) const
{
	stdErr << "Error: " << ErrorCodeToString(errorCode, refParam1) << endl;
}

void CDaedalusCallback::OnWarning(EWarningCode warningCode, const CString &refParam1) const
{
	stdErr << "Warning: " << WarningCodeToString(warningCode, refParam1) << endl;
}*/

void CDaedalusCallback::OnOpenFileFailed(const CWString &refFilename) const
{
	this->PrintError(L"Couldn't open file '" + refFilename + L"'");
}

void CDaedalusCallback::OnParsingFailed(const CWString &refFilename) const
{
	this->PrintError(L"Parsing file '" + refFilename + L"' failed.");
}

void CDaedalusCallback::OnTypeMismatch(const CType &refFrom, const CType &refTo, const CWString &refFilename, uint32 lineNumber) const
{
	this->PrintError("Type mismatch. Trying to convert '" + refFrom.ToString() + "' to '" + refTo.ToString() + "'.", refFilename, lineNumber);
}

void CDaedalusCallback::OnUndefinedIdentifier(const CString &refIdentifier, const CWString &refFilename, uint32 lineNumber) const
{
	this->PrintError("Undefined identifier '" + refIdentifier + "'", refFilename, lineNumber);
}

void CDaedalusCallback::OnUselessStatement(const SJCLib::CWString &refFilename, uint32 lineNumber) const
{
	this->PrintWarning("Dangerous statement detected. This compiler will ignore it but the ZenGine may compile it and it may alter the stack (may have a big influence on the behaviour).", refFilename, lineNumber);
}