#include <Nylon/Internal/Main.hpp>
#include "../Imgui/Imgui.hpp"
#include "DirectXHooks.hpp"
#include "CFuncHooks.hpp"

#include <Nylon/Hook.hpp>
#include <d3d9.h>
#include <Nylon/Core.hpp>
#include <filesystem>
#include <Nylon/Config.hpp>
#include <iostream>
#include <dinput.h>
#include <GH3/CFunc.hpp>
#include <GH3/Addresses.hpp>
#include <MinHook.h>

#include <Nylon/CFuncManager.hpp>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <GH3/EngineParams.hpp>

#include <GH3/DirectX.hpp>
#include <GH3/CRC.hpp>

#include <XInput.h>

namespace cfg = nylon::config;
constexpr int INST_NOP = 0x90;

constexpr int FUNC_INITIALIZEDEVICE = 0x0057B940;

extern float* DeltaTime = reinterpret_cast<float*>(0x009596bc);

// TEMP
nylon::CFuncManager _CFuncManager;

#pragma region Default Hooks
using DebugLog = nylon::hook::Binding<0x00472b50, nylon::hook::cconv::CDecl, void, char*, va_list>;

void detourDebugLog(char* fmt, va_list args)
{
    //nylon::internal::LogGH3.Info(fmt, args);

    DebugLog::Orig(fmt, args);
}


HWND WindowHandle = nullptr;

HWND detourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    uint32_t* debugFullScreen = reinterpret_cast<uint32_t*>(0x00c4cbdc);

    uint32_t style = 0;
    switch (cfg::GameWindowStyle())
    {
    case cfg::WindowStyle::Fullscreen:
        *debugFullScreen = 1;
        break;
    case cfg::WindowStyle::Windowed:
        *debugFullScreen = 0;
        style = WS_TILEDWINDOW;
        break;
    case cfg::WindowStyle::BorderlessWindowed:
        *debugFullScreen = 0;
        style = WS_POPUP;
        break;
    case cfg::WindowStyle::BorderlessFullscreen:
        *debugFullScreen = 0;
        style = WS_POPUP;
        break;
    default:
        break;
    }
    WindowHandle = nylon::hook::Orig<1, nylon::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, WS_TILEDWINDOW, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);


    return WindowHandle;
}

LRESULT detourDispatchMessageA(MSG* lmMsg)
{
    LRESULT windProcResult = 0;

    // V: Aspyr in their infinite wisdom didn't translate the fucking messages
    ::TranslateMessage(lmMsg);

    // V: For some reason WindProc isn't being called correctly, so this is moved here
    // TODO: look into this??
    if (windProcResult = nylon::imgui::WindowProc(lmMsg->hwnd, lmMsg->message, lmMsg->wParam, lmMsg->lParam))
        return windProcResult;

    return nylon::hook::Orig<1002, nylon::hook::cconv::STDCall, LRESULT, MSG*>(lmMsg);
}

constexpr int KeyboardSetCooperativeLevelID = 4;

