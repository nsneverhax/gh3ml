#pragma once

#include <GH3ML/Core.hpp>


namespace gh3ml::Config
{
	enum class WindowStyle
	{
		Fullscreen,
		Windowed,
		BorderlessWindowed,
		BorderlessFullscreen
	};

	constexpr const char* ConfigFilepath = "gh3ml/config.json";

	uint32_t GetVersionMajor();
	uint32_t GetVersionMinor();
	uint32_t GetVersionPatch();
	const std::string_view& GetVersionType();

}