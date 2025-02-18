#pragma once

#include <GH3/Common.hpp>

namespace GH3
{
	class CScript
	{
		uint32_t gap; // 0 ??
		CScript* Next = nullptr;
		CScript* Previous = nullptr;

		uint8_t* StructScript;

	};
}