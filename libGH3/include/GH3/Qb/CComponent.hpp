#pragma once

#include <cstdint>

#include <GH3/Common.hpp>

#include <GH3/Keys.hpp>

#include <GH3/Qb/QbValueType.hpp>

namespace GH3
{
	enum class CComponentType : std::uint8_t
	{
		QFlagNone = 0x00,
		QFlagStructItem = 0x01,
		QTypeInt = 0x02,
		QTypeFloat = 0x04,
		QTypeCString = 0x06,
		QTypeWString = 0x08,
		QTypePair = 0x0A,
		QTypeVector = 0x0C,
		QTypeScript = 0x0E,
		QTypeCFunc = 0x10,
		QTypeUnk9 = 0x12,
		QTypeQbStruct = 0x14,
		QTypeQbArray = 0x18,
		QTypeQbKey = 0x1A,
		QTypeQbKeyRef = 0x1B,
		QTypeUnk20 = 0x28,
		QTypeUnk21 = 0x2A,
		QTypeBinaryTree1 = 0x2C,
		QTypeBinaryTree2 = 0x2E,
		QTypeStringPointer = 0x34,
		QTypeMap = 0x36,
	};

	class CComponent
	{
	public:
		CComponentType Flags;
		std::uint16_t ScriptSize;
		GH3::CRCKey Key;
		void* Value;

		CComponent* Next;

		CComponentType GetType() const
		{
			return static_cast<CComponentType>(static_cast<uint32_t>(Flags) >> 1);
		}
	};
}
