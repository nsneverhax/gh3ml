#pragma once

#include <GH3/Common.hpp>

namespace GH3::Script
{
	class CStruct;
	class CArray;

	CStruct* GetStructure(CRCKey key);
	CArray* GetArray(CRCKey key);
}