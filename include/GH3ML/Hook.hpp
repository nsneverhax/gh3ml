#pragma once

#include <cstdint>

#include <vector>
#include <unordered_map>

#include <MinHook.h>

namespace gh3ml::hook
{
    struct HookData
    {
    public:

        uintptr_t Address;
        std::vector<uintptr_t> Hooks = std::vector<uintptr_t>();
        size_t OrigIndex = 0;
    };

    std::unordered_map<uintptr_t, HookData> Hooks;

    template<uintptr_t id, typename CConv, typename Ret, typename... Args>
    Ret Orig(Args... args)
    {
        auto& data = Hooks[id];
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

	namespace cconv
	{
		struct CDecl
		{
			template<uintptr_t id, typename Ret, typename... Args>
			static Ret __cdecl Handler(Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					Orig<id, CDecl, Ret, Args...>(args...);
				else
					return Orig<id, CDecl, Ret, Args...>(args...);
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
			template<uintptr_t id, typename Ret, typename... Args>
			static Ret __stdcall Handler(Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					Orig<id, STDCall, Ret, Args...>(args...);
				else
					return Orig<id, STDCall, Ret, Args...>(args...);
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

	template<uintptr_t id, typename Cconv, typename Ret, typename... Args>
	void CreateHook(uintptr_t address, Ret(&detour)(Args...))
	{
		bool isNew = !Hooks.contains(id);

		if (isNew)
			Hooks[id] = HookData();

		auto& data = Hooks[id];

		if (isNew)
		{
            data.Address = address;

			uintptr_t orig = 0;
			if (MH_CreateHook(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&Cconv::template Handler<id, Ret, Args...>), reinterpret_cast<void**>(&orig)) != MH_OK)
			{
				std::cout << "failed to hook: MH_CreateHook" << std::endl;
                return;
			}
			if (MH_EnableHook(reinterpret_cast<void*>(address)) != MH_OK)
            {
                std::cout << "failed to hook: MH_EnableHook" << std::endl;
                return;
            }
            std::cout << "hook" << std::endl;

			data.Hooks.push_back(orig);
		}

		data.Hooks.push_back(reinterpret_cast<uintptr_t>(&detour));
	}

    template<uintptr_t address, typename Cconv, typename Ret, typename... Args>
    void CreateHook(Ret(&detour)(Args...))
    {
        CreateHook<address, Cconv, Ret, Args...>(address, detour);
    }
}
