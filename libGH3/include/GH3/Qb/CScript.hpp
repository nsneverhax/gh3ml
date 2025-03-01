#pragma once

#include <GH3/Common.hpp>
#include <GH3/Mem/CPoolable.hpp>

namespace GH3
{
	class QbStruct;

	class CScript
	{
		uint32_t NotSessionSpecific;
		CScript* Next = nullptr;
		CScript* Previous = nullptr;
		QbStruct* StructScript;
		uint8_t* ProgramCounter;
		QbStruct* FunctionParams;
		QbStruct* InputParams;

	};
}