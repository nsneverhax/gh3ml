#include "../Main.hpp"
#include "DirectXHooks.hpp"
#include <GH3ML/Hook.hpp>
#include <GH3/DirectX.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <D3dx9tex.h>
//#pragma comment(lib, "d3d9.lib")

constexpr int PresentHookID = 2;

LPDIRECT3DTEXTURE9 tolietTexture = nullptr;

HRESULT Present(void* self, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static bool aaa = true;


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	if (nylon::internal::IsImGuiActive)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		ImGui::Begin("Nylon Menu", &nylon::internal::IsImGuiActive, window_flags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Chart"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Hash Map"))
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
		tolietTexture->GetLevelDesc(0, &surfaceDesc);
		
		ImGui::Image((ImTextureID)(intptr_t)tolietTexture, ImVec2(surfaceDesc.Width / 4.0f, surfaceDesc.Height / 4.0f));

		ImGui::End();
	}

	ImGui::EndFrame();

	if ((*gh3::Direct3DDevice)->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		(*gh3::Direct3DDevice)->EndScene();
	}

	return nylon::hook::Orig<PresentHookID, nylon::hook::cconv::STDCall, HRESULT>(self, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

bool nylon::internal::CreateDirectXHooks()
{
	uintptr_t* d3dVFTable = **reinterpret_cast<uintptr_t***>(gh3::Direct3DDevice);

	nylon::hook::CreateHook<PresentHookID, nylon::hook::cconv::STDCall>(
		d3dVFTable[17],
		Present
	);

	if (D3DXCreateTextureFromFile(*gh3::Direct3DDevice, "gh3ml\\toilet.png", &tolietTexture) != D3D_OK)
	{
		std::cout << "FAILED OT MAKE TOLIET!!" << std::endl;
	}
	else
		std::cout << "MADE TOLIET!!" << std::endl;

	return true;
}