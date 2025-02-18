#pragma once

#include "Keys.hpp"

namespace GH3::CRC
{
	extern uint32_t CRC32TableLength;
	extern uint32_t* CRC32Table;

	CRCKey CreateKeyFromStringOut(CRCKey* outKey, const char* srcString);
	CRCKey CreateKeyFromString(const char* srcString);
	void CreateKeyNameAssociation(CRCKey key, char* name);
}