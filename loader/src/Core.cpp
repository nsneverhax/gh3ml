#include <Nylon/Core.hpp>
#include <Nylon/Internal/Main.hpp>

#include <filesystem>

constexpr static uint8_t BuildDateMonth()
{
	char firstChar = __DATE__[0];
	char thirdChar = __DATE__[2];
	if (firstChar == 'J')
	{
		if (__DATE__[1] == 'a') // Jan
			return 0x0;
		if (thirdChar == 'n') // Jun
			return 0x5;
		if (thirdChar == 'l') // Jul
			return 0x6;
	}

	if (firstChar == 'F') // Feb
		return 0x1;

	if (firstChar == 'M')
	{
		if (thirdChar == 'r') // Mar
			return 0x2;
		if (thirdChar == 'y') // May
			return 0x4;
	}

	if (firstChar == 'A')
	{
		if (thirdChar == 'r') // Apr
			return 0x3;
		if (thirdChar == 'g') // Aug
			return 0x7;
	}

	if (firstChar == 'S') // Sep
		return 0x8;

	if (firstChar == 'O') // Oct
		return 0x9;

	if (firstChar == 'N') // Nov
		return 0xA;

	if (firstChar == 'D') // Dec
		return 0xB;
}

std::string_view nylon::CompileDate()
{
	return __DATE__;
}
std::string_view nylon::CompileTime()
{
	return __TIME__;
}


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
std::filesystem::path nylon::LogsDirectory()
{
	return NylonDirectory() / "Logs";
}
std::filesystem::path nylon::ResourcesDirectory()
{
	return NylonDirectory() / "Resources";
}
std::filesystem::path nylon::ProfilesDirectory()
{
	return NylonDirectory() / "Profiles";
}

bool nylon::IsPortableMode()
{
	return false;
}
std::filesystem::path nylon::PortableDirectory()
{
	return NylonDirectory() / "Portable";
}


bool nylon::ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return ReadProcessMemory(GH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
}
bool nylon::WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size, size_t* actualSize)
{
	return WriteProcessMemory(GH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, reinterpret_cast<SIZE_T*>(actualSize));
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
