#pragma once

#include <GH3/Spt/Class.hpp>

namespace GH3::Obj
{
	template<class T>
	class CSmartPointer;


	class CRefCounted : public Spt::Class
	{
	public:
		void** vftable;
		CSmartPointer<CRefCounted>* PointerList;
	};
}