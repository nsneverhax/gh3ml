#pragma once

#include <GH3/Spt/Access.hpp>
#include <GH3/Tsk/List.hpp>

namespace GH3::Tsk
{
	class BaseTask : public Spt::Access
	{

	private:
		undefined4 a;
		Lst::Node<BaseTask>* m_node;
		undefined4 b;
		undefined4 c;
		undefined4 d;
	};

	SIZE_ASSERT(BaseTask, 0x18);
}