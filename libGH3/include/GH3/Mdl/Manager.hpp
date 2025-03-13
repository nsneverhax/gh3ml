#pragma once

#include <GH3/Spt/Class.hpp>
#include <GH3/Lst/Head.hpp>

#include <GH3/Tsk/Task.hpp>
#include <GH3/Mdl/Module.hpp>

namespace GH3::Mdl
{
	class Manager : public Spt::Class
	{
	public:
		Tsk::Task<Mdl::Manager>* ProcessModulesTask;
		Lst::Head<Mdl::Module> ModuleList;
		bool ControlChange;

		void RegisterModule(Module* mdl);
		void StartModule(Module* mdl);

	};

	SIZE_ASSERT(Manager, 0x1C);
}
