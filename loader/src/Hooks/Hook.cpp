#include <Nylon/Hook.hpp>

std::unordered_map<uintptr_t, nylon::hook::HookData> nylon::hook::Hooks = { };
thread_local size_t nylon::hook::OrigIndex = 0;
