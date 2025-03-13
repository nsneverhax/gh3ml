#include <GH3/Script/ScriptCommon.hpp>
#include <GH3/Script/CStruct.hpp>

namespace GH3
{
	Script::CStruct* Script::GetStructure(CRCKey key)
	{
		NEEDS_IMPLEMENTATION();
		NEEDS_TESTING();

		return reinterpret_cast<CStruct * (__cdecl*)(CRCKey)>(0x004a5d70)(key);
	}

	Script::CArray* Script::GetArray(CRCKey key)
	{
		NEEDS_IMPLEMENTATION();
		NEEDS_TESTING();

		return reinterpret_cast<CArray * (__cdecl*)(CRCKey)>(0x004a5e00)(key);
	}
}