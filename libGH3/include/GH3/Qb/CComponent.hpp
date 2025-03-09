#pragma once

#include <cstdint>

#include <GH3/Common.hpp>

#include <GH3/Keys.hpp>

#include <GH3/Script/CComponentType.hpp>

#include <GH3/Qb/QbValueType.hpp>

#include <GH3/Script/CPair.hpp>
#include <GH3/Script/CArray.hpp>
#include <GH3/Mth/Vector.hpp>

namespace GH3
{
	class QbStruct;
}
namespace GH3::Script
{
	class CComponent
	{
	public:
		uint8_t unkFlag0;
		CComponentType Flags;
		std::uint16_t ScriptSize;
		CRCKey Key;

		union
		{
			uint32_t IntegerValue;
			float FloatValue;
			char* CStringValue;
			wchar_t* WStringValue;
			Script::CPair* PairValue;
			Mth::Vector4f* VectorValue;
			// QTypeScript
			// QTypeCFunc
			// QTypeUnk9
			QbStruct* StructValue;
			Script::CArray* ArrayValue;
			CRCKey KeyValue;
			// QTypeQbKeyRef
			// QTypeUnk20
			// QTypeUnk21
			// QTypeBinaryTree1
			// QTypeBinaryTree2
			// QTypeStringPointer
			// QTypeMap
		};

		CComponent* Next;

		CComponentType GetType() const
		{
			return static_cast<CComponentType>(static_cast<uint32_t>(Flags) & 0b11111110);
		}
	};
}
