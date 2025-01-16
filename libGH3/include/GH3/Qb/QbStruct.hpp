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


		static func_InsertCStringItem InsertCStringItem = reinterpret_cast<func_InsertCStringItem>(0x00479AC0);
	}
}