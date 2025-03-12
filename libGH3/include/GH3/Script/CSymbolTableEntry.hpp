#pragma once

#include <GH3/Common.hpp>
#include <GH3/Mem/CPoolable.hpp>
#include <GH3/Script/SymbolType.hpp>
#include <GH3//Script/CSymbolTableEntryType.hpp>

namespace GH3::Script
{
	// V: I'm p sure this inherits from CPoolable
	class CSymbolTableEntry /*  : public Mem::CPoolable<CSymbolTableEntry> */
	{
	public:
		undefined1 field0x00;
		undefined1 field0x01;
		CSymbolTableEntryType Type;
		undefined1 field0x03;

		CRCKey NameKey;
		CRCKey SourceFileKey;
		union
		{
			uint32_t UInt32Value;
			float FloatValue;
			char* CStringValue;
			CFunction CFunctionValue;
			CRCKey ChecksumValue;
		};

		CSymbolTableEntry* Next = nullptr;
	};

	SIZE_ASSERT(CSymbolTableEntry, 0x14);

	extern CSymbolTableEntry*** sp_hash_table;

	CSymbolTableEntry* LookUpSymbol(CRCKey key);
	CSymbolTableEntry* Resolve(CRCKey key);
	uint32 GetUInt32(CRCKey key);
	float GetFloat(CRCKey key);
	char* GetCString(CRCKey key);
	CRCKey GetChecksum(CRCKey key);
}