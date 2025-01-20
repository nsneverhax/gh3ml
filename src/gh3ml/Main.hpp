#pragma once

#include <GH3ML/LogSource.hpp>

namespace gh3ml::internal
{
	extern LogSource Log;
	extern LogSource LogGH3;

	static void SetupCFuncRedirection();

}