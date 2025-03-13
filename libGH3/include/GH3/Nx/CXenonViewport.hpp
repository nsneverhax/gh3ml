#pragma once

#include <GH3/Common.hpp>
#include <GH3/Gfx/CScreenFXManager.hpp>
#include <GH3/Nx/CViewport.hpp>
#include <GH3/NxXenon/sSprite.hpp>

namespace GH3::Nx
{
	class CXenonViewport : public CViewport
	{
	public:
		undefined4 field23;
		undefined4 field24;
		undefined4 field25;
		NxXenon::sSprite Sprite;
		undefined4 field27;
		undefined4 field28;
		undefined4 field29;
		undefined4 field30;
		undefined4 field31;
		undefined4 field32;
		undefined4 field33;
		Gfx::CScreenFXManager ScreenFXManager;
		undefined4 field35;
	};

	SIZE_ASSERT(CXenonViewport, 0xE8);
}