#pragma once

#include <Nylon/Hook.hpp>

#include <GH3/Script/CStruct.hpp>

namespace nylon::binding
{
	using Gfx_CScreenFXManager_AddScreenFXInstance = nylon::hook::Binding<0x005f7490, nylon::hook::cconv::ThisCall, void, void*, GH3::Script::CStruct*, GH3::undefined4>;
}