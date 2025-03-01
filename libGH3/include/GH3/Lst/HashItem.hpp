#pragma once

#include <GH3/Common.hpp>

namespace GH3::Lst
{
	template <class T>
	class HashItem
	{
	public:
		CRCKey Key;
		T* Value;

		HashItem<T>* Next;
		// friend class HashTable<T>;
	};
}