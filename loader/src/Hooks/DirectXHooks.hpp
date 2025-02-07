#pragma once

#include <cstdint>
#include <windows.h>
#include <d3d9.h>

namespace nylon::internal
{ 
	using D3D9DevicePresent = HRESULT(__stdcall*)(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);

	bool CreateDirectXHooks();


}