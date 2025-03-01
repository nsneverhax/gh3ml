#pragma once

#include <GH3/Common.hpp>

#include <GH3/Mem/Allocator.hpp>

namespace GH3::Mem
{
	class Heap : public Allocator
	{
		undefined4 field0x7c;
		uint32_t MaxAddress;
	};
}