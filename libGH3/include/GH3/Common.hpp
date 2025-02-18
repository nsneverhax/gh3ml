#pragma once

#define SIZE_ASSERT(x, s) static_assert(sizeof(x) == s)

#include <cstdint>

#include <GH3/Keys.hpp>

namespace GH3
{
	typedef std::uint8_t  undefined1;
	typedef std::uint16_t undefined2;
	typedef std::uint32_t undefined4;
	typedef std::uint64_t undefined8;
}