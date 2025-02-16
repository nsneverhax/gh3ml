#pragma once

#include <Nylon/LogSource.hpp>

#include <map>

#include <Nylon/ModInfo.hpp>

namespace nylon::internal
{
	extern LogSource Log;
	extern LogSource LogGH3;
	
	extern std::map<std::string, ModInfo> LoadedMods;
	
	extern void SetupDefaultHooks();
	void SetupCFuncRedirection();

	extern void LoadMods();
	
	void ReadConfig();
	
}
