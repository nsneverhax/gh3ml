#pragma once

// This headers includes all of the extremely basic functionality that anything in GH3ML may need


#include <Windows.h>
#include <cstdint>
#include <string>

namespace gh3ml
{

	// Vultu: VERSIONING RULES:
	// Major : a change resulting in API differences that are not backwords compatible
	// Minor : a change resulting in API differences that are backwards compatible
	// Patch : backwards compatible bug fixes

	constexpr uint32_t VersionMajor = 0;
	constexpr uint32_t VersionMinor = 1;
	constexpr uint32_t VersionPatch = 0;

	constexpr const char* VersionType = "alpha";

	constexpr const char* VersionString = "0.1.0-alpha";


	const HANDLE GetGH3Handle();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size);
	bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size);
}