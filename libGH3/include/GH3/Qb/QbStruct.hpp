#pragma once

#include <GH3/Qb/QbStructItem.hpp>



struct QbStruct
{
private:
	uint16_t m_itemChainPosition = 0;
	uint8_t m_unk1 = 0;
	uint8_t m_unk2;

public:
	bool GetKey(uint32_t key, uint32_t& outKey, int param_3 = 1);
	bool GetFloat(uint32_t key, float& out, int param_3 = 1);
	bool GetQbArrayItem(uint32_t key, void* out, int param_3 = 1);

	bool GetInt(uint32_t key, int32_t& value, int param_3 = 1);
	bool GetUInt(uint32_t key, uint32_t& value, int param_3 = 1);

	bool GetString(uint32_t key, float& out, int param_3 = 1);
	bool GetWString(uint32_t key, float& out, int param_3 = 1);
	bool GetPair(uint32_t key, float& out, int param_3 = 1);
	bool GetVector(uint32_t key, float& out, int param_3 = 1);
	bool GetStruct(uint32_t key, float& out, int param_3 = 1);
};

namespace Functions
{
	typedef bool(__thiscall* func__QbStruct_GetTypedValue)(QbStruct* _this, uint32_t key, QbValueType valueType, void* value);

	typedef void(__cdecl *func_InsertCStringItem)(QbStruct* _this, uint32_t key, char* string);
	typedef void(__cdecl* func_InsertQbKeyItem)(QbStruct* _this, uint32_t key, uint32_t item);

	static func__QbStruct_GetTypedValue GetTypedValue = reinterpret_cast<func__QbStruct_GetTypedValue>(0x004786a0);

	static func_InsertCStringItem InsertCStringItem = reinterpret_cast<func_InsertCStringItem>(0x00479AC0);
	static func_InsertQbKeyItem InsertQbKeyItem = reinterpret_cast<func_InsertQbKeyItem>(0x00479c80);
}
