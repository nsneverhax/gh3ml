#pragma once

#include <cstdint>
#include <GH3/Qb/QbValueType.hpp>

struct __declspec(align(4)) HashMapNode
{
	uint8_t Byte0 = 0;
	uint8_t Byte1 = 0;
	QbValueType ItemType;
	uint8_t Byte3;
	uint32_t Key;
	uint32_t Dword8;
	uint32_t Value;
	HashMapNode* Next;
};