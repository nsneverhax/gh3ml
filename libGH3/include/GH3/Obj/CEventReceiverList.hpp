#pragma once

#include <GH3/Common.hpp>
#include <GH3/Spt/Class.hpp>
#include <GH3/Lst/Head.hpp>
#include <GH3/Obj/CObject.hpp>

namespace GH3::Obj
{
	class CEventReceiverList : public Spt::Class
	{
	public:
		Lst::Head<CObject> ObjectList;
	};
}