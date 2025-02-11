#include <GH3/Qb/QbStruct.hpp>


bool gh3::QbStruct::GetKey(uint32_t key, uint32_t& outKey, int param_3)
{
	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t, uint32_t*, int)>(0x00478e50)(this, key, &outKey, param_3);
}

bool gh3::QbStruct::GetFloat(uint32_t key, float& out, int param_3)
{
	return Functions::GetTypedValue(this, key, QbValueType::QTypeFloat, &out);
}

bool gh3::QbStruct::GetQbArrayItem(uint32_t key, void* out, int param_3)
{
	return Functions::GetTypedValue(this, key, QbValueType::QTypeInt, out);
}
bool gh3::QbStruct::HasKey(uint32_t key)
{
	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t)>(0x00478180)(this, key);
}