#pragma once

#include <cstdint>

#include <GH3/Common.hpp>

#include <GH3/Keys.hpp>

#include <GH3/Script/CComponentType.hpp>
#include <GH3/Script/SymbolType.hpp>
#include <GH3/Script/CPair.hpp>
#include <GH3/Script/CArray.hpp>

#include <GH3/Mth/Vector.hpp>

#include <GH3/Mem/CPoolable.hpp>

namespace GH3::Script
{
	class CStruct;

	constexpr uint32 CComponentListAddress = 0x00c4ee4c;
	constexpr uint32 CComponentListIndexAddress = 0x00c4ee58;

	class CComponent : Mem::CPoolable<CComponent, CComponentListAddress, CComponentListIndexAddress>
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
			Script::CStruct* StructValue;
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
