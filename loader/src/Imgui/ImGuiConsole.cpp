#include "ImGuiConsole.hpp"
#include "ImGui.hpp"

namespace in = nylon::internal;

int ACallback(ImGuiInputTextCallbackData* data)
{
	return 0;
}

void in::ImGuiConsole::DrawLogWindow()
{
	float footerHeightReserved = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	if (ImGui::BeginChild("ScrollRegion", ImVec2(0, footerHeightReserved), false, 0))
	{
		ImGui::PushTextWrapPos();



		ImGui::PopTextWrapPos();
		ImGui::EndChild();
	}
}

void in::ImGuiConsole::Draw()
{

	if (!ImGui::Begin("Nylon Console"))
	{
		ImGui::End();
		return;
	}

	DrawLogWindow();

	ImGui::Separator();
	ImGuiInputTextFlags inputTextFlags =
		ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackCompletion |
		ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackAlways;


	if (ImGui::InputText("ConsoleInput", _buffer, 256))
	{

	}


	ImGui::End();
}