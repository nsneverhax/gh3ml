#pragma once

#include <GH3/Lst/Node.hpp>

namespace GH3::Lst
{
	template <class T>
	class Head : public Node<T>
	{

	};

	SIZE_ASSERT(Head<void*>, 0x14);
}