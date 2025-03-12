#pragma once

#include <GH3/Common.hpp>
#include <GH3/Script/SymbolType.hpp>
#include <GH3/Script/CComponent.hpp>

#include <GH3/Mem/CPoolable.hpp>

namespace GH3::Script
{
	class CStruct /* : Mem::CPoolable<CStruct> */
	{
	private:
		uint16_t m_itemChainPosition = 0;
		uint8_t m_unk1 = 0;
		uint8_t m_unk2 = 0;

		bool search_for(CRCKey key, QType type, void* value);

	public:
		Script::CComponent* ComponentList;

		void AddComponent(CComponent* component, int param_2);

		bool GetChecksum(CRCKey key, CRCKey& outKey, int printContents = false);

		bool GetFloat(CRCKey key, float& out, int printContents = false);
		bool GetArray(CRCKey key, void* out, int printContents = false);

		bool GetInteger(CRCKey key, int32_t* out, int printContents = false);

		bool GetNonLocalizedString(CRCKey key, char** out, int printContents = false);
		//bool GetWString(uint32_t key, const& out, int printContents = 1);
		//bool GetPair(uint32_t key, float& out, int printContents = 1);
		//bool GetVector(uint32_t key, float& out, int printContents = 1);
		bool GetStructure(CRCKey key, float& out, int printContents = false);
		bool HasKey(CRCKey key);
	};

	//namespace Functions
	//{
	//	typedef bool(__thiscall* func__QbStruct_GetTypedValue)(QbStruct* self, uint32_t key, QbValueType valueType, void* value);

	//	typedef void(__thiscall* func_InsertCStringItem)(QbStruct* self, uint32_t key, char* string);
	//	typedef void(__thiscall* func_InsertQbKeyItem)(QbStruct* self, uint32_t key, uint32_t item);

	//	static func__QbStruct_GetTypedValue GetTypedValue = reinterpret_cast<func__QbStruct_GetTypedValue>(0x004786a0);

	//	static func_InsertCStringItem InsertCStringItem = reinterpret_cast<func_InsertCStringItem>(0x00479AC0);
	//	static func_InsertQbKeyItem InsertQbKeyItem = reinterpret_cast<func_InsertQbKeyItem>(0x00479c80);
	//}

}

