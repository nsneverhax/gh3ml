#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <filesystem>

#include <chrono>
#include <type_traits>

namespace nylon
{
	std::string_view CompileDate();
	std::string_view CompileTime();

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
	/// <summary>
	/// The current directory where Nylon will look for resources
	/// </summary>
	/// <returns></returns>
	std::filesystem::path ResourcesDirectory();

	/// <summary>
	/// The current directory where Nylon will look for portable resources
	/// </summary>
	/// <returns></returns>
	std::filesystem::path PortableDirectory();

	/// <summary>
	/// The current directory where Nylon will emulate MemoryCard functions
	/// </summary>
	/// <returns></returns>
	//std::filesystem::path MemorycardDirectory();

	/// <summary>
	/// Is Nylon in portable mode?
	/// </summary>
	/// <returns></returns>
	bool IsPortableMode();

	bool IsWine();
	std::string_view WineVersion();

	const HANDLE GH3Handle();

	bool ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualWritten = nullptr);

	bool WriteMemory(uintptr_t baseAddress, uint8_t* buffer, size_t size, size_t* actualWritten = nullptr);

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	inline bool WriteMemory(uintptr_t baseAddress, T value, size_t* actualWritten = nullptr)
	{
		return WriteMemory(baseAddress, reinterpret_cast<uint8_t*>(&value), sizeof(value), actualWritten);
	}

	/// <summary>
	/// not yet functional! 
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	std::string ParseFilepath(std::string_view filepath);
}