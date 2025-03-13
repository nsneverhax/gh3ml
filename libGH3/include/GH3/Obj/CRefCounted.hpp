#pragma once

#include <GH3/Spt/Class.hpp>

namespace GH3::Obj
{
	template<class T>
	class CSmtPtr;


	class CRefCounted : public Spt::Class
	{
	protected:
		CSmtPtr<CRefCounted>* mp_pointerList;
	public:

		virtual ~CRefCounted();

		void AddSmartPointer(CSmtPtr<CRefCounted>* smtPtr);
		void RemoveSmartPointer(CSmtPtr<CRefCounted>* smtPtr);
		void NotifySmartPointers();
	};
}