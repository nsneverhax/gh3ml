#pragma once

#include <Nylon/Hook.hpp>

namespace nylon::internal
{
	enum
	{
		KEY_ASPYR_WIN_INIT = 0x823459C8, // ?Init@Win@Aspyr@@YA?AW4Error@12@W4Mode@12@@Z
		KEY_ASPYR_GET_CONFIG_NUMBER_W = 0x53A1FA16,// ?GetConfigNumber@Win@Aspyr@@YANPB_WN@Z
		KEY_ASPYR_GET_CONFIG_NUMBER = 0xEBBF1149, // ?GetConfigNumber@Win@Aspyr@@YANPBDN@Z
	};


	void SetupAspyrHooks();
}