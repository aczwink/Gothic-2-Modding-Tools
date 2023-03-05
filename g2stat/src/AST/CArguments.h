//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		//Forward declarations
		class CType;

		namespace OptAST
		{
			//Forward declarations
			class CFunction;
			class CLocalVariable;
		}
		
		namespace AST
		{
			class CArguments : public ANode
			{
				struct SArg
				{
					CType *pType;
					SJCLib::CString name;
				};
			private:
				//Members
				SJCLib::CLinkedList<SArg> args;
			public:
				//Constructor
				CArguments(CType *pType, const SJCLib::CString &refName);
				//Destructor
				~CArguments();
				//Methods
				void Add(CType *pType, const SJCLib::CString &refName);
				void AddArgs(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CFunction *pFunction, CCompiler &refCompiler);
			};
		}
	}
}