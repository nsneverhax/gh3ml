#include <GH3/Mdl/Manager.hpp>
#include <GH3/Common.hpp>
#include <GH3/Mdl/Module.hpp>


namespace GH3::Mdl
{
	void Mdl::Manager::StartModule(Module* mdl)
	{
		NEEDS_TESTING();
		if (!mdl->Locked)
		{
			mdl->Command = Module::vSTART;
			this->ControlChange = true;
		}
	}

	void Manager::RegisterModule(Module* mdl)
	{
		NEEDS_TESTING();
		GH3::Lst::Node<Module>* node = mdl->Node;
		node->SetPrevious(ModuleList.GetNext());
		node->SetNext(&ModuleList);
		ModuleList.SetPrevious(node);
	}
}