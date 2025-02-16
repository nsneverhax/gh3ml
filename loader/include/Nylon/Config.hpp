#pragma once

#include <Nylon/Core.hpp>

#include <filesystem>

namespace nylon::Config
{
	enum class WindowStyle
	{
		Fullscreen,
		Windowed,
		BorderlessWindowed,
		BorderlessFullscreen
	};
	
	std::filesystem::path ConfigFilepath();

	uint32_t VersionMajor();
	uint32_t VersionMinor();
	uint32_t VersionPatch();
	uint32_t VersionType();
	bool UnlockFPS();
	bool OpenConsole();
	bool AllowQScriptPrintf();
}
