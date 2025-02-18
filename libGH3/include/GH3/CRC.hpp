#pragma once

#include <GH3/Common.hpp>

namespace GH3::CRC
{
	struct ChecksumName
	{
		GH3::CRCKey Checksum;
		const char* Name;
	};

	extern ChecksumName* ChecksumNameHashTable;
	extern char* ChecksumNames;

	extern uint32_t CRC32TableLength;
	extern uint32_t* CRC32Table;

	CRCKey CreateKeyFromStringOut(CRCKey* outKey, const char* srcString);
	CRCKey CreateKeyFromString(const char* srcString);
	void CreateKeyNameAssociation(CRCKey key, char* name);

	char* FindChecksumName(CRCKey key);

}