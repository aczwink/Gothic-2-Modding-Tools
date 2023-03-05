#pragma once
//Local
#include "AST\AConstant.h"
#include "AST\AInstance.h"
#include "AST\CClass.h"
#include "AST\CFunction.h"
#include "AST\CInstance.h"
#include "AST\CPrototype.h"
#include "OptAST\CClass.h"
#include "OptAST\CConstant.h"
#include "OptAST/CExternal.h"
#include "OptAST\CFunction.h"
#include "OptAST\CGlobalVariable.h"
#include "OptAST\CInstance.h"
#include "OptAST\CPrototype.h"
#include "ASymbol.h"
#include "ICompilerCallback.h"
#include "CParser.h"
#include "CProgramBuffer.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class CCompiler
		{
		private:
			//Members
			bool failed;
			const ICompilerCallback &refCallback;
			CParser *pParser;
			CProgramBuffer programBuffer;
			//SJCLib::CMap<uint32, uint32> funcCallOffsets; //maps program offsets to function symbol indices where to insert the function offset
			//SJCLib::CMap<uint32, uint32> instanceCallOffsets; //maps program offsets to instance symbol indices where to insert the constructor offset
			/*
			SJCLib::CMap<SJCLib::CString, SJCLib::CString> externalsMap; //maps a lower case representation to the correct external name
			*/
			SJCLib::CMap<SJCLib::CString, OptAST::CClass *> classes; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::CClass *> unprocessedClasses; //key is lower case
			SJCLib::CMap<SJCLib::CString, OptAST::CConstant *> constants; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::AConstant *> unprocessedConstants; //key is lower case
			SJCLib::CMap<SJCLib::CString, OptAST::CFunction *> functions; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::CFunction *> unprocessedFunctions; //key is lower case
			SJCLib::CMap<SJCLib::CString, OptAST::CGlobalVariable *> globalVariables; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::AVariable *> unprocessedGlobalVariables; //key is lower case
			SJCLib::CMap<SJCLib::CString, OptAST::CInstance *> instances; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::AInstance *> unprocessedInstances; //key is lower case
			OptAST::CInstance *pInstanceHelp; //the special instance_help symbol
			SJCLib::CMap<SJCLib::CString, OptAST::CPrototype *> prototypes; //key is lower case
			SJCLib::CMap<SJCLib::CString, AST::CPrototype *> unprocessedPrototypes;  //key is lower case
			SJCLib::CLinkedList<const ASymbol *> symbolList;
			SJCLib::CMap<SJCLib::CString, uint32> constantStringsMap; //maps constant strings to their symbol index
			//Functions
			uint32 CalcSize(SVariables *pVariables, uint16 &refnVariables);
			//void Compile(SClass *pClass);
			//void Compile(SConstant *pConstant);
			//void Compile(SConstValue *pConstValue);
			//void Compile(SElseIfs *pElseIfs, SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void Compile(SExpression *pExpr, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void Compile(SFunction *pFunction);
			//void Compile(SInstance *pInstance);
			//EType Compile(SLeftValue *pLeftValue, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void Compile(SPrototype *pPrototype);
			//void Compile(SStatement *pStatement, SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo = NULL);
			//void CompileAssignment(SLeftValue *pLeftValue, SExpression *pExpr, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void CompileCall(const SJCLib::CString &refFuncName, SCallArgs *pArgs, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void CompileGlobalVariable(SVariable *pVariable);
			//EType CompileIdentifier(const SJCLib::CString &refIdentifier, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//EType CompileIdentifier(const SJCLib::CString &refIdentifier, const SArrayIndex *pArrayIndex, const SCompileClassInfo *pClassInfo);
			//EType CompileMemberIdentifier(const SJCLib::CString &refReferenceName, const SJCLib::CString &refMemberName, const SArrayIndex *pArrayIndex, const SJCLib::CMap<SJCLib::CString, SCompileVariableInfo> &refLocalVariables, const SCompileClassInfo *pClassInfo);
			//void CreateSymbol(SFunction *pFunction);
			//void CreateSymbol(SInstance *pInstance);
			//void CreateSymbol(SPrototype *pPrototype);
			void CreateSymbolTable();
			//void CreateSymbolTable(SGlobals *pFirst);
			//uint32 GetConstantStringSymbolIndex(SJCLib::CString &refString);
			uint32 GetSize(SVariable *pVariable);
			//bool IsExternal(const SJCLib::CString &refFuncName, uint32 &refOutSymbolIndex);
			bool ProcessUnprocessedClass(const SJCLib::CString &refName);
			bool ProcessUnprocessedConstant(const SJCLib::CString &refName);
			bool ProcessUnprocessedFunction(const SJCLib::CString &refName);
			bool ProcessUnprocessedGlobalVariable(const SJCLib::CString &refName);
			bool ProcessUnprocessedInstance(const SJCLib::CString &refName);
			bool ProcessUnprocessedPrototype(const SJCLib::CString &refName);
			void PutExternal(OptAST::CExternal *pExternal);
			void PutExternals();
		public:
			//Constructor
			CCompiler(const ICompilerCallback &refCallback);
			//Destructor
			~CCompiler();
			//Functions
			void Compile();
			//void Compile(CCompilePreprocessor &refCompileProc);
			OptAST::CClass *FindClass(const SJCLib::CString &refIdentifier);
			OptAST::CConstant *FindConstant(const SJCLib::CString &refIdentifier);
			OptAST::CFunction *FindFunction(const SJCLib::CString &refIdentifier);
			OptAST::CGlobalVariable *FindGlobalVariable(const SJCLib::CString &refIdentifier);
			OptAST::CInstance *FindInstance(const SJCLib::CString &refIdentifier);
			OptAST::CPrototype *FindPrototype(const SJCLib::CString &refIdentifier);
			uint32 GetConstantStringSymbolIndex(const SJCLib::CString &refString, const ASymbol *pSymbol);
			bool Process(const SJCLib::CString &refInputSrcFile);
			bool ProcessAttribute(SJCLib::CString &refName, OptAST::CClass *pClass);
			bool ProcessClass(const SJCLib::CString &refName);
			bool ProcessConstant(const SJCLib::CString &refName);
			bool ProcessFunction(const SJCLib::CString &refName);
			bool ProcessGlobalVariable(const SJCLib::CString &refName);
			bool ProcessIdentifier(SJCLib::CString &refIdentifier, AST::CClass *pClass = NULL);
			bool ProcessInstance(const SJCLib::CString &refName);
			bool ProcessPrototype(const SJCLib::CString &refName);
			void Release();
			void WriteOutput(SJCLib::AOutputStream &refOutputStream);
			
			//Inline
			inline void Add(OptAST::CClass *pClass)
			{
				this->classes.Insert(pClass->GetName().ToLowercase(), pClass);
			}
			
			inline void Add(OptAST::CConstant *pConstant)
			{
				this->constants.Insert(pConstant->GetName().ToLowercase(), pConstant);
			}

			inline void Add(OptAST::CFunction *pFunction)
			{
				this->functions.Insert(pFunction->GetName().ToLowercase(), pFunction);
			}
			
			inline void Add(OptAST::CGlobalVariable *pVariable)
			{
				this->globalVariables.Insert(pVariable->GetName().ToLowercase(), pVariable);
			}

			inline void Add(OptAST::CInstance *pInstance)
			{
				this->instances.Insert(pInstance->GetName().ToLowercase(), pInstance);
			}

			inline void Add(OptAST::CPrototype *pPrototype)
			{
				this->prototypes.Insert(pPrototype->GetName().ToLowercase(), pPrototype);
			}
			
			inline uint32 AddSymbol(const ASymbol *pSymbol)
			{
				this->symbolList.InsertTail(pSymbol);
				
				return this->symbolList.GetNoOfElements()-1;
			}

			inline void AddUnprocessedInstance(const SJCLib::CString &refName, AST::AInstance *pInstance)
			{
				ASSERT(!this->unprocessedInstances.Contains(refName.ToLowercase()));
				
				this->unprocessedInstances.Insert(refName.ToLowercase(), pInstance);
			}

			inline void AddUnprocessedVariable(const SJCLib::CString &refName, AST::AVariable *pVariable)
			{
				ASSERT(!this->unprocessedGlobalVariables.Contains(refName.ToLowercase()));
				
				this->unprocessedGlobalVariables.Insert(refName.ToLowercase(), pVariable);
			}

			inline const SJCLib::CMap<SJCLib::CString, OptAST::CInstance *> &GetInstances() const
			{
				return this->instances;
			}
		};
	}
}