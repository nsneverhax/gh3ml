#include <Nylon/CFuncManager.hpp>
#include "DefaultCFuncs.hpp"

#include <Nylon/Hook.hpp>


nylon::CFuncManager::CFuncManager()
{
	for (uint32_t i = 0; i < GH3::CFuncArrayCount; i++)
	{
		auto descriptor = GH3::CFuncArray[i];

		m_functions.emplace(reinterpret_cast<uintptr_t>(descriptor.Function), std::string(descriptor.Name));
	}
}

#include <iostream>
#include <fstream>

void nylon::CFuncManager::Register()
{
	// TODO: REIMPLEMENT THE DAMN CFUNC FUNC

	// Vultu: I don't feel like reimplementing it right now so let's just put our data into a format
	// that the GH3 function will like, this *should* only be called once ever, so... 

	GH3::CFuncDescriptor* funcs = new GH3::CFuncDescriptor[m_functions.size()];

	std::ofstream myfile("example.txt");

	uint32_t i = 0;
	for (auto kv : m_functions)
	{
		funcs[i] = GH3::CFuncDescriptor();
		funcs[i].Function = reinterpret_cast<void*>(kv.first);
		funcs[i].Name = kv.second.data();

		std::uint8_t magic = *reinterpret_cast<std::uint8_t*>(kv.first + 2);

		if (magic == 0xC3)
			myfile << "[S] ";
		else
			myfile << "[ ] ";
		myfile << kv.second.data() << "\n";
		i++;
	}
	myfile.close();

	NodeArray_SetCFuncInfo::Orig(funcs, m_functions.size());
	delete[] funcs;

	// log.Info("Registered %d functions.", i);
}

void nylon::CFuncManager::Add(const GH3::CFuncDescriptor& descriptor)
{
	m_functions.emplace(reinterpret_cast<uintptr_t>(descriptor.Function), std::string(descriptor.Name));
}
