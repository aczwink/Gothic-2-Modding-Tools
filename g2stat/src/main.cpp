//SJC
#include <SJCLib.h>
#include <SJCWinLib.h>
//Local
#include "resource.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Prototypes
bool CheckArguments();
bool EvaluateArguments(CArray<CString> &args);
bool GenerateDoc(CString g2dir, CString modName, CString outputPath);
void PrintManual();

//Global Variables
CString g_Input;
CString g_mod;
CString g_Output;

int main(int argc, char* argv[])
{
	CArray<CString> args;

	SetConsoleTitle(APPLICATION_TITLE);
	stdOut << APPLICATION_TITLE << endl << endl;

	for(uint32 i = 1; i < (uint32)argc; i++)
	{
		args.Push(argv[i]);
	}

	if(EvaluateArguments(args))
	{
		if(!GenerateDoc(g_Input, g_mod, g_Output))
			return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}
	else
	{
		PrintManual();
		return EXIT_FAILURE;
	}
	
	PrintManual();
	return EXIT_SUCCESS;
}

void PrintManual()
{
	stdOut
		<< "Usage: " << endl
		<< "  " << APPLICATION_NAME << " g2dir mod output" << endl << endl
		<< "   g2dir      path to gothic 2 the night of the raven" << endl
		<< "   mod        name of the mod to load. Name must be equal to mod ini file without file extension" << endl
		<< "   output     folder in which the output is putted" << endl;
}

bool EvaluateArguments(CArray<CString> &args)
{
	//exactly 3 args must exist
	if(args.GetNoOfElements() != 3)
		return false;

	for(uint32 i = 0; i < args.GetNoOfElements(); i++)
	{
		if(args[i][0] == '-' && !g_Input.IsEmpty()) //An option
		{
			ASSERT(0);
		}
		else //Either input, mod or output
		{
			if(g_Input.IsEmpty())
			{
				g_Input = args[i];
			}
			else
			{
				if(g_mod.IsEmpty())
				{
					g_mod = args[i];
				}
				else
				{
					if(g_Output.IsEmpty())
					{
						g_Output = args[i];
					}
					else
					{
						return false;
					}
				}
			}
		}
	}

	return CheckArguments();
}

bool CheckArguments()
{
	return true;
}