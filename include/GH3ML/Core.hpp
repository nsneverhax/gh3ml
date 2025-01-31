#pragma once

// This headers includes all of the extremely basic functionality that anything in GH3ML may need


#include <Windows.h>
#include <cstdint>
#include <string>

namespace gh3ml
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

	extern const std::string& GetModsDirectory();

	/// <summary>
	/// Parses a string as a filepath, and resolves any variables in it
	/// </summary>
	/// <returns></returns>
	extern std::string ParseFilepath(const std::string& filepath);

	extern bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);
	extern bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);
}