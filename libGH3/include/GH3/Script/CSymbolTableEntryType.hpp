#pragma once

#include <GH3/Common.hpp>

namespace GH3::Script
{
	enum class CSymbolTableEntryType : uint8
	{
		NONE,
		INTEGER,
		FLOAT,
		STRING,
		LOCALIZEDSTRING,
		PAIR,
		VECTOR,
		QSCRIPT,
		CFUNCTION,
		MEMBERFUNCTION,
		STRUCT,
		STRUCTPOINTER,
		ARRAY,
		NAME
	};

	const char* GetTypeName(CSymbolTableEntryType type);
}