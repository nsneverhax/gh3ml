#pragma once

#include <Nylon/Hook.hpp>

#include <GH3/Qb/CScript.hpp>
#include <GH3/Script/CStruct.hpp>

#include <cstdint>
#include <windows.h>
#include <d3d9.h>

namespace nylon::internal
{
	namespace binding
	{
		using CFunc_PrintStruct = nylon::hook::Binding<0x00530970, nylon::hook::cconv::CDecl, bool, GH3::Script::CStruct*, GH3::Script::CScript*>;
		using CFunc_PrintF = nylon::hook::Binding<0x00530940, nylon::hook::cconv::CDecl, bool, GH3::Script::CStruct*, GH3::Script::CScript*>;
		using CFunc_LoadPak = nylon::hook::Binding<0x004a1780, nylon::hook::cconv::CDecl, bool, GH3::Script::CStruct*, GH3::Script::CScript*>;

		using CFunc_LoadTexture = nylon::hook::Binding<0x00541f40, nylon::hook::cconv::CDecl, bool, GH3::Script::CStruct*, GH3::Script::CScript*>;

		// using CFunc_MemCardSystemInitialize = nylon::hook::Binding<0x0043c1b0, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::Script::CScript*>;

		using CFuncs_SetGemConstants = nylon::hook::Binding<0x0041b930, nylon::hook::cconv::CDecl, bool, GH3::Script::CStruct*, GH3::Script::CScript*>;
	}

	void CreateCFuncHooks();

	using D3D9DevicePresent = HRESULT(__stdcall*)(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);

	void SetupDefaultHooks();
	bool CreateDirectXHooks();

	void SetupCEngineHooks();
	void SetupGuitarFuncsHooks();

	void SetupGfxCScreenFXManagerHooks();
}