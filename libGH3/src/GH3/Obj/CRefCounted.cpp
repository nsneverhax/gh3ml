#include <GH3/Obj/CRefCounted.hpp>
#include <GH3/Obj/CSmartPointer.hpp>

namespace GH3::Obj
{

	void CRefCounted::AddSmartPointer(CSmtPtr<CRefCounted>* smtPtr)
	{
		smtPtr->Next = this->PointerList;
		if (this->PointerList != NULL) {
			this->PointerList->Previous = smtPtr;
		}
		this->PointerList = smtPtr;
	}
	void CRefCounted::RemoveSmartPointer(CSmtPtr<CRefCounted>* smtPtr)
	{
		if (smtPtr->Previous == NULL) {
			this->PointerList = smtPtr->Next;
		}
		else {
			smtPtr->Previous->Next = smtPtr->Next;
		}
		if (smtPtr->Next != NULL) {
			smtPtr->Next->Previous = smtPtr->Previous;
		}
		smtPtr->Next = NULL;
		smtPtr->Previous = NULL;
	}
	void CRefCounted::NotifySmartPointers()
	{
		CSmtPtr<CRefCounted>* pCVar1;
		CRefCounted* piVar2;
		CSmtPtr<CRefCounted>* piVar1;

		pCVar1 = this->PointerList;
		while (pCVar1 != NULL) {
			piVar1 = pCVar1->Next;
			if (pCVar1->Data != NULL) {
				if (pCVar1->Previous == NULL) {
					pCVar1->Data->PointerList = piVar1;
				}
				else {
					pCVar1->Previous->Next = piVar1;
				}
				if (pCVar1->Next != NULL) {
					pCVar1->Next->Previous = pCVar1->Previous;
				}
				pCVar1->Previous = NULL;
				pCVar1->Next = NULL;
				pCVar1->Data = NULL;
			}
			pCVar1->Data = NULL;
			pCVar1 = piVar1;
		}
	}
}