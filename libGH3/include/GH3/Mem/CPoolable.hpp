#pragma once

#include <GH3/Common.hpp>

#include <GH3/Mem/CCompactPool.hpp>

namespace GH3::Mem
{
	// V: Are these static members?
	class CPoolable
	{
		CCompactPool* Pools[2];
		int32_t field0x04;
		bool PoolCreated[2];
		int32_t CurrentPool;
	};
}