#pragma once

#include <Nylon/Hook.hpp>

#include <cstdint>
#include <windows.h>
#include <d3d9.h>

namespace nylon::internal
{

	enum
	{
		KEY_ASPYR_WIN_INIT = 0x823459C8, // ?Init@Win@Aspyr@@YA?AW4Error@12@W4Mode@12@@Z
		KEY_ASPYR_GET_CONFIG_NUMBER_W = 0x53A1FA16,// ?GetConfigNumber@Win@Aspyr@@YANPB_WN@Z
		KEY_ASPYR_GET_CONFIG_NUMBER = 0xEBBF1149, // ?GetConfigNumber@Win@Aspyr@@YANPBDN@Z
	};

	using D3D9DevicePresent = HRESULT(__stdcall*)(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);

	void SetupDefaultHooks();
	bool CreateDirectXHooks();
	void SetupAspyrHooks();

	void SetupCEngineHooks();
	void SetupGuitarFuncsHooks();
}