#pragma once

#include <GH3/Common.hpp>

#include <GH3/Script/CComponentType.hpp>

namespace GH3::Script
{
	class CArray
	{
	public:
		void* data;
		CComponentType Type;
		uint32_t size;

		/*
		uint8_t UnknownMember1;
		uint8_t UnknownMember2;
		CComponentType Type;
		uint8_t UnknownMember3;
		uint32_t Size;
		void* data;*/
	};

	//SIZE_ASSERT(CArray, 0xC);
}