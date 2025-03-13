#pragma once

#include <GH3/Common.hpp>

#include <GH3/Obj/CRefCounted.hpp>

namespace GH3::Obj
{
	class Script::CScript;
	// class Script::CStruct;

	// TODO: THIS!!!
	class CObject : public CRefCounted
	{
	public:
		class CAliveRefCounted : public CRefCounted
		{

		};

		virtual ~CObject()
		{

		}

		virtual void FUN_00d98e8a(void* param_1)
		{
			NEEDS_IMPLEMENTATION();
			reinterpret_cast<void(__thiscall*)(CObject*, void*)>(0x004e5460)(this, param_1);
		}
		virtual void SetProperties(void* param_1)
		{
			NEEDS_IMPLEMENTATION();
			reinterpret_cast<void(__thiscall*)(CObject*, void*)>(0x004e53b0)(this, param_1);
		}

		void RemoveTagsFromScript(uint32 param_1)
		{
			NEEDS_IMPLEMENTATION();
			reinterpret_cast<void(__thiscall*)(CObject*, int)>(0x00d98a1f)(this, param_1);
		}


		uint32 Flags;
		void* Manager;
		CScript* Script;
		void* field3; // QbStructItemField4_0x14
		undefined4 field5;
		CRCKey field6;
		float field7;
		undefined4 field8;
		void* field9; // QbStructItemField12_0x28
		CRCKey field10;
		undefined4 field11;
		float field12;
		undefined1** field13;
		undefined1* field14;
		undefined4 field15;
		undefined1*** Previous; // Previous?
		undefined1*** Next; // Next?
		undefined4 field18;
		CRCKey field19;
		undefined4 field20;
		CAliveRefCounted _base_CAliveRefCounted;
		undefined4 field22;
	};

	SIZE_ASSERT(CObject::CAliveRefCounted, 0x8);
	SIZE_ASSERT(CObject, 0x64);

}