#pragma once

#include <GH3/Tsk/BaseTask.hpp>

namespace GH3::Tsk
{
	template <typename T>
	class Task : public BaseTask
	{
	public:

		typedef void(TaskEntryPoint)(const Task<T>&);

	// private:

		TaskEntryPoint* m_taskEntryPoint;
		T& m_data;
	};

	SIZE_ASSERT(Task<void*>, 0x20);
}