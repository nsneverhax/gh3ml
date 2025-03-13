#pragma once


#define NX_ENVIROMENT_UNKNOWN

#if _WIN32 || _WIN64
#if _WIN32 && _WIN64
#error "Invalid NX Windows Enviroment!"
#endif
#if _WIN32
#define NX_ENVIROMENT_WIN32
#else
#define NX_ENVIROMENT_WIN64
#endif
#undef NX_ENVIROMENT_UNKNOWN
#endif


#ifdef NX_ENVIROMENT_UNKNOWN
#error "Unknown NX Enviroment"
#endif // NX_ENVIROMENT_UNKNOWN


#ifdef NO_SIZE_ASSERT
#define SIZE_ASSERT(x, s)
#else
#define SIZE_ASSERT(x, s) static_assert(sizeof(x) == s)
#define SIZE_ASSERT_FUZZYS(x, s, a) static_assert(sizeof(x) == ((s / a) * a) + (((s % a) != 0) * a))
#define SIZE_ASSERT_FUZZYX(x, s, a) static_assert((sizeof(x) / a * a) + (((x % a) != 0) * a) == s)
#endif // NO_SIZE_ASSERT

#define GH3Func(name, address, cconv, ret) using name = ret(cconv*)

#define FAST_GH3_API

#define GH3_API __declspec(dllexport)

#include <GH3/Keys.hpp>
#include <GH3/CRC.hpp>

#include <cstdint>
#include <string>

#include <iostream>

#define _STR(x) #x
#define STR(x) _STR(x)
#define TODO(x) __pragma(message("TODO: " _STR(x) " :: " __FILE__ "@" STR(__LINE__)))

#define NEEDS_IMPLEMENTATION() std::cout << __FUNCTION__ << " in " << __FILE__  << " @ " << STR(__LINE__) << " NEEDS IMPLEMENTATION." << std::endl; \
	__pragma(message("**** IMPLEMENTATION NEEDED **** " __FUNCTION__  " in " __FILE__ "\" @ " STR(__LINE__)))

#define NEEDS_TESTING() std::cout << __FUNCTION__ << " in " << __FILE__  << " @ " << STR(__LINE__) << " NEEDS TO BE TESTED. Please report if it is working!" << std::endl; \
	__pragma(message("**** TESTING NEEDED **** " __FUNCTION__  " in \"" __FILE__ "\" @ " STR(__LINE__)))

namespace GH3
{

	using undefined1 = std::uint8_t;
	using undefined2 = std::uint16_t;
	using undefined4 = std::uint32_t;
	using undefined8 = std::uint64_t;


	// V: I stole these types from my game engine
	// Eventually this should be able to target non C++11+

	typedef std::uint8_t	uint8;
	typedef std::int8_t		int8;

	typedef std::uint16_t	uint16;
	typedef std::int16_t	int16;

	typedef std::uint32_t	uint32;
	typedef std::int32_t	int32;

	typedef std::uint64_t	uint64;
	typedef std::int64_t	int64;


	class CStruct;
	class CScript;


	using CFunction = bool(__stdcall*)(CStruct*, CScript*);


	template<uint32 size>
	struct UnknownStructure
	{
		uint8 memory[size];

		template <class T>
		T GetValue(uint32 address)
		{

		}
	};
}