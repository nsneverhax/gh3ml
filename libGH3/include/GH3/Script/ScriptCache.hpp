#pragma once

#include <GH3/Common.hpp>

#include <GH3/SingletonPtr.hpp>

#include <GH3/Mdl/Module.hpp>

namespace GH3
{
	namespace Script
	{
		class ScriptCache : Mdl::Module
		{
		public:
			void* Member2_0x14;
			undefined4 Member0x18;
			undefined4 Member0x1C;
			undefined4 Member_0x20;
		};

		static_assert(sizeof(ScriptCache) == 0x24);
	}

	SingletonPtr<GH3::Script::ScriptCache> Script_Cache;

}