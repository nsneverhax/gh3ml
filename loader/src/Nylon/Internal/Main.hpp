#pragma once

#include <filesystem>
#include <map>

#include <GH3/Keys.hpp>

#include <Nylon/LogSource.hpp>
#include <Nylon/ModInfo.hpp>

#define _STR(x) #x
#define STR(x) _STR(x)
#define TODO(x) __pragma(message("TODO: " _STR(x) " :: " __FILE__ "@" STR(__LINE__)))

namespace nylon::internal
{
	extern LogSource Log;
	extern LogSource LogGH3;
	
	extern std::map<std::string, ModInfo> LoadedMods;
	
	void PushLogTask(std::string_view name);
	void PopLogTask();


	void SetupCFuncRedirection();

	void LoadMods();
	
	void ReadConfig();
	void WriteConfig();

	void ReadKeyAssociations(std::filesystem::path path);

	extern std::map<GH3::CRCKey, std::string> KeyAssociations;
}
