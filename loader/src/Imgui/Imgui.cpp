#include "Imgui.hpp"
#include <Nylon/CommandConsole.hpp>
#include <Nylon/VersionInfo.hpp>

#include <GH3/DirectX.hpp>
#include <GH3/Addresses.hpp>
#include <XInput.h>

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

bool _nylonMenuActive = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <iostream>

LRESULT nylon::imgui::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool waitForTabRelease = false;

	if (!_nylonMenuActive)
		XInputEnable(true);

	LRESULT windProcResult = ERROR_SUCCESS;

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
			return ERROR_SUCCESS;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (LOWORD(wParam))
		{
		case VK_OEM_3:
			waitForTabRelease = false;
			return ERROR_SUCCESS;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return ERROR_SUCCESS;
}

void nylon::imgui::SetNylonMenuActive(bool state)
{
	if (_nylonMenuActive == state)
		return;

	_nylonMenuActive = state;

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
}

bool nylon::imgui::GetNylonMenuActive()
{
	return _nylonMenuActive;
}

bool showTextureViewer = false;

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
	std::string title = "Nylon Menu " + to_string(nylon::Version());
	
	bool active = GetNylonMenuActive();
	//ImGui::SetWindowFontScale(2);

	if (ImGui::Begin(title.c_str(), &active, window_flags))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Hash Map Browser"))
				{

				}
				if (ImGui::MenuItem("Texture Viewer"))
				{
					showTextureViewer = true;
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

		//D3DSURFACE_DESC surfaceDesc;
		//conduitTapTextures[conduitFrame]->GetLevelDesc(0, &surfaceDesc);
	
	
		//ImGui::Image((ImTextureID)(intptr_t)conduitTapTextures[conduitFrame], ImVec2(surfaceDesc.Width, surfaceDesc.Height));

		// ImGui::Text(nylon::CompileDate);
		ImGui::Text(nylon::CompileDateTime.data());

		ImGui::InputDouble("FrameTime?", GH3::Time::DOUBLE_00b544b8);

		for (auto i = 0; i < 9; i++)
		{
			std::string str = "Whammy Param";
			str.append(std::to_string(i));

			ImGui::SliderFloat(str.data(), &whammyMultipliers[i], 0.0, 1.0f);
		}
	}
	ImGui::End();

	Console.Draw();

	nylon::imgui::TextureViewer();

	if (!active && GetNylonMenuActive())
		SetNylonMenuActive(false);
}

void nylon::imgui::TextureViewer()
{
	LPDIRECT3DTEXTURE9* textures = reinterpret_cast<LPDIRECT3DTEXTURE9*>(0x00c5e788);

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	if (ImGui::Begin("Texture Viewer", &showTextureViewer, window_flags))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Hash Map Browser"))
				{

				}
				if (ImGui::MenuItem("Texture Viewer"))
				{
					showTextureViewer = true;
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

		ImGui::Text("ID: 0");
		if (textures != nullptr && textures[0] != nullptr)
		{
			D3DSURFACE_DESC surfaceDesc;
			textures[0]->GetLevelDesc(0, &surfaceDesc);
			ImGui::Image((ImTextureID)(intptr_t)textures[0], ImVec2(surfaceDesc.Width, surfaceDesc.Height));
		}
	}
	ImGui::End();
}