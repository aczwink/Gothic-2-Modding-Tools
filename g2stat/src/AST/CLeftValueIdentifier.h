#pragma once
//Local
#include "AExpression.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		namespace OptAST
		{
			//Forward declarations
			class CConstant;
			class CFunction;
			class CGlobalVariable;
		}

		namespace AST
		{
			//Forward declarations
			class CInstance;

			enum EIdentifierType
			{
				IDENTIFIERTYPE_ATTRIBUTE,
				IDENTIFIERTYPE_CONSTANT,
				IDENTIFIERTYPE_FUNCTION,
				IDENTIFIERTYPE_GLOBALVARIABLE,
				IDENTIFIERTYPE_INSTANCE,
				IDENTIFIERTYPE_LOCALVARIABLE,
				IDENTIFIERTYPE_NOFUNC,
				IDENTIFIERTYPE_NULL,
				IDENTIFIERTYPE_SLF,
			};

			class CLeftValueIdentifier : public AExpression
			{
			protected:
				//Members
				SJCLib::CString identifier;
				EIdentifierType type;
				OptAST::CConstant *pConstant;
				OptAST::CFunction *pFunction;
				OptAST::CInstance *pInstance;
				OptAST::CClass *pClass;
				OptAST::CLocalVariable *pLocalVariable;
				OptAST::CGlobalVariable *pGlobalVar;
				bool hasCast;
				CType castToType;
			public:
				//Constructor
				CLeftValueIdentifier(const SJCLib::CString &refIdentifier, const SJCLib::CWString &refFileName, uint32 lineNumber);
				//Destructor
				~CLeftValueIdentifier();
				//Methods
				AExpression *GetOptimizedExpression(CCompiler &refCompiler);
				OptAST::AExpression *GetTranslatedExpression(CCompiler &refCompiler) const;
				CType GetType() const;
				virtual bool Process(SJCLib::CMap<SJCLib::CString, OptAST::CLocalVariable *> &refLocalVariables, OptAST::CClass *pClass, OptAST::CInstance *pInstance, CCompiler &refCompiler, const ICompilerCallback &refCallback);
				void SetCastTo(const CType &refType);
			};
		}
	}
}