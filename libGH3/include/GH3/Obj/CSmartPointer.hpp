#pragma once

#include <GH3/Common.hpp>

namespace GH3::Obj
{
	class CRefCounted;

	template <class T>
	class CSmartPointer
	{
	public:
		T* Data;
		CSmartPointer<CRefCounted>* Previous;
		CSmartPointer<CRefCounted>* Next;
	};
}