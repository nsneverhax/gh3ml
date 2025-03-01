#pragma once

#include <GH3/Common.hpp>

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
	};

	SIZE_ASSERT(CCompactPool, 0x6c);
}