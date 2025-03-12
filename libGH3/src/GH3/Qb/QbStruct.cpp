#include <GH3/Script/CStruct.hpp>

namespace GH3::Script
{
	bool CStruct::search_for(CRCKey key, QType valueType, void* value)
	{
		return reinterpret_cast<bool(__thiscall*)(CStruct*, CRCKey, QType, void*)>(0x004786a0)(this, key, valueType, value);
	}

	void CStruct::AddComponent(CComponent* component, int param_2)
	{
		reinterpret_cast<void(__thiscall*)(CStruct*, CComponent*, int)>(0x0027bdb0)(this, component, param_2);
	}

	bool CStruct::GetInteger(CRCKey key, int32_t* out, int printContents)
	{
		if (search_for(key, QTypeInt, &key))
		{
			*out = key;
			return true;
		}

		//if (printContents)
		//		Script::PrintContents(this, 0, 1)	
		return false;
	}


	bool CStruct::GetNonLocalizedString(CRCKey key, char** out, int printContents)
	{
		CRCKey ogKey = key;

		if (search_for(key, QTypeCString, &key))
		{
			*out = reinterpret_cast<char*>(key);
		}

		//if (printContents)
		//		Script::PrintContents(this, 0, 1)	
		return false;
	}
	void CStruct::AddNonLocalizedString(CRCKey key, char** out, int printContents)
	{


	}
}
//bool GH3::CStruct::GetKey(CRCKey key, CRCKey& outKey, int param_3)
//{
//	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t, uint32_t*, int)>(0x00478e50)(this, key, &outKey, param_3);
//}
//
//bool GH3::QbStruct::GetFloat(CRCKey key, float& out, int param_3)
//{
//	return Functions::GetTypedValue(this, key, QbValueType::QTypeFloat, &out);
//}
//
//bool GH3::QbStruct::GetQbArrayItem(CRCKey key, void* out, int param_3)
//{
//	return Functions::GetTypedValue(this, key, QbValueType::QTypeInt, out);
//}
//
//bool GH3::QbStruct::GetString(CRCKey key, char** out, int param_3)
//{
//	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t, char**, uint32_t)>(0x004788b0)(this, key, out, param_3);
//}
//
//bool GH3::QbStruct::HasKey(CRCKey key)
//{
//	return reinterpret_cast<bool(__thiscall*)(QbStruct*, uint32_t)>(0x00478180)(this, key);
//}