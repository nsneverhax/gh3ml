#pragma once

#include <d3d9.h>
#include <dinput.h>

namespace gh3
{
	static IDirect3DDevice9** Direct3DDevice = reinterpret_cast<IDirect3DDevice9**>(0x00c5c7a8);

	static IDirectInputDevice8** MouseDevice = reinterpret_cast<IDirectInputDevice8**>(0x00b4e368);
	static IDirectInputDevice8** KeyboardDevice = reinterpret_cast<IDirectInputDevice8**>(0x00b4e364);
}