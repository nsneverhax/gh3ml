#pragma once

#include <GH3/Common.hpp>

namespace GH3::Script
{
	class CPair
	{
	public:
		uint8_t gap0[1];
		uint8_t byte1;
		float X;
		float Y;
		/*union
		{
			CPair* Next;
			float X = 0.0f;
		};
		float Y = 0.0f;*/
	};
}