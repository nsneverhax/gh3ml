#pragma once

#include <GH3/Common.hpp>

namespace GH3::Obj
{
	class CRefCounted;

	template <class T>
	class CSmtPtr
	{
	public:
		T* Data;
		CSmtPtr<CRefCounted>* Previous;
		CSmtPtr<CRefCounted>* Next;
	};
}