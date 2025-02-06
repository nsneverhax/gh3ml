#include "Imgui.hpp"

#include <GH3/DirectX.hpp>


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

bool nylon::imgui::NylonMenuActive = true;

void nylon::imgui::NylonMenu()
{
	if (!NylonMenuActive)
		return;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
	std::string title = "Nylon Menu " + std::string(nylon::VersionString);
	
	if (ImGui::Begin(title.c_str(), &NylonMenuActive, window_flags))
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
	
		ImGui::End();
	}
}