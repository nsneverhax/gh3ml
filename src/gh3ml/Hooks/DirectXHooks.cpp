#include "DirectXHooks.hpp"
#include <GH3ML/Hook.hpp>
#include <GH3/DirectX.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

constexpr int PresentHookID = 2;

namespace in = gh3ml::internal;

HRESULT Present(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static bool show_demo_window = true;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return gh3ml::hook::Orig<PresentHookID, gh3ml::hook::cconv::STDCall, HRESULT>(self, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

bool in::CreateDirectXHooks()
{
	uintptr_t* d3dVFTable = **reinterpret_cast<uintptr_t***>(gh3::Direct3DDevice);

	gh3ml::hook::CreateHook<PresentHookID, gh3ml::hook::cconv::STDCall>(
		d3dVFTable[17],
		Present
	);

	return true;
}