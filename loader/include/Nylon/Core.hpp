#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <filesystem>

namespace nylon
{
	// Vultu: VERSIONING RULES:
	// Major : a change resulting in API differences that are not backwards compatible
	// Minor : a change resulting in API differences that are backwards compatible
	// Patch : backwards compatible bug fixes

	constexpr uint32_t VersionMajor = 0;
	constexpr uint32_t VersionMinor = 2;
	constexpr uint32_t VersionPatch = 0;

	constexpr std::string_view VersionType = "alpha";

	constexpr std::string_view VersionString = "0.2.0-alpha";

	/// <summary>
	/// The current directory of the Guitar Hero III executable
	/// </summary>
	/// <returns></returns>
	std::filesystem::path GameDirectory();
	/// <summary>
	/// The current directory of where Nylon will look for directories and files
	/// </summary>
	/// <returns></returns>
	std::filesystem::path NylonDirectory();
	/// <summary>
	/// The current directory where Nylon will look for mods
	/// </summary>
	/// <returns></returns>
	std::filesystem::path ModsDirectory();
	/// <summary>
	/// The current directory where Nylon will create log files
	/// </summary>
	/// <returns></returns>
	std::filesystem::path LogDirectory();


	const HANDLE GetGH3Handle();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);
	bool WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize = nullptr);

	std::string ParseFilepath(std::string_view filepath);
}