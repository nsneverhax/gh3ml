#pragma once

#include <GH3/Common.hpp>
#include <GH3/Spt/Class.hpp>
#include <GH3/Lst/HashTable.hpp>
#include <GH3/Obj/CObject.hpp>
#include <GH3/Obj/CEventReceiverList.hpp>
#include <GH3/Obj/CEventLog.hpp>

#include <GH3/Spt/Singleton.hpp>

namespace GH3::Obj
{
	class CTracker : public Spt::Class
	{
		uint32_t IDSeed;
		Lst::HashTable<CObject>* HashTable;
		Lst::HashTable<CObject>* AliasTable;
		Lst::HashTable<CEventReceiverList>* EventReceiverListTable;
		CEventReceiverList* EventListenerList;
		bool BlockEventLaunching;
		int32_t RecurseDepth;
		CEventLog EventLog;
		int32_t NextEventScript;

		void* field0x3D;
		undefined1 unknown[459];
		bool Debug;
	};

	SIZE_ASSERT(CTracker, 0x20C);
}

namespace GH3
{
	extern Spt::SingletonPtr<Obj::CTracker> Obj_CTracker;
}