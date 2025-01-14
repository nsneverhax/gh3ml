#pragma once

#include <Windows.h>
#include <cstdint>

namespace gh3ml
{
	const HANDLE GetGH3Handle();

	bool ReadMemory(const std::uint32_t* baseAddress, std::uint8_t* buffer, size_t size);
	bool WriteMemory(const std::uint32_t* baseAddress, std::uint8_t* buffer, size_t size);
}