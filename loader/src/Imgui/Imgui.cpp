#include "Imgui.hpp"
#include "ImGuiConsole.hpp"

#include <GH3/DirectX.hpp>
#include <GH3/Addresses.hpp>
#include <XInput.h>

nylon::internal::ImGuiConsole _console = { };

void nylon::imgui::BeginFrame()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void nylon::imgui::EndFrame()
{
	ImGui::EndFrame();

	if ((*gh3::Direct3DDevice)->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		(*gh3::Direct3DDevice)->EndScene();
	}
}
float* whammyMultipliers = new float[9];

bool _nylonMenuActive = true;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <iostream>

LRESULT nylon::imgui::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool waitForTabRelease = false;

	LRESULT windProcResult = 0;

	if (windProcResult = ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return windProcResult;

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_OEM_3:

			if (!waitForTabRelease)
				SetNylonMenuActive(!GetNylonMenuActive());

			waitForTabRelease = true;
			return 0;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (LOWORD(wParam))
		{
		case VK_OEM_3:
			waitForTabRelease = false;
			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}

void nylon::imgui::SetNylonMenuActive(bool state)
{
	if (!_nylonMenuActive != state)
		return;

	// V: State change

	if (_nylonMenuActive)
	{
		XInputEnable(false);
		(*gh3::KeyboardDevice)->Unacquire();
		(*gh3::MouseDevice)->Unacquire();
	}
	else
	{
		XInputEnable(true);
		(*gh3::KeyboardDevice)->Acquire();
		(*gh3::MouseDevice)->Acquire();
	}
	_nylonMenuActive = state;
}

bool nylon::imgui::GetNylonMenuActive()
{
	return _nylonMenuActive;
}

void nylon::imgui::NylonMenu()
{
	static bool whammyMAde = false;

	if (!whammyMAde)
	{
		for (auto i = 0; i < 9; i++)
			whammyMultipliers[i] = 1.0f;
		whammyMAde = true;
	}

	if (!GetNylonMenuActive())
		return;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	std::string title = "Nylon Menu " + std::string(nylon::VersionString);
	
	bool active = GetNylonMenuActive();

	if (ImGui::Begin(title.c_str(), &active, window_flags))
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
		//conduitTapTextures[conduitFrame]->GetLevelDesc(0, &surfaceDesc);
	
	
		//ImGui::Image((ImTextureID)(intptr_t)conduitTapTextures[conduitFrame], ImVec2(surfaceDesc.Width, surfaceDesc.Height));
	
		ImGui::InputDouble("FrameTime?", GH3::Time::DOUBLE_00b544b8);

		for (auto i = 0; i < 9; i++)
		{
			std::string str = "Param";
			str.append(std::to_string(i));

			ImGui::SliderFloat(str.data(), &whammyMultipliers[i], 0.0, 10.0f);
		}
		ImGui::End();
	}

	_console.Draw();

	if (!active && GetNylonMenuActive ())
		SetNylonMenuActive(false);
}