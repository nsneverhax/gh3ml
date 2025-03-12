#pragma once

#include <GH3/Common.hpp>
#include <GH3/Script/CComponent.hpp>

namespace GH3::Mem
{
	class CCompactPool
	{
		uint8_t* Buffer;
		uint8_t* BufferEnd;
		uint32_t TotalItems;
		uint32_t ItemSize;
		uint32_t CurrentUsedItems;
		void* FreeList;
		char Name[64];
		int32_t MaxUsedItems;
		undefined4 field0x5c;
		undefined4 field0x60;
		undefined4 field0x64;
		undefined2 field0x68;

	public:
		void* Allocate(undefined4 param_1);
	};

	SIZE_ASSERT(CCompactPool, 0x6c);



	void* CCompactPool::Allocate(uint32_t param_1)
	{
		if (FreeList == NULL)
			return NULL;

		CurrentUsedItems++;
		if (MaxUsedItems < CurrentUsedItems)
			MaxUsedItems = CurrentUsedItems;

		return this->FreeList;
	}
}