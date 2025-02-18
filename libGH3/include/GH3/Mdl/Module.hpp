#pragma once

#include <GH3/Common.hpp>
#include <GH3/Spt/Class.hpp>
#include <GH3/Lst/Node.hpp>

namespace GH3::Mdl
{
	class Module : public Spt::Class
	{
	public:

		enum State : std::uint32_t
		{
			vSTOPPED,
			vRUNNING
		};

		enum Command : std::uint32_t
		{
			vNONE,
			vSTART,
			vSTOP,
			vRESTART
		};

		State State;
		Command Command;
		bool Locked;
		
		Lst::Node<Module>* Node;
	};

	SIZE_ASSERT(Module, 0x14);
}