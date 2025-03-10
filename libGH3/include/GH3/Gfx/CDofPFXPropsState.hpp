#pragma once

#include <GH3/Common.hpp>

#include <GH3/Gfx/CScreenFXPropsState.hpp>

namespace GH3::Gfx
{
	class QbStruct;
	typedef QbStruct CStruct;

	class CDofFXPropsState : public CScreenFXPropsState
	{
		bool IsOn;
		float BackDist;
		float FocalDist;
		float FrontDist;
		float ClampBack;

		uint32 BackColor[4];
		uint32 FrontColor[4];

		uint32 BlurResolution;
		float BlurRadius;

		uint32 UDivs;
		uint32 VDivs;
		uint32 Order;

		void AllocateCopy();
		void Draw();
		void plat_draw();
		void Resolve();
		bool SetParams(CStruct* cstruct);
		void GetParams(CStruct* cstruct);

	};

	SIZE_ASSERT(CDofFXPropsState, 0x60);

}