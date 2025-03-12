#pragma once

#include <GH3/Common.hpp>

#include <GH3/Gfx/CScreenFXPropsState.hpp>

namespace GH3::Gfx
{
	class CDofFXPropsState : public CScreenFXPropsState
	{
	private:
		void plat_draw();

	public:

		CDofFXPropsState();
		CDofFXPropsState(const CDofFXPropsState& source);

		bool IsOn;
		float BackDist;
		float FrontDist;
		float Strength;
		float CrossFade;

		uint32 BackColor[4];
		uint32 FrontColor[4];

		uint32 BlurResolution;
		float BlurRadius;

		uint32 UDivs;
		uint32 VDivs;
		uint32 Order;

		void AllocateCopy();
		void Draw();
		void Resolve();
		bool SetParams(CStruct* cstruct);
		void GetParams(CStruct* cstruct);

	};

	SIZE_ASSERT(CDofFXPropsState, 0x60);

	CDofFXPropsState::CDofFXPropsState()
	{
		BackColor[0] = 0;
		BackColor[1] = 0;
		BackColor[2] = 0;
		BackColor[3] = 0;

		FrontColor[0] = 0;
		FrontColor[1] = 0;
		FrontColor[2] = 0;
		FrontColor[3] = 0;

		BackDist = 0;
		FrontDist = 0;
		Strength = 0;
		CrossFade = 0;
		BlurResolution = 1;
		UDivs = 1;
		VDivs = 1;
		IsOn = false;
		BlurRadius = 6;
	}
	CDofFXPropsState::CDofFXPropsState(const CDofFXPropsState& source)
	{
		BackColor[0] = source.BackColor[0];
		BackColor[1] = source.BackColor[1];
		BackColor[2] = source.BackColor[2];
		BackColor[3] = source.BackColor[3];

		FrontColor[0] = source.BackColor[0];
		FrontColor[1] = source.BackColor[1];
		FrontColor[2] = source.BackColor[2];
		FrontColor[3] = source.BackColor[3];

		BackDist = source.BackDist;
		FrontDist = source.FrontDist;
		Strength = source.Strength;
		CrossFade = source.CrossFade;
		BlurResolution = source.BlurResolution;
		UDivs = source.UDivs;
		VDivs = source.VDivs;
		IsOn = source.IsOn;
		BlurRadius = source.BlurRadius;
	}

}