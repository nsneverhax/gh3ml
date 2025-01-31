#pragma once

#include <cstdint>

#include <GH3/Qb/QbNodeFlags.hpp>
#include <GH3/Qb/QbValueType.hpp>

namespace GH3
{

	/// <summary>
	/// This type has NOT been verified to work in a direct cast to GH3 use with caution!
	/// </summary>
	struct QbStructItem
	{
	public:
		std::uint8_t Unknown0x1_1;
		QbNodeFlags Flags;
		std::uint16_t Unknown0x2_2;
		std::uint32_t Key;
		std::int32_t Value;

		QbStructItem* Next;


	};
}
