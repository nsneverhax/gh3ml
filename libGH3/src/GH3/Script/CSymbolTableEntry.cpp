#include <GH3/Script/CSymbolTableEntry.hpp>

namespace GH3
{
	Script::CSymbolTableEntry*** Script::sp_hash_table = reinterpret_cast<Script::CSymbolTableEntry***>(0x00c03aa8);

	Script::CSymbolTableEntry* Script::LookUpSymbol(CRCKey key)
	{
		CSymbolTableEntry* entry = (*sp_hash_table)[key & 0x7FFF];

		//for (entry = (*sp_hash_table)[key & 0x7FFF]; (entry != NULL && (entry->NameKey != key));
		//	entry = entry->Next) {
		//}

		while (true)
		{
			if (entry->NameKey == key)
				break;

			if (entry == nullptr)
				return entry;

			entry = entry->Next;
		}

		return entry;
	}

	// TODO: V: THIS IS SHIT!
	Script::CSymbolTableEntry* Script::Resolve(CRCKey key)
	{
		CSymbolTableEntry* entry = LookUpSymbol(key);

		if (entry != nullptr)
		{
			CSymbolTableEntryType type = entry->Type;
			while ((uint32)type == 0xD || (uint32)type == 0x1A)
			{
				CSymbolTableEntry* entry2 = (*sp_hash_table)[entry->ChecksumValue & 0x7FFF];

				while (true)
				{
					if (entry2 == nullptr)
						goto LAB_004a591f;
					if (entry2->NameKey == entry->ChecksumValue)
						break;

					entry2 = entry2->Next;
				}
				if (entry2 == nullptr)
					break;
				entry = entry2;
				type = entry2->Type;
			}
		}

	LAB_004a591f:

		return entry;
	}

	uint32 Script::GetUInt32(CRCKey key)
	{
		CSymbolTableEntry* entry = Resolve(key);

		if (entry == nullptr)
			return 0;

		return entry->UInt32Value;
	}
	float Script::GetFloat(CRCKey key)
	{
		CSymbolTableEntry* entry = Resolve(key);

		if (entry == nullptr)
			return 0;
		if (entry->Type == Script::CSymbolTableEntryType::FLOAT)
			return entry->FloatValue;
		else if (entry->Type == Script::CSymbolTableEntryType::INTEGER)
			return (float)entry->UInt32Value;
	}
	char* Script::GetCString(CRCKey key)
	{
		CSymbolTableEntry* entry = Resolve(key);

		if (entry == nullptr)
			return 0;

		return entry->CStringValue;
	}
	CRCKey Script::GetChecksum(CRCKey key)
	{
		CSymbolTableEntry* entry = Resolve(key);

		if (entry == nullptr)
			return 0;

		return entry->ChecksumValue;
	}
}