#pragma once

#include "Global.hpp"

namespace gh3::crc32
{
	extern uint32_t CRC32TableLength;
	extern uint32_t* CRC32Table;

	GH3Key CreateKeyFromStringOut(GH3Key* outKey, const char* srcString);
	GH3Key CreateKeyFromString(const char* srcString);
	void CreateKeyNameAssociation(GH3Key key, char* name);
}