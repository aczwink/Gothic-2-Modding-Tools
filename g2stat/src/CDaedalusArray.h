/*#pragma once
//Local
#include "Daedalus.h"

namespace SJCPBLib
{
	namespace Daedalus
	{
		class CDaedalusArray
		{
		private:
			//Variables
			EType type;
			uint32 nElements;
			UValue *pValues;
		public:
			//Constructor
			CDaedalusArray(EType type, uint32 nElements);
			//Destructor
			~CDaedalusArray();
			//Operators
			UValue &operator[](uint32 index);
			//Functions
			void Release();
			SJCLib::CString ToString() const;
			//Inline
			inline uint32 GetNumberOfElements() const
			{
				return this->nElements;
			}
		};
	}
}*/