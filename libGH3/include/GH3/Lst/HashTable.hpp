#pragma once

#include <GH3/Common.hpp>

#include <GH3/Lst/HashItem.hpp>

namespace GH3::Lst
{
	template <class T>
	class HashTable
	{
	public:
		uint32_t Resolution;

		HashItem<T>* HashTable;
		int32_t Size;

		int32_t IteratorIndex;
		HashItem<T>* IteratorItem;
		bool AllowDuplicates;
	};
}