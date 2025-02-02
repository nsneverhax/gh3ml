#include <Nylon/Core.hpp>
#include "Main.hpp"

const std::string& nylon::ModsDirectory()
{
	return nylon::internal::ModsPath;
}

bool nylon::ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return ReadProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
}
bool nylon::WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return WriteProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
}


std::string nylon::ParseFilepath(std::string_view filepath)
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
