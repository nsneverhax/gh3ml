#include <GH3ML/Core.hpp>
#include "Main.hpp"

extern const std::string& gh3ml::GetModsDirectory()
{
	return gh3ml::internal::ModsPath;
}

bool gh3ml::ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return ReadProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
}
bool gh3ml::WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return WriteProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
}


std::string gh3ml::ParseFilepath(const std::string& filepath)
{
	int whitespaceCount = 0;

	// Vultu: Trim leading whitespace
	for (auto i = 0; i < filepath.length(); i++)
	{
		if (filepath[i] == ' ')
			whitespaceCount++;
		else
			break;
	}


	return std::string();
}