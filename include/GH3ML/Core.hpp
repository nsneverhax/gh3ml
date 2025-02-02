#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace nylon
{
	const HANDLE GetGH3Handle();
	const std::string& ModsDirectory();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);
	bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);

	std::string ParseFilepath(std::string_view filepath);
}