#include <Core.hpp>

bool gh3ml::ReadMemory(const std::uint32_t* baseAddress, std::uint8_t* buffer, size_t size)
{
	return ReadProcessMemory(GetGH3Handle(), baseAddress, buffer, size, NULL);
}
bool gh3ml::WriteMemory(const std::uint32_t* baseAddress, std::uint8_t* buffer, size_t size)
{
	return false;
}