#include <Nylon/CFuncManager.hpp>

#include <Nylon/Hook.hpp>


nylon::CFuncManager::CFuncManager()
{
	for (uint32_t i = 0; i < gh3::CFuncArrayCount; i++)
	{
		auto descriptor = gh3::CFuncArray[i];

		m_functions.emplace(reinterpret_cast<uintptr_t>(descriptor.Function), std::string(descriptor.Name));
	}
}

void nylon::CFuncManager::Register()
{
	// TODO: REIMPLEMENT THE DAMN CFUNC FUNC

	// Vultu: I don't feel like reimplementing it right now so let's just put our data into a format
	// that the GH3 function will like, this *should* only be called once ever, so... 

	gh3::CFuncDescriptor* funcs = new gh3::CFuncDescriptor[m_functions.size()];

	uint32_t i = 0;
	for (auto kv : m_functions)
	{
		funcs[i] = gh3::CFuncDescriptor();
		funcs[i].Function = reinterpret_cast<void*>(kv.first);
		funcs[i].Name = kv.second.data();
		i++;
	}

	NodeArray_SetCFuncInfo::Orig(funcs, m_functions.size());
	delete[] funcs;

	log.Info("Registered %d functions.", i);
}

void nylon::CFuncManager::Add(const gh3::CFuncDescriptor& descriptor)
{
	m_functions.emplace(reinterpret_cast<uintptr_t>(descriptor.Function), std::string(descriptor.Name));
}
