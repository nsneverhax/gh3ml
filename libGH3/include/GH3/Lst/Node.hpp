#pragma once

#include <GH3/Common.hpp>

#include <GH3/Spt/Class.hpp>

namespace GH3::Lst
{
	typedef int32_t Priority;

	enum class NodePriority : uint16_t
	{
		vNORMAL_PRIROITY = 0,
		VHEAD_NODE = UINT16_MAX
	};

	enum class SystemTaskPriority
	{
		PRIORITY_PROCESS_MODULES = -1000,
		PRIORITY_FLUSH_DEAD_OBJECTS = 1000
	};

	template<class T>
	class Node : public Spt::Class
	{
	private:
		T* m_data = nullptr;
		Priority m_priority = 0;
		Node<T>* m_next;
		Node<T>* m_previous;
	public:

		Node(T* data, Priority priority = NodePriority::vNORMAL_PRIROITY);
		virtual ~Node(void);

		void SetPriority(Priority priority);
		void SetNext(Node<T>* node);
		void SetPrevious(Node<T>* node);

		Priority GetPriority() const;
		Node<T> GetNext() const;
		Node<T> GetPrevious() const;
		T* GetData() const;

		Node<T>* IterateNext() const;
		Node<T>* IteratePrevious() const;

		bool IsInList() const;
		bool IsHead() const;

	};

	SIZE_ASSERT(Node<void*>, 0x14);

	template<class T>
	Node<T>::Node(T* data, Priority priority)
	{
		m_data = data;
		m_priority = priority;
	}


	template<class T>
	inline void Node<T>::SetPriority(Priority priority)
	{
		m_priority = priority;
	}
	template<class T>
	inline void Node<T>::SetNext(Node<T>* node)
	{
		m_next = node;
	}
	template<class T>
	inline void Node<T>::SetPrevious(Node<T>* node)
	{
		m_previous = node;
	}


	template<class T>
	Priority Node<T>::GetPriority() const
	{
		return m_priority;
	}
	template<class T>
	Node<T> Node<T>::GetNext() const
	{
		return m_next->IsHead() ? nullptr : m_next;
	}
	template<class T>
	Node<T> Node<T>::GetPrevious() const
	{
		return m_previous->IsHead() ? nullptr : m_previous;
	}
	template <class T>
	T* Node<T>::GetData() const
	{
		return m_data;
	}


	template <class T>
	bool Node<T>::IsInList() const
	{
		return m_previous != this;
	}
	template <class T>
	bool Node<T>::IsHead() const
	{
		return m_data == reinterpret_cast<void*>(NodePriority::VHEAD_NODE);
	}
}
