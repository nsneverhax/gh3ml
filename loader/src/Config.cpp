#include <Nylon/Config.hpp>
#include "Main.hpp"

#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

namespace fs = std::filesystem;
namespace in = nylon::internal;
namespace cfg = nylon::config;

nylon::VersionInfo _versionInfo = { };

bool _unlockFPS = false;
bool _openConsole = false;
bool _allowScriptPrintf = false;
cfg::WindowStyle _windowStyle = cfg::WindowStyle::Fullscreen;

bool _configMalformed = false;

void UnwrapValue(matjson::Value& value, std::string_view name, bool* outValue, bool defaultValue)
{
	if (outValue == nullptr)
		return;

	*outValue = defaultValue;
	try
	{
		if (!value.contains(name.data()))
			return;

		*outValue = value[name.data()].asBool().unwrap();

		return;
	}
	catch (...)
	{
		_configMalformed = true;
		return;
	}
}
void UnwrapValue(matjson::Value& value, std::string_view name, uint32_t* outValue, uint32_t defaultValue)
{
	if (outValue == nullptr)
		return;

	*outValue = defaultValue;
	try
	{
		if (!value.contains(name.data()))
			return;

		*outValue = value[name.data()].asUInt().unwrap();

		return;
	}
	catch (...)
	{
		_configMalformed = true;
		return;
	}
}

void in::ReadConfig()
{
	_configMalformed = true;

	if (!fs::exists(cfg::ConfigFilepath()))
	{
		in::Log.Warn("Unable to find \"{}\" so it will be remade.", cfg::ConfigFilepath().string());

	}

	std::ifstream t(cfg::ConfigFilepath().c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();

	auto result = matjson::parse(buffer);

	if (!result)
	{
		in::Log.Warn("Unable to parse \"{}\" so it will be remade.", cfg::ConfigFilepath().string());

		return;
	}

	matjson::Value object = result.unwrap();

	if (object.contains("versionInfo"))
	{
		auto versionValue = object["versionInfo"];
		UnwrapValue(versionValue, "major", &_versionInfo.Major, nylon::Version().Major);
		UnwrapValue(versionValue, "minor", &_versionInfo.Minor, nylon::Version().Minor);
		UnwrapValue(versionValue, "revision", &_versionInfo.Revision, nylon::Version().Revision);
		UnwrapValue(versionValue, "type", reinterpret_cast<uint32_t*>(&_versionInfo.Type), (uint32_t)nylon::Version().Type);

		if (_versionInfo != nylon::Version())
			_configMalformed = true;
	}
	else
		_configMalformed = true;

	UnwrapValue(object, "unlockfps", &_unlockFPS, false);
	UnwrapValue(object, "openGH3Console", &_openConsole, true);
	UnwrapValue(object, "allowQScriptPrintf", &_allowScriptPrintf, true);

	UnwrapValue(object, "windowStyle", reinterpret_cast<uint32_t*>(&_windowStyle), (uint32_t)cfg::WindowStyle::Windowed);

	if (_configMalformed)
	{
		in::Log.Warn("\"{}\" was malformed or the version didn't match, so it will be remade using known values.", cfg::ConfigFilepath().string());
		WriteConfig();
	}
}

void in::WriteConfig()
{
	try
	{
		auto obj = matjson::makeObject(
			{
				{ "openGH3Console", true },
				{ "allowQScriptPrintf", true },
				{ "windowStyle", 1 },
				{ "pluginLogType", 1 },
				{ "unlockfps", false },
				{ "versionInfo", matjson::makeObject({
					{ "major", nylon::Version().Major},
					{ "minor", nylon::Version().Minor },
					{ "revision", nylon::Version().Revision },
					{ "type", (uint32_t)nylon::Version().Type },
					}),

				}
			}
		);

		auto dumped = obj.dump();
		std::ofstream dumpFile(nylon::NylonDirectory() / "config.json");

		dumpFile << dumped.c_str();
		dumpFile.close();
	}
	catch (...)
	{
		Log.Error("There was an unknown error writing the config file!");
	}
}

std::filesystem::path cfg::ConfigFilepath()
{
	return nylon::NylonDirectory() / "config.json";
}

const nylon::VersionInfo& cfg::Version()
{
	return _versionInfo;
}

bool cfg::UnlockFPS()
{
	return _unlockFPS;
}

bool cfg::OpenConsole()
{
	return _openConsole;
}
bool cfg::AllowQScriptPrintf()
{
	return _allowScriptPrintf;
}
cfg::WindowStyle cfg::GameWindowStyle()
{
	return _windowStyle;
}