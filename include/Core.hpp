#pragma once

#include <Windows.h>
#include <cstdint>

namespace gh3ml
{
	const HANDLE GetGH3Handle();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size);
	bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size);
}