#pragma once

#include <GH3/Qb/CComponent.hpp>


namespace GH3
{
	struct QbStruct
	{
	private:
		uint16_t m_itemChainPosition = 0;
		uint8_t m_unk1 = 0;
		uint8_t m_unk2 = 0;

	public:
		Script::CComponent* ComponentList;

		bool GetKey(CRCKey key, CRCKey& outKey, int param_3 = 1);
		bool GetFloat(CRCKey key, float& out, int param_3 = 1);
		bool GetQbArrayItem(CRCKey key, void* out, int param_3 = 1);

		bool GetInt(CRCKey key, int32_t& value, int param_3 = 1);
		bool GetUInt(CRCKey key, uint32_t& value, int param_3 = 1);

		bool GetString(CRCKey key, char** out, int param_3 = 1);
		//bool GetWString(uint32_t key, const& out, int param_3 = 1);
		//bool GetPair(uint32_t key, float& out, int param_3 = 1);
		//bool GetVector(uint32_t key, float& out, int param_3 = 1);
		bool GetStruct(CRCKey key, float& out, int param_3 = 1);
		bool HasKey(CRCKey key);
	};

	namespace Functions
	{
		typedef bool(__thiscall* func__QbStruct_GetTypedValue)(QbStruct* self, uint32_t key, QbValueType valueType, void* value);

		typedef void(__thiscall* func_InsertCStringItem)(QbStruct* self, uint32_t key, char* string);
		typedef void(__thiscall* func_InsertQbKeyItem)(QbStruct* self, uint32_t key, uint32_t item);

		static func__QbStruct_GetTypedValue GetTypedValue = reinterpret_cast<func__QbStruct_GetTypedValue>(0x004786a0);

		static func_InsertCStringItem InsertCStringItem = reinterpret_cast<func_InsertCStringItem>(0x00479AC0);
		static func_InsertQbKeyItem InsertQbKeyItem = reinterpret_cast<func_InsertQbKeyItem>(0x00479c80);
	}

}