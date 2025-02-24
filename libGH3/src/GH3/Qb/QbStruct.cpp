#include <GH3/Qb/QbStruct.hpp>


bool GH3::QbStruct::GetKey(CRCKey key, CRCKey& outKey, int param_3)
{
	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t, uint32_t*, int)>(0x00478e50)(this, key, &outKey, param_3);
}

bool GH3::QbStruct::GetFloat(CRCKey key, float& out, int param_3)
{
	return Functions::GetTypedValue(this, key, QbValueType::QTypeFloat, &out);
}

bool GH3::QbStruct::GetQbArrayItem(CRCKey key, void* out, int param_3)
{
	return Functions::GetTypedValue(this, key, QbValueType::QTypeInt, out);
}

bool GH3::QbStruct::GetString(CRCKey key, char** out, int param_3)
{
	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t, char**, uint32_t)>(0x004788b0)(this, key, out, param_3);
}

bool GH3::QbStruct::HasKey(CRCKey key)
{
	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t)>(0x00478180)(this, key);
}