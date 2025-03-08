#pragma once

#include <GH3/Common.hpp>
#include <GH3/Mem/CPoolable.hpp>

namespace GH3::Script
{
	using CStruct = GH3::QbStruct;

	class CScript
	{
		uint32_t NotSessionSpecific;
		CScript* Next = nullptr;
		CScript* Previous = nullptr;
		CStruct* StructScript;
		uint8_t* ProgramCounter;
		CStruct* FunctionParams;
		CStruct* InputParams;

	};
}