HRESULT KeyboardSetCooperativeLevel(void* self, HWND hwnd, DWORD dwFlags)
{
    nylon::internal::Log.Info("KeyboardSetCooperativeLevel -> {:X}", dwFlags);
    auto ret = nylon::hook::Orig<KeyboardSetCooperativeLevelID, nylon::hook::cconv::STDCall, HRESULT>(self, hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    //(*gh3::KeyboardDevice)->Unacquire();

    return ret;
}
constexpr int MouseSetCooperativeLevelID = 5;

HRESULT MouseSetCooperativeLevel(void* self, HWND hwnd, DWORD dwFlags)
{
    nylon::internal::Log.Info("MouseSetCooperativeLevel -> {:X}", dwFlags);
    auto ret = nylon::hook::Orig<MouseSetCooperativeLevelID, nylon::hook::cconv::STDCall, HRESULT>(self, hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    //(*gh3::MouseDevice)->Unacquire();

    return ret;
}


using Video_InitializeDevice = nylon::hook::Binding<0x0057b940, nylon::hook::cconv::CDecl, void, void*>;

void detourVideo_InitializeDevice(void* engineParams)
{
    if (nylon::config::UnlockFPS())
    {
      // Vultu: We need to set the values we NOP'd out before
      union
      {
          uint8_t bytes[sizeof(uint32_t)];
          uint32_t value;
      } uint32_u;

       uint32_u.value = 0x01;

        nylon::WriteMemory(0x00c5b918, uint32_u.bytes, sizeof(uint32_t));

        uint32_u.value = D3DPRESENT_INTERVAL_IMMEDIATE;

        nylon::WriteMemory(0x00c5b934, uint32_u.bytes, sizeof(uint32_t));
    }

    Video_InitializeDevice::Orig(engineParams);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(WindowHandle);
    ImGui_ImplDX9_Init(*gh3::Direct3DDevice);

    nylon::internal::Log.Info("Hooking DirectX 9...");
    nylon::internal::CreateDirectXHooks();
    nylon::internal::Log.Info("Finished hooking DirectX 9.");

    uintptr_t* kbdVFTable = **reinterpret_cast<uintptr_t***>(gh3::KeyboardDevice);
    nylon::hook::CreateHook<KeyboardSetCooperativeLevelID, nylon::hook::cconv::STDCall>(
        kbdVFTable[13],
        KeyboardSetCooperativeLevel
    );

    uintptr_t* mseVFTable = **reinterpret_cast<uintptr_t***>(gh3::MouseDevice);
    nylon::hook::CreateHook<MouseSetCooperativeLevelID, nylon::hook::cconv::STDCall>(
        mseVFTable[13],
        MouseSetCooperativeLevel
    );
}

// using WindowProc = nylon::hook::Binding<0x00578880, nylon::hook::cconv::STDCall, LRESULT, HWND, UINT, WPARAM, LPARAM>;
LRESULT(__cdecl** AspyrDefWindowProcA)(HWND, UINT, WPARAM, LPARAM) = reinterpret_cast<LRESULT(__cdecl**)(HWND, UINT, WPARAM, LPARAM)>(0x00898020);
bool(__cdecl* Kbd_KeyboardStringHandler_sUpdate)(HWND, uint32_t, WPARAM, LPARAM) = reinterpret_cast<bool(__cdecl*)(HWND, uint32_t, WPARAM, LPARAM)>(0x00554850);

LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT windProcResult = 0;

    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_ENDSESSION:
        if (wParam != 0)
        {
            ExitProcess(0);
            return 0;
        }
        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xFFF0) == SC_SCREENSAVE || (wParam & 0xFFF0) == SC_MONITORPOWER)
            return 0;
        break;
    case WM_SETCURSOR:
        if (nylon::imgui::GetNylonMenuActive() && GetCursor() == NULL)
            SetCursor(LoadCursor(nullptr, IDC_ARROW));
        else
            SetCursor(NULL);
        return 0;
    default:
        break;
    }

    if (!nylon::imgui::GetNylonMenuActive())
    {
        if (windProcResult = Kbd_KeyboardStringHandler_sUpdate(hWnd, uMsg, wParam, lParam))
            return windProcResult;
    }

    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    //return (*AspyrDefWindowProcA)(hWnd, uMsg, wParam, lParam);
}

#pragma endregion


using func_SetNewWhammyValue = nylon::hook::Binding<0x0041de60, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*>;
bool detourSetNewWhammyValue(GH3::QbStruct* self)
{
    return SetNewWhammyValue(self);
    //return func_SetNewWhammyValue::Orig(self);
}


using CreateHighwayDrawRect = nylon::hook::Binding<0x00601d30, nylon::hook::cconv::CDecl, int, double*, float, float, float, float, float, float, float, float, float, float>;

