#pragma once

#include <GH3/Common.hpp>

namespace GH3::Gfx
{
	class CScreenFXPropsState
	{
		void** vftable;
		undefined4 Time;
		undefined4 field1;
		undefined4 field2;
		undefined4 field3;
		undefined4 field4;
	};

	SIZE_ASSERT(CScreenFXPropsState, 0x18);
}