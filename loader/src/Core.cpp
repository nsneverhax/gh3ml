#include <Nylon/Core.hpp>
#include "Main.hpp"

#include <filesystem>

std::filesystem::path nylon::GameDirectory()
{
	return std::filesystem::current_path();
}
std::filesystem::path nylon::NylonDirectory()
{
	return GameDirectory() / "nylon";
}
std::filesystem::path nylon::ModsDirectory()
{
	return NylonDirectory() / "Mods";
}
std::filesystem::path nylon::LogDirectory()
{
	return NylonDirectory() / "Logs";
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
