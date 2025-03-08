#include <GH3/Script/CSymbolTableEntryType.hpp>

namespace GH3::Script
{
	const char* GetTypeName(CSymbolTableEntryType type)
	{
		switch (type)
		{
		case GH3::Script::CSymbolTableEntryType::NONE:
			return "None";
		case GH3::Script::CSymbolTableEntryType::INTEGER:
			return "Integer";
		case GH3::Script::CSymbolTableEntryType::FLOAT:
			return "Float";
		case GH3::Script::CSymbolTableEntryType::STRING:
			return "String";
		case GH3::Script::CSymbolTableEntryType::LOCALIZEDSTRING:
			return "Local String";
		case GH3::Script::CSymbolTableEntryType::PAIR:
			return "Pair";
		case GH3::Script::CSymbolTableEntryType::VECTOR:
			return "Vector";
		case GH3::Script::CSymbolTableEntryType::QSCRIPT:
			return "Script";
		case GH3::Script::CSymbolTableEntryType::CFUNCTION:
			return "C-Function";
		case GH3::Script::CSymbolTableEntryType::MEMBERFUNCTION:
			return "Member Function";
		case GH3::Script::CSymbolTableEntryType::STRUCT:
			return "Structure";
		case GH3::Script::CSymbolTableEntryType::STRUCTPOINTER:
			return "Structure Pointer";
		case GH3::Script::CSymbolTableEntryType::ARRAY:
			return "Array";
		case GH3::Script::CSymbolTableEntryType::NAME:
			return "Name";
		default:
			return "Unknown";
		}
	}
}