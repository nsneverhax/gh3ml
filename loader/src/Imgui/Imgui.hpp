#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <Nylon/Core.hpp>

extern float* whammyMultipliers;

namespace nylon::imgui
{
	void BeginFrame();
	void EndFrame();

	LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SetNylonMenuActive(bool state);
	bool GetNylonMenuActive();

	void NylonMenu();

}
