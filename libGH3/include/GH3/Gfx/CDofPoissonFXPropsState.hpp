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

		void AllocateCopy();
		void Draw();
		void plat_draw();
		void Resolve();
		bool SetParams(CStruct* cstruct);
		void GetParams(CStruct* cstruct);

	};

	SIZE_ASSERT(CDofPoissonFXPropsState, 0x2c);

}