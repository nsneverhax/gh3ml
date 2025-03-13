#pragma once

#include <GH3/Common.hpp>

#include <GH3/Obj/CSmartPointer.hpp>
#include <GH3/Gfx/Camera.hpp>

namespace GH3::Nx
{
	//
	//
	// vftable[2] -> CreateRenderTarget
	//
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
		Obj::CSmtPtr<Gfx::Camera> Camera;
		undefined4 field20;
		undefined4 field21;
		undefined4 field22;

		void CreateRenderTarget();
	};

	SIZE_ASSERT(CViewport, 0x5C);
}