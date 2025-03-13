#pragma once

#include <GH3/Common.hpp>

#include <d3d9.h>

namespace GH3::NxXenon
{
	class sSprite
	{
	public:
		void** vftable = reinterpret_cast<void**>(0x008bf654);
		undefined4 field1;
		undefined4 field2;
		undefined4 field3;
		undefined4 field4;
		uint32 BlendType;
		void* UnknownNode;
		undefined4 field7;
		undefined4 field8;
		IDirect3DBaseTexture9** Textures;
		float field10;
		float field11;
		undefined2 field12;
		undefined2 field13;
		float field14;
		float field15;
		undefined4 field16;
		undefined4 field17;
		undefined4 field18;
		undefined4 field19;
		undefined4 field20;
		undefined4 field21;
		undefined4 field22;
		undefined4 UnkDrawState;
	};

	SIZE_ASSERT(sSprite, 0x5C);
}