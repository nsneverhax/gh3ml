#pragma once

#include <GH3/Common.hpp>

#include <GH3/Obj/CObject.hpp>

#include <GH3/Mth/Vector.hpp>

#include <GH3/Image/RGBA.hpp>

#include <GH3/Obj/CSmartPointer.hpp>

namespace GH3::Front
{
	class CScreenElement;

	struct ConcatProps
	{
		Mth::Vector3f WorldPosition;
		Mth::Vector2f ScreenPosition;
		uint32_t ZPosition;

		Mth::Vector2f UpperLeft;

		Mth::Vector2f RenderScale;

		Mth::Vector2f AbsoluteScale;

		float RotationAngle;

		Image::RGBA Color;
	};

	class CScreenElement : public Obj::CObject
	{
	public:
		Obj::CSmartPointer<CScreenElement> Parent;
		Obj::CSmartPointer<CScreenElement> ChildList;

		Obj::CSmartPointer<CScreenElement> Next;
		Obj::CSmartPointer<CScreenElement> Previous;

		ConcatProps LocalProperties;
		ConcatProps TargetProperties;

		uint32 AnimLastTime;
		uint32 AnimNextTime;

		undefined4 field8;
		undefined4 field9;

		ConcatProps SummedProperties;

		Mth::Vector2f Just;
		Mth::Vector2f BaseSize;

		float ZPriority;
	};
}