#pragma once

#include <GH3/Common.hpp>
#include <GH3/Record.hpp>
#include <GH3/Lst/Head.hpp>

namespace GH3::Mem
{
	class Region;

	class Allocator
	{
	public:
		class Block
		{

		};
		class Context
		{

		};

		void** vftable;
		Record UsedBlocks;
		Record FreeBlocks;
		Record UsedMemory;
		Record FreeMemory;
		Region* Region;
		int32_t Direction;
		Block* FirstBlock;
		void* Top;
		char* Name;
		Context* CurrentContext;
		Context* InitialContext;
		Lst::Head<Context> ContextStack;
		Lst::Head<Allocator>* field0x54_unkListHead;
		Lst::Head<Allocator>* field0x58_unkListHead;
		Lst::Head<Allocator>* field0x5c_unkListHead;
		Lst::Head<Allocator>* field0x60_unkListHead;
		undefined4 field0x64;
		undefined4 field0x68;
		Lst::Head<Context>* ContextNodeHead;
		undefined4 field0x70;
		undefined4 field0x74;
		undefined4 field0x78;
	};

	SIZE_ASSERT(Allocator, 0x7C);

}