#pragma once
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "version.h" //Only here

//Definitions
#define __STR(x) #x
#define _STR(x) __STR(x)

#define APPLICATION_NAME "daedalusNfo"
#define APPLICATION_CREATOR "SoulJammingCurse"
#define APPLICATION_CREATOR_WEBSITE "http://souljammingcurse.de"
#define APPLICATION_ORIGINALFILENAME "daedalusNfo.exe"
#define APPLICATION_VERSION_RESOURCE VERSION_MAJOR,VERSION_MINOR,VERSION_BUILD,VERSION_REVISION
#define APPLICATION_VERSION_STRING _STR(VERSION_MAJOR) "." _STR(VERSION_MINOR) "." _STR(VERSION_BUILD) "." _STR(VERSION_REVISION)

#ifdef _DEBUG
#define APPLICATION_TITLE APPLICATION_NAME " by " APPLICATION_CREATOR " v" APPLICATION_VERSION_STRING " Build:" BUILDDATE_STRING " Debug Mode"
#else
#define APPLICATION_TITLE APPLICATION_NAME " by " APPLICATION_CREATOR " v" APPLICATION_VERSION_STRING " Build:" BUILDDATE_STRING
#endif
