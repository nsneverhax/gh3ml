#pragma once

#include <GH3/Qb.hpp>

#include <Nylon/Hook.hpp>

namespace nylon::internal
{
	namespace binding
	{
		using CFunc_PrintStruct = nylon::hook::Binding<0x00530970, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::QbScript*>;
		using CFunc_PrintF = nylon::hook::Binding<0x00530940, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::QbScript*>;
		using CFunc_LoadPak = nylon::hook::Binding<0x004a1780, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::QbScript*>;
	}

	void CreateCFuncHooks();
}
