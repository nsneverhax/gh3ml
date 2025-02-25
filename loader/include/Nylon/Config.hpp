#pragma once

#include <Nylon/Core.hpp>
#include <Nylon/VersionInfo.hpp>

#include <filesystem>

namespace nylon::config
{
	enum class WindowStyle
	{
		Fullscreen,
		Windowed,
		BorderlessWindowed,
		BorderlessFullscreen
	};

	std::filesystem::path ConfigFilepath();

	const VersionInfo& Version();
	bool UnlockFPS();
	bool OpenConsole();
	bool AllowQScriptPrintf();
	WindowStyle GameWindowStyle();
}
