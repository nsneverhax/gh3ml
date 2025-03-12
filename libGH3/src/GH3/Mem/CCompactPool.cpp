#include <GH3/Mem/CCompactPool.hpp>

namespace GH3::Mem
{
	void* CCompactPool::Allocate(uint32_t param_1)
	{
		if (FreeList == NULL)
			return NULL;

		CurrentUsedItems++;
		if (MaxUsedItems < CurrentUsedItems)
			MaxUsedItems = CurrentUsedItems;

		return this->FreeList;
	}
}