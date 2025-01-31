#pragma once

#include <cstdint>

// TODO: IMPROVE THIS
struct Node
{
public:
	void** Vftable = nullptr;
	void* Data = nullptr;
	uint32_t Unknown = 0;

	Node* Previous = nullptr;;
	Node* Next = nullptr;
};