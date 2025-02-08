#pragma once

#include <Nylon/Core.hpp>

namespace nylon::Config
{
	enum class WindowStyle
	{
		Fullscreen,
		Windowed,
		BorderlessWindowed,
		BorderlessFullscreen
	};

	constexpr const char* ConfigFilepath = "nylon/config.json";

	uint32_t VersionMajor();
	uint32_t VersionMinor();
	uint32_t VersionPatch();
	std::string_view VersionType();
	bool UnlockFPS();
	bool OpenConsole();
	bool AllowQScriptPrintf();
}
