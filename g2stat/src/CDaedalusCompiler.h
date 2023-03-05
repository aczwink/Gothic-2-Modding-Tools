/*#pragma once
//Local
#include "CDaedalusProgram.h"
#include "CClass.h"
#include "CFunction.h"
#include "CConstant.h"
#include "Daedalus.h"
#include "IDaedalusCallback.h"

namespace SJCPBLib
{
	class CDaedalusCompiler
	{
	private:
		//Variables
		bool compiledSuccessfully;
		IDaedalusCallback *pCallback;
		SJCLib::CArray<byte> program;
		SJCLib::CMap<SJCLib::CString, uint32> functionIndexMap; //maps function name to index... function name is lower case
		SJCLib::CMap<SJCLib::CString, Daedalus::CClass *> classes;
		SJCLib::CMap<SJCLib::CString, Daedalus::CFunction *> functions;
		SJCLib::CMap<SJCLib::CString, Daedalus::CInstance *> instances;
		SJCLib::CMap<SJCLib::CString, Daedalus::CPrototype *> prototypes;
		//Variables which contain work to be done
		//Variables for constants and constvalues, don't touch by hand.. use functions
		SJCLib::CArray<Daedalus::CConstant *> constants; //all kind of constants
		SJCLib::CMap<float, uint32> constantFloats; //maps inline float constants to their index
		SJCLib::CMap<int32, uint32> constantInts; //maps inline int constants to their index
		SJCLib::CMap<SJCLib::CString, uint32> constantStrings; //maps inline string constants to their index
		//Variables that should be acessed ONLY by functions
		SJCLib::CMap<SJCLib::CString, SJCLib::CString> classesCaseMap; //Maps a lower case class name to the defined one
		SJCLib::CMap<SJCLib::CString, SJCLib::CString> prototypesCaseMap; //Maps a lower case prototype name to the defined one
		//Functions
		bool Compile(Daedalus::SArrayIndex *pArrayIndex);
		void Compile(Daedalus::SClass *pClass);
		bool Compile(Daedalus::SConstant *pConstant);
		bool Compile(Daedalus::SConstValue *pConstValue, Daedalus::EType &refOutType);
		bool Compile(Daedalus::SExpression *pExpr, Daedalus::CClass *pClassData, Daedalus::EType &refOutType);
		bool Compile(Daedalus::SFunction *pFunction);
		bool Compile(Daedalus::SInstance *pInstance);
		bool Compile(Daedalus::SLeftValue *pLeftValue, Daedalus::CClass *pClassData);
		void Compile(Daedalus::SPrototype *pPrototype);
		bool Compile(Daedalus::SStatement *pStatement, Daedalus::CClass *pClassData);
		bool Compile(Daedalus::SStatement *pStatement, Daedalus::CFunction &refFunction);
		bool Compile(Daedalus::SStatements *pStatements, Daedalus::CClass *pClassData);
		bool Compile(Daedalus::SStatements *pStatements, Daedalus::CFunction &refFunction);
		bool Compile(Daedalus::SVariable *pVariable); //global context
		bool Compile(Daedalus::SVariable *pVariable, Daedalus::CClass &refClassData); //instance context
		bool Compile(Daedalus::SVariables *pVariables, Daedalus::CClass &refClassData);
		bool CompileAssignment(Daedalus::SLeftValue *pLeftValue, Daedalus::SExpression *pExpr, Daedalus::CClass *pClass);
		bool CompileConstruct(Daedalus::CClass *pClassData);
		bool Preprocess(Daedalus::SGlobals *pGlobal);

		//Inline
		inline Daedalus::CClass *GetClass(SJCLib::CString className)
		{
			ASSERT(this->IsClassDefined(className));

			return this->classes[this->classesCaseMap[className.ToLowercase()]];
		}

		inline Daedalus::CPrototype *GetPrototype(SJCLib::CString prototypeName)
		{
			ASSERT(this->IsPrototypeDefined(prototypeName));

			return this->prototypes[this->prototypesCaseMap[prototypeName.ToLowercase()]];
		}

		inline bool IsClassDefined(SJCLib::CString className)
		{
			return this->classesCaseMap.Contains(className.ToLowercase());
		}

		inline bool IsPrototypeDefined(SJCLib::CString prototypeName)
		{
			return this->prototypesCaseMap.Contains(prototypeName.ToLowercase());
		}
	public:
		//Constructor
		CDaedalusCompiler(const IDaedalusCallback *pCallback);
		//Destructor
		~CDaedalusCompiler();
		//Functions
		void Compile(SJCLib::CString inputSrcFile, CDaedalusProgram &refOutProgram);
		//void GetProgram(CDaedalusProgram &refProgram);
		void Release();
		//Inline
		/*inline bool GetClassInfo(SJCLib::CString className, Daedalus::CClass *&refOutput)
		{
			if(!this->classes.Contains(className))
				return false;
			refOutput = this->classes[className];
			
			return true;
		}*/
//	};
//}