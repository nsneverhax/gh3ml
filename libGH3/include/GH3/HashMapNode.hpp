#pragma once

#include <cstdint>
#include <GH3/Qb/QbValueType.hpp>

namespace GH3
{
	struct HashMapNode
	{

		uint8_t Byte0 = 0;
		QbValueType ItemType;
		uint8_t Byte1 = 0;
		uint8_t Byte2 = 0;
		uint8_t Byte3 = 0;
		uint32_t Key;
		uint32_t Dword8;
		uint32_t Value;
		HashMapNode* Next;

	};
}