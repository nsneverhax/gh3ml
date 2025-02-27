#pragma once

#include <GH3/Spt/Class.hpp>

#include <cstdint>

namespace GH3::Spt
{
	class Access : public Spt::Class
	{
	private:
		int32_t m_count;

	public:
		Access();
		void Forbid();
		void Permit();
		void Enable();
		bool HaveAccess();
	};


	Access::Access()
	{
		m_count = 0;
	}

	void Access::Forbid()
	{
		m_count++;
	}

	void Access::Permit()
	{
		m_count--;
	}

	void Access::Enable()
	{
		m_count = 0;
	}

	bool Access::HaveAccess()
	{
		return m_count == 0;
	}

}


