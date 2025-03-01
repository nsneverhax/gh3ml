#pragma once

#include <GH3/Common.hpp>

namespace GH3::Mem
{
	class Allocator;

	class Region
	{
	public:
		void** vftable;
		uint32_t Start;
		uint32_t MinimumFreeMemory;
		uint32_t field0xc;
		uint32_t field0x10;
		uint32_t End;
		Allocator* Allocators;
		void* field0x1c;
	};

	SIZE_ASSERT(Region, 0x20);
}