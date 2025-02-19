#include "../Main.hpp"
#include "DirectXHooks.hpp"
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
	MSG msg;
	while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	static float conduitTapTimer = 0;
	static int conduitFrame = 0;

	nylon::imgui::BeginFrame();

	nylon::imgui::NylonMenu();

	ImGui::ShowDemoWindow();

	nylon::imgui::EndFrame();



	return nylon::hook::Orig<PresentHookID, nylon::hook::cconv::STDCall, HRESULT>(self, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

bool nylon::internal::CreateDirectXHooks()
{
	uintptr_t* d3dVFTable = **reinterpret_cast<uintptr_t***>(gh3::Direct3DDevice);


	nylon::hook::CreateHook<ResetHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[16],
		Reset
	);

	nylon::hook::CreateHook<PresentHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[17],
		Present
	);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	if (!ImGui_ImplDX9_CreateDeviceObjects())
		nylon::internal::Log.Error("Unable to Create ImGui Device Objects");
	else
		nylon::internal::Log.Info("Created ImGui Device Objects");

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
