#pragma once

namespace SJCPBLib
{
	namespace Daedalus
	{
		class AReferenceable
		{
		private:
			//Members
			uint32 nReferences;
		public:
			//Constructor
			inline AReferenceable()
			{
				this->nReferences = 0;
			}

			//Inline
			inline uint32 GetReferenceCount() const
			{
				return this->nReferences;
			}

			inline void IncrementRefCount()
			{
				this->nReferences++;
			}
		};
	}
}