#pragma once

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <GH3ML/Core.hpp>

namespace gh3ml::imgui
{
	void BeginFrame();
	void EndFrame();
}