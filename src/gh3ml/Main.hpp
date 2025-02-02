#pragma once

#include <GH3ML/LogSource.hpp>

#include <map>

#include <GH3ML/ModInfo.hpp>

namespace nylon::internal
{
	extern LogSource Log;
	extern LogSource LogGH3;
	
	extern std::string ModsPath;

	extern std::map<std::string, ModInfo> LoadedMods;
	
	extern bool IsImGuiActive;

	extern void SetupDefaultHooks();
	void SetupCFuncRedirection();

	extern void LoadMods();
	
	void ReadConfig();
	
}