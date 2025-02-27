#pragma once

#include <GH3/Spt/Class.hpp>
#include <GH3/Lst/Head.hpp>

#include <GH3/Tsk/Task.hpp>
#include <GH3/Mdl/Module.hpp>

namespace GH3::Mdl
{
	class Manager : public Spt::Class
	{
		Tsk::Task<Mdl::Manager> ProcessModulesTask;
		Lst::Head<Mdl::Module> ModuleList;
		bool ControlChange;
	};

	// SIZE_ASSERT(Manager, 0x18);
}
