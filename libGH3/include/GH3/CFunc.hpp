#pragma once

#include "Qb.hpp"

#include <GH3/Script/CStruct.hpp>
#include <GH3/Script/CScript.hpp>

namespace GH3
{
	struct CFuncDescriptor
	{
		char* Name = nullptr;
		void* Function = nullptr;
	};

	static_assert(sizeof(CFuncDescriptor) == 8, "CFuncDescriptor must be 8 bytes");

	extern uint32_t CFuncArrayCount;
	extern CFuncDescriptor* CFuncArray;




	bool SetNewWhammyValue(Script::CStruct* qbStruct);
}

