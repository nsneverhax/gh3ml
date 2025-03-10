#include <Nylon/Internal/Main.hpp>
#include "Hooks.hpp"
#include <Nylon/Hook.hpp>
#include <GH3/DirectX.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <GH3/Addresses.hpp>
#include <Nylon/Config.hpp>

#include <D3dx9tex.h>

#include "../Imgui/Imgui.hpp"

constexpr int PresentHookID = 2;
constexpr int ResetHookID = 3;


constexpr int KeyboardID = 200;
constexpr int MouseID = 300;

LPDIRECT3DTEXTURE9 conduitTapTextures[] = { nullptr, nullptr };

HRESULT Reset(void* self, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();


	auto ret = nylon::hook::Orig<ResetHookID, nylon::hook::cconv::STDCall, HRESULT>(self, pPresentationParameters);

	if (!ImGui_ImplDX9_CreateDeviceObjects())
		nylon::internal::Log.Error("Unable to Create ImGui Device Objects");
	else
		nylon::internal::Log.Info("Created ImGui Device Objects");

	return ret;
}

HRESULT Present(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static float conduitTapTimer = 0;
	static int conduitFrame = 0;

	nylon::imgui::BeginFrame();

	nylon::imgui::NylonMenu();

	// ImGui::ShowDemoWindow();

	nylon::imgui::EndFrame();



	return nylon::hook::Orig<PresentHookID, nylon::hook::cconv::STDCall, HRESULT>(self, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

typedef uintptr_t* VFTable;

#define GetDXVFTable(x) (**reinterpret_cast<VFTable**>(x))

HRESULT detour__KeyboardAcquire(IDirectInputDevice8* self)
{
	return self->Acquire();
}

HRESULT detour__MouseAcquire(IDirectInputDevice8* self)
{
	return self->Acquire();
}

bool nylon::internal::CreateDirectXHooks()
{
	VFTable d3dVFTable = **reinterpret_cast<uintptr_t***>(gh3::Direct3DDevice);


	nylon::hook::CreateHook<ResetHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[16],
		Reset
	);

	nylon::hook::CreateHook<PresentHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[17],
		Present
	);

	VFTable mouseVftable = GetDXVFTable(gh3::MouseDevice);
	VFTable keyboardVftable = GetDXVFTable(gh3::KeyboardDevice);

	nylon::hook::CreateHook<MouseID, nylon::hook::cconv::STDCall>(
		mouseVftable[7],
		detour__MouseAcquire
	);
	nylon::hook::CreateHook<KeyboardID, nylon::hook::cconv::STDCall>(
		keyboardVftable[7],
		detour__KeyboardAcquire
	);


	/*
	if (D3DXCreateTextureFromFile(*gh3::Direct3DDevice, "nylon\\Resources\\conduit\\conduit_tap_l.png", &conduitTapTextures[0]) != D3D_OK)
	{

	}
	if (D3DXCreateTextureFromFile(*gh3::Direct3DDevice, "nylon\\Resources\\conduit\\conduit_tap_r.png", &conduitTapTextures[1]) != D3D_OK)
	{

	}
	*/
	return true;
}
