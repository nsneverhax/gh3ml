#include <GH3ML/Config.hpp>
#include "Main.hpp"

#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

uint32_t _versionMajor = 0;
uint32_t _versionMinor = 0;
uint32_t _versionPatch = 0;
bool _unlockFPS = false;
bool _overrideWindProc = false;

std::string_view _versionType = { };

namespace fs = std::filesystem;
namespace ml = gh3ml::internal;

void gh3ml::internal::ReadConfig()
{
	if (!fs::exists(gh3ml::Config::ConfigFilepath))
	{
		// TODO: this
	}


	std::ifstream t(gh3ml::Config::ConfigFilepath);
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
	if (object.contains("overrindWindProc"))
		_overrideWindProc = object["overrindWindProc"].asBool().unwrap();
}

uint32_t gh3ml::Config::VersionMajor()
{
	return _versionMajor;
}
uint32_t gh3ml::Config::VersionMinor()
{
	return _versionMinor;
}
uint32_t gh3ml::Config::VersionPatch()
{
	return _versionPatch;
}
const std::string_view& gh3ml::Config::VersionType()
{
	return _versionType;
}
bool gh3ml::Config::UnlockFPS()
{
	return _unlockFPS;
}
bool gh3ml::Config::OverrideWindProc()
{
	return _overrideWindProc;
}
