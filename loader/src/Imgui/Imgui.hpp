#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <Nylon/Core.hpp>

namespace nylon::imgui
{
	void BeginFrame();
	void EndFrame();

	extern bool NylonMenuActive;
	void NylonMenu();

}
