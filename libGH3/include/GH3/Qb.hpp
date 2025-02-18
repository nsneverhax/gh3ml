#pragma once

#include <cstdint>

#include "Keys.hpp"
#include "Qb/QbStruct.hpp"
#include "Qb/CScript.hpp"


/*
	typedef QbStruct* (__cdecl *func_qbMalloc)(size_t size, std::uint32_t unknown);
	typedef void* (__cdecl *func_qbArrMalloc)(size_t size, std::uint32_t unknown);
	typedef QbStructItem* (__cdecl *func_qbItemMalloc)(size_t size, std::uint32_t unknown);
	typedef void* (__cdecl *func_qbFree)(void* qbStruct);

	static func_qbMalloc qbMalloc = reinterpret_cast<func_qbMalloc>(0x00402370);
	static func_qbArrMalloc qbArrMalloc = reinterpret_cast<func_qbArrMalloc>(0x004373A0);
	static func_qbItemMalloc qbItemMalloc = reinterpret_cast<func_qbItemMalloc>(0x00437410);
	static func_qbFree qbFree = reinterpret_cast<func_qbFree>(0x004023E0);
*/