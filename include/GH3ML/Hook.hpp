#pragma once

#include <cstdint>

#include <vector>
#include <unordered_map>

#include <MinHook.h>

namespace gh3ml::hook
{
	namespace cconv
	{
		struct CDecl
		{
			template<uintptr_t offset, typename Ret, typename... Args>
			static Ret __cdecl Handler(Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					Orig<offset, CDecl, Ret, Args...>(args...);
				else
					return Orig<offset, CDecl, Ret, Args...>(args...);
			}

			template<typename Ret, typename... Args>
			static Ret Trampoline(uintptr_t address, Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					reinterpret_cast<Ret(__cdecl*)(Args...)>(address)(args...);
				else
					return reinterpret_cast<Ret(__cdecl*)(Args...)>(address)(args...);
			}

		};

		struct STDCall
		{
			template<uintptr_t offset, typename Ret, typename... Args>
			static Ret __stdcall Handler(Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					Orig<offset, STDCall, Ret, Args...>(args...);
				else
					return Orig<offset, STDCall, Ret, Args...>(args...);
			}

			template<typename Ret, typename... Args>
			static Ret Trampoline(uintptr_t address, Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					reinterpret_cast<Ret(__stdcall*)(Args...)>(address)(args...);
				else
					return reinterpret_cast<Ret(__stdcall*)(Args...)>(address)(args...);
			}

		};
	}

	uintptr_t ModuleBase = 0;

	struct HookData
	{
	public:

		std::vector<uintptr_t> Hooks = std::vector<uintptr_t>();
		size_t OrigIndex = 0;

		// uintptr_t GetAddress() const;
	};


	std::unordered_map<uintptr_t, HookData> Hooks;

	template<uintptr_t offset, typename Cconv, typename Ret, typename... Args>
	void CreateHook(Ret(__cdecl &detour)(Args...))
	{
		auto address = offset;
		bool isNew = !Hooks.contains(address);

		if (isNew)
			Hooks[address] = HookData();

		auto& data = Hooks[address];

		if (isNew)
		{
			uintptr_t orig = 0;
			if (MH_CreateHook(reinterpret_cast<void*>(address), &cconv::CDecl::Handler<offset, Ret, Args...>, reinterpret_cast<void**>(&orig)) != MH_OK)
			{
				std::cout << "failed to hook" << std::endl;

			}
			else
				std::cout << "hook" << std::endl;

			data.Hooks.push_back(orig);
		}

		data.Hooks.push_back(reinterpret_cast<uintptr_t>(&detour));
	}

	template<uintptr_t offset, typename Cconv, typename Ret, typename... Args>
	void CreateHook(Ret(__stdcall& detour)(Args...))
	{
		auto address = offset;
		bool isNew = !Hooks.contains(address);

		if (isNew)
			Hooks[address] = HookData();

		auto& data = Hooks[address];

		if (isNew)
		{
			uintptr_t orig = 0;
			if (MH_CreateHook(reinterpret_cast<void*>(address), &Cconv::template Handler<offset, Ret, Args...>, reinterpret_cast<void**>(&orig)) != MH_OK)
			{
				std::cout << "failed to hook" << std::endl;

			}
			else
				std::cout << "hook" << std::endl;

			data.Hooks.push_back(orig);
		}

		data.Hooks.push_back(reinterpret_cast<uintptr_t>(detour));
	}

	template<uintptr_t offset, typename CConv, typename Ret, typename... Args>
	Ret Orig(Args... args) 
	{
		auto addr = offset;
		auto& data = Hooks[addr];
		size_t index = data.Hooks.size() - ++data.OrigIndex;

		if (index == 0)
			data.OrigIndex = 0;

		if constexpr (std::is_same_v<Ret, void>) 
		{
			if (index == 0) 
				CConv::template Trampoline<Ret, Args...>(data.Hooks[index], args...);
			else 
				reinterpret_cast<Ret(*)(Args...)>(data.Hooks[index])(args...);
		}
		else 
		{
			if (index == 0)
				return CConv::template Trampoline<Ret, Args...>(data.Hooks[index], args...);
			else
				return reinterpret_cast<Ret(*)(Args...)>(data.Hooks[index])(args...);
		}
	}
}