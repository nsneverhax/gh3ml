#pragma once

#include <GH3/Qb.hpp>

#include <Nylon/Hook.hpp>

namespace nylon::internal
{
	namespace binding
	{
		using CFunc_PrintStruct = nylon::hook::Binding<0x00530970, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::CScript*>;
		using CFunc_PrintF = nylon::hook::Binding<0x00530940, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::CScript*>;
		using CFunc_LoadPak = nylon::hook::Binding<0x004a1780, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::CScript*>;

		using CFunc_LoadTexture = nylon::hook::Binding<0x00541f40, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, GH3::CScript*>;
	}

	void CreateCFuncHooks();
}
