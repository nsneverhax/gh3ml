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
		undefined1* This; // this???
	};
	SIZE_ASSERT(CObject::CAliveRefCounted, 0x8);
	SIZE_ASSERT(CObject, 0x64);

}