int deoutCreateHighwayDrawRect(double * array, float param_2, float param_3, float whammyTopWidth, float param_5, float whammyWidthOffset , float param_7, float param_8, float param_9, float whammyTailEnd, float whammyTailBegin)
{
    // Vultu: I am not sure of the perf implications of calling this every call, but this will do until resizable windows get implemented i guess
    static int backBufferWidth = 0;
    // temp
    if (backBufferWidth == 0)
    {
        auto instance = (GH3::EngineParams::Instance());
        IDirect3DSurface9* pSurface;
        (*gh3::Direct3DDevice)->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
        D3DSURFACE_DESC SurfaceDesc;
        pSurface->GetDesc(&SurfaceDesc);
        backBufferWidth = SurfaceDesc.Width;
        pSurface->Release();
    }
    
    float whammySizeMultiplier = ((float)backBufferWidth / 1280.0f);
    return CreateHighwayDrawRect::Orig(
        array, 
        param_2 * whammyMultipliers[1],
        param_3 * whammyMultipliers[2], // Whammy Tail Lower ??
        whammyTopWidth * whammySizeMultiplier, 
        param_5 * whammyMultipliers[3] * whammySizeMultiplier,
        whammyWidthOffset * whammySizeMultiplier,
        param_7 * whammySizeMultiplier, 
        param_8 * whammyMultipliers[5],
        param_9 * whammyMultipliers[6],
        whammyTailEnd * whammyMultipliers[7], // Whammy Glow ??
        whammyTailBegin * whammyMultipliers[8] // Whammy Tail Begin
    );
}

using Nx_DirectInput_InitMouse = nylon::hook::Binding<0x0047dfa0, nylon::hook::cconv::CDecl, HRESULT>;

HRESULT detourNx_DirectInput_InitMouse()
{
    HRESULT ret = Nx_DirectInput_InitMouse::Orig();


    return ret;

}

using D3DDeviceLostFUN_0057ae20 = nylon::hook::Binding<0x0057ae20, nylon::hook::cconv::CDecl, void>;

void detourD3DDeviceLostFUN_0057ae20()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    D3DDeviceLostFUN_0057ae20::Orig();
    ImGui_ImplDX9_CreateDeviceObjects();
}

void detourNodeArray_SetCFuncInfo(void* startAddress, uint32_t count)
{
    // Vultu: Don't do anything becuase CFunc Manager will handle it all
}

using CFuncWait = nylon::hook::Binding<0x0052eaf0, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*, void*>;

bool detourCFuncWait(GH3::QbStruct* params, void* script)
{
    // Vultu: Write out deltatime to the memory before we get there, honestly it might be better to rewrite this function later.

    union
    {
        float value = 0;
        uint8_t bytes[sizeof(float)];
    } deltaBuffer;

    float waitTime = 0;
    params->GetFloat(0, waitTime);


    deltaBuffer.value = (*DeltaTime) * 1000.0f; // convert to ms

    nylon::WriteMemory(0x008a71bc, deltaBuffer.bytes, sizeof(float));

    auto orig = CFuncWait::Orig(params, script);

    // Restore this to be safe
    //deltaBuffer.value = 16.666666f;
    //nylon::WriteMemory(0x008a71bc, deltaBuffer.bytes, sizeof(float));

    return orig;
}

using Time_UpdateTime = nylon::hook::Binding<0x00492780, nylon::hook::cconv::CDecl, void>;
void detourTimeUpdateTime()
{
    double frameTime = *GH3::Time::DOUBLE_00b544b8;
    *GH3::Time::CurrentFrameTime = *GH3::Time::CurrentSlowDown;

    double temp = *reinterpret_cast<double*>(0x008b1068);
    double awawa = (1.0 / 60.0);
    if (((*GH3::Time::UnknownFrameTimeRelated_009596c8) * frameTime * 100 < *GH3::Time::DOUBLE_00b544b8) || *GH3::Time::DOUBLE_00b544b8 < 0.0)
    {
        frameTime = (*GH3::Time::UnknownFrameTimeRelated_009596c8) * frameTime;
    }
    *GH3::Time::NoSlowFrameTime = (float)frameTime;
    *GH3::Time::DOUBLE_00b544b0 = *GH3::Time::DOUBLE_00b544b8;
    *GH3::Time::DeltaTime = (float)frameTime * *GH3::Time::CurrentSlowDown;
}

