#pragma once

#include <cstdint>

namespace GH3::Spt
{
	template <typename T>
	class SingletonPtr
	{
	public:
		SingletonPtr(T* self)
		{
			Instance = self;
		}


		T* operator->() const;
		T& operator*() const;

		T* Instance = nullptr;
		uint32_t InstanceCount = 0;
	};

	template <typename T> inline
	T* SingletonPtr<T>::operator->() const
	{
		return Instance;
	}
	template <typename T> inline
	T& SingletonPtr<T>::operator*() const
	{
		return *Instance;
	}

	// SingletonPtr<void> Mlp_Manager = { reinterpret_cast<void*>(0x00b4eb24) };
	// SingletonPtr<void> Mdl_Manager = { reinterpret_cast<void*>(0x00b4eb18) };
}