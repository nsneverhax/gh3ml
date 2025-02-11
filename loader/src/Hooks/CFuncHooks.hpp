#pragma once

#include <GH3/Qb.hpp>

#include <Nylon/Hook.hpp>

namespace nylon::internal
{
	namespace binding
	{
		using CFunc_PrintStruct = nylon::hook::Binding<0x00530970, nylon::hook::cconv::CDecl, bool, gh3::QbStruct*, gh3::QbScript*>;
		using CFunc_PrintF = nylon::hook::Binding<0x00530940, nylon::hook::cconv::CDecl, bool, gh3::QbStruct*, gh3::QbScript*>;
	}

	void CreateCFuncHooks();
}
