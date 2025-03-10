#pragma once

#include <GH3/Common.hpp>

#include <GH3/Gfx/CScreenFXPropsState.hpp>

namespace GH3::Gfx
{
	class CDofPoissonFXPropsState : public CScreenFXPropsState
	{
		bool IsOn;
		float BackDist;
		float FocalDist;
		float FrontDist;
		float ClampBack;
	};

	SIZE_ASSERT(CDofPoissonFXPropsState, 0x2c);
}