#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>

namespace nylon
{
	// Vultu: VERSIONING RULES:
	// Major : a change resulting in API differences that are not backwards compatible
	// Minor : a change resulting in API differences that are backwards compatible
	// Patch : backwards compatible bug fixes

	constexpr uint32_t VersionMajor = 0;
	constexpr uint32_t VersionMinor = 2;
	constexpr uint32_t VersionPatch = 0;

	constexpr const char* VersionType = "alpha";

	constexpr const char* VersionString = "0.2.0-alpha";

	const HANDLE GetGH3Handle();
	const std::string& ModsDirectory();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);
	bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);

	std::string ParseFilepath(std::string_view filepath);
}