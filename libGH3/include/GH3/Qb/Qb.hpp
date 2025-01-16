#pragma once

#include <cstdint>

#include <GH3/Qb/QbNodeFlags.hpp>
#include <GH3/Qb/QbStructItem.hpp>
#include <GH3/Qb/QbStruct.hpp>


namespace GH3::Functions
{

	typedef QbStruct* (__cdecl* func_qbMalloc)(size_t size, std::uint32_t unknown);
	typedef void* (__cdecl* func_qbArrMalloc)(size_t size, std::uint32_t unknown);
	typedef QbStructItem* (__cdecl* func_qbItemMalloc)(size_t size, std::uint32_t unknown);
	typedef void* (__cdecl* func_qbFree)(void* qbStruct);

	constexpr func_qbMalloc qbMalloc = reinterpret_cast<func_qbItemMalloc>(0x00402370);
	constexpr func_qbArrMalloc qbArrMalloc = reinterpret_cast<func_qbItemMalloc>(0x004373A0);
	constexpr func_qbItemMalloc qbItemMalloc = reinterpret_cast<func_qbItemMalloc>(0x00437410);
	constexpr func_qbFree qbFree = reinterpret_cast<func_qbFree>(0x004023E0);
}