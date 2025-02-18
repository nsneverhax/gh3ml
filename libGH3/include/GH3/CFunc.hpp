#pragma once

#include "Qb.hpp"

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

	bool SetNewWhammyValue(QbStruct* qbStruct);
}

