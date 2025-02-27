#pragma once

#ifdef NO_SIZE_ASSERT
#define SIZE_ASSERT(x, s)
#else
#define SIZE_ASSERT(x, s) static_assert(sizeof(x) == s)
#endif // NO_SIZE_ASSERT


#define GH3_API __declspec(dllexport)

#include <GH3/Keys.hpp>

#include <cstdint>
#include <string>

namespace GH3
{
	typedef std::uint8_t  undefined1;
	typedef std::uint16_t undefined2;
	typedef std::uint32_t undefined4;
	typedef std::uint64_t undefined8;
}