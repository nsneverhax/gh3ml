#pragma once

#include <GH3/Common.hpp>
#include <GH3/Mdl/Module.hpp>
#include <GH3/Obj/CTracker.hpp>
#include <GH3/Tsk/Task.hpp>


namespace GH3::Ass
{
	class CAssMan : public Mdl::Module
	{
	public:
		undefined4 field0x14;
		void* field0x18;
		undefined4 unknownFields[32];

		Obj::CTracker* Tracker;

		void* field0xA0;
		undefined4 field0xA4;
		void* field0xA8;
		void* field0xAC;
		undefined4 field0xB0;
		undefined4 field0xB4;
		undefined4 field0xB8;
		undefined4 field0xBC;
		Tsk::Task<Ass::CAssMan>* Task;
	};

	SIZE_ASSERT(CAssMan, 0xC4);
}