using CRC_CreateKeyNameAssociation = nylon::hook::Binding<0x004a6820, nylon::hook::cconv::CDecl, void, GH3::CRCKey, char*>;
void detour__CRC_CreateKeyNameAssociate(GH3::CRCKey key, char* string)
{
    CRC_CreateKeyNameAssociation::Orig(key, string);
}

ATOM detour__RegisterClassA(WNDCLASSA* lpWndClass)
{
    lpWndClass->lpfnWndProc = WindowProc;
    return RegisterClassA(lpWndClass);
}


using ControllerUpdate = nylon::hook::Binding<0x0047e5b0, nylon::hook::cconv::CDecl, void, void*>;
void detour__ControllerUpdate(void* manager) 
{
    if (nylon::imgui::GetNylonMenuActive())
        return;

    ControllerUpdate::Orig(manager);
}

using CRC_FindChecksumeName = nylon::hook::Binding<0x004A69A0, nylon::hook::cconv::CDecl, char*, GH3::CRCKey>;
char* detour__CRC_FindChecksumeName(GH3::CRCKey key)
{
    char* origName = CRC_FindChecksumeName::Orig(key);

    if (nylon::internal::KeyAssociations.contains(key))
        return nylon::internal::KeyAssociations[key].data();

    return origName;
}

void nylon::internal::SetupDefaultHooks()
{
    Log.Info("Setting up default hooks...");

    // Vultu: I really don't feel like rewriting the entire function for right now
    // so I'm going NOP where some global variables are set
    uint8_t buffer[6];
    memset(buffer, INST_NOP, sizeof(buffer));

    if (nylon::config::UnlockFPS())
    {

        nylon::WriteMemory(FUNC_INITIALIZEDEVICE + 0x1C7, buffer, sizeof(buffer)); // 0x0057BB07 : dword ptr [D3DPresentParams.SwapEffect],EDI
        nylon::WriteMemory(FUNC_INITIALIZEDEVICE + 0x239, buffer, sizeof(buffer)); // 0x0057bb79 : dword ptr [D3DPresentParams.PresentationInterval],EDI
    }


    nylon::hook::CreateHook<1, nylon::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA")),
        detourCreateWindowExA
    );

    nylon::hook::CreateHook<1002, nylon::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "DispatchMessageA")),
        detourDispatchMessageA
    );

    nylon::hook::CreateHook<1003, nylon::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "RegisterClassA")),
        detour__RegisterClassA
    );

    nylon::internal::CreateCFuncHooks();

    nylon::hook::CreateHook<DebugLog>(detourDebugLog);
    nylon::hook::CreateHook<Video_InitializeDevice>(detourVideo_InitializeDevice);
    

    nylon::hook::CreateHook<CreateHighwayDrawRect>(deoutCreateHighwayDrawRect);
    nylon::hook::CreateHook<Nx_DirectInput_InitMouse>(detourNx_DirectInput_InitMouse);
    nylon::hook::CreateHook<D3DDeviceLostFUN_0057ae20>(detourD3DDeviceLostFUN_0057ae20);
    nylon::hook::CreateHook<nylon::NodeArray_SetCFuncInfo>(detourNodeArray_SetCFuncInfo);
    nylon::hook::CreateHook<CRC_CreateKeyNameAssociation>(detour__CRC_CreateKeyNameAssociate);

    nylon::hook::CreateHook<ControllerUpdate>(detour__ControllerUpdate);
    nylon::hook::CreateHook<CRC_FindChecksumeName>(detour__CRC_FindChecksumeName);

    // nylon::hook::CreateHook<Time_UpdateTime>(detourTimeUpdateTime);

    // nylon::hook::CreateHook<CFuncWait>(detourCFuncWait);


    _CFuncManager = { };

    _CFuncManager.Register();

    Log.Info("Finished setting up default hooks.");
}
