#pragma once

#include <GH3/Qb/QbStructItem.hpp>


namespace GH3
{

	struct QbStruct
	{
	public:

	};

	namespace Functions
	{
		typedef void(__cdecl *func_InsertCStringItem)(QbStruct* _this, Key key, char* string);
		typedef void(__cdecl* func_InsertQbKeyItem)(QbStruct* _this, Key key, Key item);

		static func_InsertCStringItem InsertCStringItem = reinterpret_cast<func_InsertCStringItem>(0x00479AC0);
		static func_InsertQbKeyItem InsertQbKeyItem = reinterpret_cast<func_InsertQbKeyItem>(0x00479c80);
	}
}