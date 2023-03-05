#pragma once
//Local
#include "AST\ANode.h"
#include "Daedalus.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class CType : public AST::ANode
		{
		private:
			//Members
			bool isArray;
			uint32 nElements;
			EType type;
			SJCLib::CString className; //for instances
		public:
			//Constructor
			CType();
			CType(const CType &refSource);
			CType(EType type);
			CType(const SJCLib::CString &refClassName);
			//Methods
			uint32 GetSize() const;
			bool IsConvertableTo(const CType &refOther, bool &refNeedCast) const;
			SJCLib::CString ToString() const;

			//Inline
			inline const SJCLib::CString &GetClassName() const
			{
				return this->className;
			}

			inline uint32 GetNumberOfElements() const
			{
				return this->nElements;
			}

			inline EType GetType() const
			{
				return this->type;
			}

			inline void SetNumberOfElements(uint32 nElements)
			{
				this->isArray = true;
				this->nElements = nElements;
			}

			inline void UnsetArray()
			{
				this->isArray = false;
				this->nElements = 1;
			}
		};
	}
}