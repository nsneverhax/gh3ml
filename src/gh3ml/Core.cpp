#include <GH3ML/Core.hpp>
#include "Main.hpp"

extern const std::string& gh3ml::GetModsDirectory()
{
	return gh3ml::internal::ModsPath;
}

bool gh3ml::ReadMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size)
{
	return ReadProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, NULL);
}
bool gh3ml::WriteMemory(uintptr_t baseAddress, std::uint8_t* buffer, size_t size)
{
	return WriteProcessMemory(GetGH3Handle(), reinterpret_cast<void*>(baseAddress), buffer, size, NULL);
}