#pragma once

#include <GH3/Common.hpp>

namespace GH3::Nx
{
	class CViewport
	{
	public:
		void** vftable = reinterpret_cast<void**>(0x008b6454);
		undefined4 field1;
		undefined4 field2;
		undefined4 field3;
		undefined4 field4;
		undefined4 field5;
		undefined4 field6;
		undefined4 field7;
		float field8;
		float field9;
		undefined4 field10;
		undefined4 field11;
		float field12;
		float field13;
		undefined4 field14;
		undefined4 field15;
		undefined4 field16;
		undefined4 field17;
		undefined4 field18;
		undefined4 field19;
		undefined4 field20;
		undefined4 field21;
		undefined4 field22;
	};

	SIZE_ASSERT(CViewport, 0x5C);
}