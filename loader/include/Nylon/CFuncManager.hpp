#pragma once

#include <cstdint>

#include <map>
#include <string>

#include <Nylon/LogSource.hpp>

#include <GH3/CFunc.hpp>

namespace nylon
{
	class CFuncManager
	{
	private:
		std::map<uintptr_t, std::string> m_functions = { };
		LogSource log = LogSource("CFuncManager");

	public:
		CFuncManager();

		/// <summary>
		/// Registers the current CFunc map into the global hashmap
		/// </summary>
		void Register();

		void Add(const gh3::CFuncDescriptor& descriptor);
	};



}
