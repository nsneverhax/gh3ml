#pragma once

#include <GH3/Common.hpp>

#include <GH3/Spt/Class.hpp>

namespace GH3::Lst
{
	template<class T>
	class Node : public Spt::Class
	{
	private:
		T* data = nullptr;
		uint32_t priority = 0;
		Node<T>* next;
		Node<T>* prev;
	public:

		Node(T* data, uint32_t priority);
		virtual ~Node(void);

	};

	template<class T>
	Node<T>::Node(T* data, uint32_t priority)
	{
		this->data = data;
		this->priority = priority;
	}


}
