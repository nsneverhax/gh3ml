#pragma once

#include <cstdint>

#include <vector>
#include <unordered_map>

#include <MinHook.h>

// TODO: this is dumb!
#include "../src/Main.hpp"

#include <format>

namespace nylon::hook
{
    struct HookData
    {
    public:

        uintptr_t Address = NULL;
        std::vector<uintptr_t> Hooks = std::vector<uintptr_t>();
        size_t OrigIndex = 0;
    };

    extern std::unordered_map<uintptr_t, HookData> Hooks;

    template<uintptr_t id, typename Cconv, typename Ret, typename... Args>
    Ret Orig(Args... args)
    {
        auto& data = Hooks[id];
        size_t index = data.Hooks.size() - ++data.OrigIndex;

        if constexpr (std::is_same_v<Ret, void>)
        {
            if (index == 0)
                Cconv::template Trampoline<Ret, Args...>(data.Hooks[index], args...);
            else
                reinterpret_cast<Ret(*)(Args...)>(data.Hooks[index])(args...);
            data.OrigIndex--;
        }
        else
        {
            Ret ret;
            if (index == 0)
                ret = Cconv::template Trampoline<Ret, Args...>(data.Hooks[index], args...);
            else
                ret = reinterpret_cast<Ret(*)(Args...)>(data.Hooks[index])(args...);
            data.OrigIndex--;
            return ret;
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


		struct ThisCall
		{
			template<uintptr_t id, typename Ret, typename... Args>
			static Ret __thiscall Handler(Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					Orig<id, ThisCall, Ret, Args...>(args...);
				else
					return Orig<id, ThisCall, Ret, Args...>(args...);
			}

			template<typename Ret, typename... Args>
			static Ret Trampoline(uintptr_t address, Args... args)
			{
				if constexpr (std::is_same_v<Ret, void>)
					reinterpret_cast<Ret(__thiscall*)(Args...)>(address)(args...);
				else
					return reinterpret_cast<Ret(__thiscall*)(Args...)>(address)(args...);
			}
		};
	}

	template<uintptr_t id, typename Cconv, typename Ret, typename... Args>
	void CreateHook(uintptr_t address, Ret(&detour)(Args...), const char* name = nullptr)
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
				nylon::internal::Log.Error("Failed to hook function at address: {:X}", address);
                return;
			}
			if (MH_EnableHook(reinterpret_cast<void*>(address)) != MH_OK)
            {
				nylon::internal::Log.Error("Failed to enable function hook with address: {:X}", address);
                return;
            }
			nylon::internal::Log.Info("Hooked function at address: 0x{:X}", address);

			data.Hooks.push_back(orig);
		}

		data.Hooks.push_back(reinterpret_cast<uintptr_t>(&detour));
	}

    template<uintptr_t address, typename Cconv, typename Ret, typename... Args>
    void CreateHook(Ret(&detour)(Args...))
    {
        CreateHook<address, Cconv, Ret, Args...>(address, detour);
    }

    template<uintptr_t Address, typename Cconv, typename Ret, typename... Args>
    struct Binding {
        static constexpr uintptr_t address = Address;
        using cconv = Cconv;
        using func = Ret(&)(Args...);
        Ret value;
        explicit Binding(Args... args) {
            value = Cconv::template Trampoline<Ret, Args...>(Address, args...);
        }
        operator Ret() const { return value; } // NOLINT(*-explicit-constructor)
        static Ret Orig(Args... args) {
            return nylon::hook::Orig<Address, Cconv, Ret, Args...>(args...);
        }
    };

    template<uintptr_t Address, typename Cconv, typename... Args>
    struct Binding<Address, Cconv, void, Args...> {
        static constexpr uintptr_t address = Address;
        using cconv = Cconv;
        using func = void(&)(Args...);
        explicit Binding(Args... args) {
            Cconv::template Trampoline<void, Args...>(Address, args...);
        }
        static void Orig(Args... args) {
            nylon::hook::Orig<Address, Cconv, void, Args...>(args...);
        }
    };

    template<typename Binding>
    void CreateHook(typename Binding::func detour)
    {
        CreateHook<Binding::address, typename Binding::cconv>(Binding::address, detour);
    }
}

namespace nylon
{
	using NodeArray_SetCFuncInfo = hook::Binding<0x00d94ee8, hook::cconv::CDecl, void, void*, uint32_t>;
}
