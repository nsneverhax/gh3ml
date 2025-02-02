#include "Imgui.hpp"

#include <GH3/DirectX.hpp>

void gh3ml::imgui::BeginFrame()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gh3ml::imgui::EndFrame()
{
	ImGui::EndFrame();

	if ((*gh3::Direct3DDevice)->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		(*gh3::Direct3DDevice)->EndScene();
	}
}