//Local
#include "ANode.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CClass;
		}

		namespace AST
		{
			//Forward declarations
			class AVariable;
			class CClass;
			
			class CVariables : public ANode
			{
			private:
				//Members
				SJCLib::CLinkedList<AVariable *> variables;
			public:
				//Constructor
				CVariables();
				//Destructor
				~CVariables();
				//Methods
				void AddVariableAfter(AVariable *pNew, AVariable *pAfter);
				void Process(CCompiler &refCompiler, CClass *pClass, OptAST::CClass *pOptClass);
				void RemoveVariable(AVariable *pVariable);

				//Inline
				inline void Add(AVariable *pVariable)
				{
					this->variables.InsertFront(pVariable);
				}

				inline uint32 GetCount() const
				{
					return this->variables.GetNoOfElements();
				}

				inline const SJCLib::CLinkedList<AVariable *> &GetList() const
				{
					return this->variables;
				}
			};
		}
	}
}