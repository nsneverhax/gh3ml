#pragma once

#include <GH3/Common.hpp>
#include <GH3/Mem/CPoolable.hpp>
#include <GH3/Script/CComponentType.hpp>

namespace GH3::Script
{
	class CArray : Mem::CPoolable<CArray>
	{
	public:
		CComponentType Type;
		uint32_t Size;

		union
		{
			void* ArrayData;

			int32* Integers;
			float* Floats;
			CRCKey* Keys;

			int32 Integer;
			float Float;
			CRCKey Key;
		};

		float SetFloat(int index);
	};
}