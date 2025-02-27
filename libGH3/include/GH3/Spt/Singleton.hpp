#pragma once

#include <cstdint>

namespace GH3::spt
{
	template <typename T>
	class SingletonPtr
	{
	public:
		SingletonPtr(T* self)
		{
			Instance = self;
		}

		T* Instance = nullptr;
		uint32_t InstanceCount = 0;
	};


	SingletonPtr<void> Obj_CTracker = { reinterpret_cast<void*>(0x00b4f360) };
	SingletonPtr<void> Mlp_Manager = { reinterpret_cast<void*>(0x00b4eb24) };
	SingletonPtr<void> Mdl_Manager = { reinterpret_cast<void*>(0x00b4eb18) };
}