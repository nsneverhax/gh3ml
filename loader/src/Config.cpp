#include <Nylon/Config.hpp>
#include "Main.hpp"

#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

uint32_t _versionMajor = 0;
uint32_t _versionMinor = 0;
uint32_t _versionPatch = 0;
uint32_t _versionType = 0;

bool _unlockFPS = false;
bool _openConsole = false;
bool _allowScriptPrintf = false;

namespace fs = std::filesystem;
namespace in = nylon::internal;
namespace cfg = nylon::Config;

void nylon::internal::ReadConfig()
{
	bool malformed = false;

	if (!fs::exists(cfg::ConfigFilepath()))
	{
		in::Log.Warn("Unable to find \"{}\" so it will be remade.", cfg::ConfigFilepath());

	}


	std::ifstream t(cfg::ConfigFilepath().c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();

	auto result = matjson::parse(buffer);

	if (!result)
	{
		in::Log.Warn("Unable to parse \"{}\" so it will be remade.", cfg::ConfigFilepath());

		return;
	}

	matjson::Value object = result.unwrap();

	if (object.contains("versionInfo"))
	{
		_versionMajor = object["versionInfo"]["major"].asUInt().unwrap();
		_versionMinor = object["versionInfo"]["minor"].asUInt().unwrap();
		_versionPatch = object["versionInfo"]["revision"].asUInt().unwrap();
		_versionType = object["versionInfo"]["type"].asUInt().unwrap();
	}
	else
		malformed = true;

	if (object.contains("unlockfps"))
		_unlockFPS = object["unlockfps"].asBool().unwrap();
	else
		malformed = true;

	if (object.contains("openGH3Console"))
		_openConsole = object["openGH3Console"].asBool().unwrap();
	else
		malformed = true;

	if (object.contains("allowQScriptPrintf"))
		_allowScriptPrintf = object["allowQScriptPrintf"].asBool().unwrap();
	else
		malformed = true;

	if (malformed)
	{
		in::Log.Warn("\"{}\" was malformed, so it will be remade using known values.", cfg::ConfigFilepath());

	}
}

std::filesystem::path ConfigFilepath()
{
	return nylon::NylonDirectory() / "config.json";
}

uint32_t cfg::VersionMajor()
{
	return _versionMajor;
}
uint32_t cfg::VersionMinor()
{
	return _versionMinor;
}
uint32_t cfg::VersionPatch()
{
	return _versionPatch;
}
uint32_t cfg::VersionType()
{
	return _versionType;
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