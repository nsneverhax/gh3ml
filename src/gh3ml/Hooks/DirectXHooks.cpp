#include "../Main.hpp"
#include "DirectXHooks.hpp"
#include <GH3ML/Hook.hpp>
#include <GH3/DirectX.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <GH3/Addresses.hpp>
#include <GH3ML/Config.hpp>

#include <D3dx9tex.h>

#include "../Imgui/Imgui.hpp"


constexpr int PresentHookID = 2;

LPDIRECT3DTEXTURE9 conduitTapTextures[] = { nullptr, nullptr };

HRESULT Present(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static float conduitTapTimer = 0;
	static int conduitFrame = 0;

	static bool aaa = true;

	gh3ml::imgui::BeginFrame();

	if (nylon::internal::IsImGuiActive)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		std::string title = "Nylon Menu " + std::string(nylon::VersionString);

		if (ImGui::Begin(title.c_str(), &nylon::internal::IsImGuiActive, window_flags))
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Windows"))
				{
					if (ImGui::MenuItem("Hash Map Browser"))
					{

					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Chart"))
				{
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Debug"))
				{

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}
			D3DSURFACE_DESC surfaceDesc;
			conduitTapTextures[conduitFrame]->GetLevelDesc(0, &surfaceDesc);


			ImGui::Image((ImTextureID)(intptr_t)conduitTapTextures[conduitFrame], ImVec2(surfaceDesc.Width, surfaceDesc.Height));

			ImGui::End();
		}
	}

	conduitTapTimer += *DeltaTime;

	if (conduitTapTimer >= 0.125)
	{
		conduitFrame = (conduitFrame + 1) % 2;
		conduitTapTimer -= 0.125;
	}
	gh3ml::imgui::EndFrame();



	return nylon::hook::Orig<PresentHookID, nylon::hook::cconv::STDCall, HRESULT>(self, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

bool nylon::internal::CreateDirectXHooks()
{
	uintptr_t* d3dVFTable = **reinterpret_cast<uintptr_t***>(gh3::Direct3DDevice);

	nylon::hook::CreateHook<PresentHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[17],
		Present
	);

	if (D3DXCreateTextureFromFile(*gh3::Direct3DDevice, "gh3ml\\Resources\\conduit_tap_l.png", &conduitTapTextures[0]) != D3D_OK)
	{

	}
	if (D3DXCreateTextureFromFile(*gh3::Direct3DDevice, "gh3ml\\Resources\\conduit_tap_r.png", &conduitTapTextures[1]) != D3D_OK)
	{

	}

	return true;
}