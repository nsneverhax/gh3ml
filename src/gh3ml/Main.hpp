#pragma once

#include <GH3ML/LogSource.hpp>

namespace gh3ml::internal
{
	extern LogSource Log;
	extern LogSource LogGH3;

	extern void SetupDefaultHooks();
	void SetupCFuncRedirection();
	
	
	void ReadConfig();
	
}