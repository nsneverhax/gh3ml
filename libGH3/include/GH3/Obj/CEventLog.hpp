#pragma once

#include <GH3/Common.hpp>
#include <GH3/Lst/HashTable.hpp>

namespace GH3::Obj
{
	class CEventLog
	{
	public:
		enum class OccuranceType : uint32_t
		{
			LAUNCH,
			HANDLE,
			READ,
			UPDATE,
			OBJECT_ADD,
			OBJECT_REMOVE
		};

		struct EventEntry
		{
			uint32_t Type;
			uint32_t Target;
			uint32_t Source;
			uint32_t Receiver;
			OccuranceType OccuranceType;
			int Depth;
		};


		EventEntry* Entries;
		uint32_t NextEntry;
		bool Wrap;
		char** EventNameList;
		Lst::HashTable<char*>* EventNameTable;
		int32_t Depth;
		int32_t NewEntries;
	};

	SIZE_ASSERT(CEventLog, 0x19);
}