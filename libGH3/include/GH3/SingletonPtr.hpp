#pragma once

#include <cstdint>

namespace GH3
{
    template<typename T>
    class SingletonPtr
    {
        T* m_instance = { };
        uint32_t m_instanceCount = 0;

    public:


        T* Instance();
        uint32_t InstanceCount();
    };

    template<typename T>
    T* SingletonPtr<T>::Instance()
    {
        return m_instance;
    }
    template<typename T>
    uint32_t SingletonPtr<T>::InstanceCount()
    {
        return m_instanceCount;
    }

}