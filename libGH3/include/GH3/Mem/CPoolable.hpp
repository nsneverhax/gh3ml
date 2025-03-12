#pragma once

#include <GH3/Common.hpp>

#include <GH3/Mem/CCompactPool.hpp>

namespace GH3::Mem
{
	// V: Are these static members?

	// template <typename T> <- how source looks
	template <typename T, uint32 TList, uint32 TListIndex>
	class CPoolable
	{
		static inline uint32 ListAddress = TList;
		static inline uint32 ListIndexAddress = TListIndex;

		static CCompactPool* Pools[2];
		static int32_t field0x04;
		static bool PoolCreated[2];
		static int32_t CurrentPool;

		// it wouldn't let me define this outside of the class

		TODO("Need to implement \"Mem::CPoolable<>::operator new\"");
		void* operator new(size_t size, undefined4 param_2)
		{
			CCompactPool* list = *reinterpret_cast<CCompactPool**>(ListAddress);
			uint32 listIndex = *reinterpret_cast<uint32*>(ListIndexAddress);

			CCompactPool* item = (&list)[listIndex];
			if (item != NULL)
			{
				auto allocated = item.Allocate();
			}


			return (void*)NULL;
		}

	};



}