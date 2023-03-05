#pragma once
//Libs
#include <SJCLib.h>
//Local
#include "AST\CGlobals.h"
#include "CLexer.h"
#include "Daedalus.h"
#include "ICompilerCallback.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class CParser : public SJCLib::CLALR1Parser<EToken, AST::ANode *>
		{
		private:
			//Variables
			const ICompilerCallback &refCallback;
			CLexer lexer;
			SJCLib::CWString fileName;
			SJCLib::CFiniteSet<AST::ANode *> tmpNodes;
			SJCLib::CFiniteSet<SJCLib::CString *> rawSemanticValues;
			SJCLib::CFiniteSet<void *> treeNodes;
			//Functions
			void OnPutToken(const EToken &refToken, const SJCLib::CString &refString, AST::ANode *&refOutput);
			void OnReduce(int32 reductionRule, AST::ANode *&refOutput);
			//Inline
			inline AST::ANode *GetSemanticValue(uint16 index)
			{
				AST::ANode *pNode;
				
				SJCLib::CLALR1Parser<EToken, AST::ANode *>::GetSemanticValue(index, pNode);
				this->Unregister(pNode);

				return pNode;
			}

			inline void Register(AST::ANode *pNode)
			{
				this->tmpNodes.Insert(pNode);
			}

			inline void Unregister(AST::ANode *pNode)
			{
				this->tmpNodes.Delete(pNode);
			}
		public:
			//Constructor
			CParser(const ICompilerCallback &refCallback);
			//Destructor
			~CParser();
			//Functions
			void *MemAlloc(uint32 size);
			void MemFree(SArrayIndex *pArrayIdx);
			void MemFree(SConstValue *pConstValue);
			void MemFree(SJCLib::CString *pStr);
			bool Parse(const byte *pInput, SJCLib::CWString filename);
			void Release();
			
			//Inline
			inline AST::CGlobals *GetAST()
			{
				AST::CGlobals *pGlobals;

				pGlobals = (AST::CGlobals *)this->GetSemanticValue(0);
				this->Register(pGlobals);

				return pGlobals;
			}
		};
	}
}

/*//SJCLib
#include <SJCLib.h>
//Local
#include "CDaedalusLexer.h"
#include "Daedalus.h"

namespace SJCPBLib
{
	class CDaedalusParser
	{
		typedef int32 State;
		typedef int32 Action; //|Action| is a state, - means reduction, + means shift
	private:
		//Variables
		CDaedalusLexer lexer;
		Daedalus::EToken lookAhead;
		SJCLib::CArray<State> stateStack;
		//SJCLib::CArray<Daedalus::USemanticValue> semanticStack;
		SJCLib::CFiniteSet<SJCLib::CString *> strings;
		//Functions
		//Daedalus::EParserNonTerminals Reduce(Action reductionRule);
	public:
		//Functions
		bool Parse(const char *pSource);
	};
}*/