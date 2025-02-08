#include <Nylon/Config.hpp>
#include "Main.hpp"

#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

uint32_t _versionMajor = 0;
uint32_t _versionMinor = 0;
uint32_t _versionPatch = 0;
bool _unlockFPS = false;
bool _openConsole = false;
bool _allowScriptPrintf = false;

std::string_view _versionType = { };

namespace fs = std::filesystem;
namespace ml = nylon::internal;

void nylon::internal::ReadConfig()
{
	if (!fs::exists(nylon::Config::ConfigFilepath))
	{
		// TODO: this
	}


	std::ifstream t(nylon::Config::ConfigFilepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();

	auto result = matjson::parse(buffer);

	if (!result)
	{
		return;
	}

	matjson::Value object = result.unwrap();

	_versionMajor = object["versionInfo"]["major"].asUInt().unwrap();
	_versionMinor = object["versionInfo"]["minor"].asUInt().unwrap();
	_versionPatch = object["versionInfo"]["patch"].asUInt().unwrap();
	_versionType = object["versionInfo"]["type"].asString().unwrap();

	if (object.contains("unlockfps"))
		_unlockFPS = object["unlockfps"].asBool().unwrap();

	if (object.contains("openGH3Console"))
		_openConsole = object["openGH3Console"].asBool().unwrap();

	if (object.contains("allowQScriptPrintf"))
		_allowScriptPrintf = object["allowQScriptPrintf"].asBool().unwrap();
}

uint32_t nylon::Config::VersionMajor()
{
	return _versionMajor;
}
uint32_t nylon::Config::VersionMinor()
{
	return _versionMinor;
}
uint32_t nylon::Config::VersionPatch()
{
	return _versionPatch;
}
std::string_view nylon::Config::VersionType()
{
	return _versionType;
}
bool nylon::Config::UnlockFPS()
{
	return _unlockFPS;
}

bool nylon::Config::OpenConsole()
{
	return _openConsole;
}
bool nylon::Config::AllowQScriptPrintf()
{
	return _allowScriptPrintf;
}