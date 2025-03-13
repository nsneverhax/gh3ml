#pragma once

#include <GH3/Spt/Class.hpp>

namespace GH3::Obj
{
	template<class T>
	class CSmtPtr;


	class CRefCounted : public Spt::Class
	{
	public:
		void** vftable;
		CSmtPtr<CRefCounted>* PointerList;

		void AddSmartPointer(CSmtPtr<CRefCounted>* smtPtr);
		void RemoveSmartPointer(CSmtPtr<CRefCounted>* smtPtr);
		void NotifySmartPointers();
	};
}