#pragma once

#include <GH3/Keys.hpp>

namespace GH3::CRC
{
	// V: Experimental
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


	// V: Actual proven stuff


	CRCKey GenerateCRC(const char* string, int size);
	CRCKey GenerateCRCFromString(const char* string);

}

#define HASH(x) GH3::CRC::GenerateCRCFromString(x)