#pragma once

#include <cstdint>

namespace GH3
{
	enum class QbValueType : uint8_t
	{
		QTypeNull = 0,
		QTypeInt = 1,
		QTypeFloat = 2,
		QTypeCString = 3,
		QTypeWString = 4,
		QTypePair = 5,
		QTypeVector = 6,
		QTypeScript = 7,
		QTypeCFunc = 8,
		QTypeUnk0x9 = 9,
		QTypeQbStruct = 10,
		QTypeUnk0xB = 11,
		QTypeQbArray = 12,
		QTypeKey = 13,
		QTypeUnk0xE = 14,
		QTypeUnk0xF = 15,
		QTypeUnk0x10 = 16,
		QTypeUnk0x11 = 17,
		QTypeUnk0x14 = 20,
		QTypeUnk0x15 = 21,
		QTypeBinaryTree1 = 22,
		QTypeBinaryTree2 = 23,
		QTypeUnk0x18 = 24,
		QTypeUnk0x19 = 25,
		QTypeStringPointer = 26,
		QTypeQbMap = 27,
		QTypeQbStringsQs = 28,
	};
}