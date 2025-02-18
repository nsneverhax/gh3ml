#include "../Main.hpp"
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

namespace cfg = nylon::Config;
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
        *debugFullScreen = 0;
        break;
    case cfg::WindowStyle::Windowed:
        *debugFullScreen = 1;
        style = WS_TILEDWINDOW;
        break;
    case cfg::WindowStyle::BorderlessWindowed:
        *debugFullScreen = 1;
        style = WS_POPUP;
        break;
    case cfg::WindowStyle::BorderlessFullscreen:
        *debugFullScreen = 1;
        style = WS_POPUP;
        break;
    default:
        break;
    }
    WindowHandle = nylon::hook::Orig<1, nylon::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, WS_TILEDWINDOW, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);


    return WindowHandle;
}

using Video_InitializeDevice = nylon::hook::Binding<0x0057b940, nylon::hook::cconv::CDecl, void, void*>;

void detourVideo_InitializeDevice(void* engineParams)
{
    if (nylon::Config::UnlockFPS())
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

    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(WindowHandle);
    ImGui_ImplDX9_Init(*gh3::Direct3DDevice);


    nylon::internal::Log.Info("Hooking DirectX 9...");
    nylon::internal::CreateDirectXHooks();
    nylon::internal::Log.Info("Finished hooking DirectX 9.");
}

using WindowProc = nylon::hook::Binding<0x00578880, nylon::hook::cconv::STDCall, LRESULT, HWND, UINT, WPARAM, LPARAM>;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT detourWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool waitForTabRelease = false;


    auto ret = WindowProc::Orig(hWnd, uMsg, wParam, lParam);


    //(*gh3::MouseDevice)->Unacquire();

    /*
    (*gh3::MouseDevice)->SetCooperativeLevel(WindowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    (*gh3::KeyboardDevice)->SetCooperativeLevel(WindowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    */
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (LOWORD(wParam))
        {
        case VK_OEM_3:

            if (!waitForTabRelease)
                nylon::imgui::NylonMenuActive = !nylon::imgui::NylonMenuActive;

            waitForTabRelease = true;
            break;
        default:
            break;
        }
        break;
    case WM_KEYUP:
        switch (LOWORD(wParam))
        {
        case VK_OEM_3:
            waitForTabRelease = false;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }


    return ret;
}



#pragma endregion


using func_SetNewWhammyValue = nylon::hook::Binding<0x0041de60, nylon::hook::cconv::CDecl, bool, GH3::QbStruct*>;
bool detourSetNewWhammyValue(GH3::QbStruct* self)
{
    return SetNewWhammyValue(self);
    //return func_SetNewWhammyValue::Orig(self);
}


using CreateHighwayDrawRect = nylon::hook::Binding<0x00601d30, nylon::hook::cconv::CDecl, int, double*, float, float, float, float, float, float, float, float, float, float>;

int deoutCreateHighwayDrawRect(double * array, float param_2, float param_3, float whammyTopWidth, float param_5, float whammyWidthOffset , float param_7, float param_8, float param_9, float param_10, float param_11)
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
    
    float whammySizeMultiplier = ((float)backBufferWidth / 1280.0f) * 1.25f;
    return CreateHighwayDrawRect::Orig(
        array, 
        param_2 * whammyMultipliers[1],
        param_3 * whammyMultipliers[2],
        whammyTopWidth * whammySizeMultiplier, 
        param_5 * whammyMultipliers[3],
        whammyWidthOffset * whammySizeMultiplier,
        param_7 * whammySizeMultiplier, 
        param_8 * whammyMultipliers[5],
        param_9 * whammyMultipliers[6],
        param_10 * whammyMultipliers[7], // Whammy Tail End
        param_11 * whammyMultipliers[8] // Whammy Tail Begin
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

void nylon::internal::SetupDefaultHooks()
{
    Log.Info("Setting up default hooks...");

    if (nylon::Config::UnlockFPS())
    {
        // Vultu: I really don't feel like rewriting the entire function for right now
        // so I'm going NOP where some global variables are set
        uint8_t buffer[6];
        memset(buffer, INST_NOP, sizeof(buffer));

        nylon::WriteMemory(FUNC_INITIALIZEDEVICE + 0x1C7, buffer, sizeof(buffer)); // 0x0057BB07 : dword ptr [D3DPresentParams.SwapEffect],EDI
        nylon::WriteMemory(FUNC_INITIALIZEDEVICE + 0x239, buffer, sizeof(buffer)); // 0x0057bb79 : dword ptr [D3DPresentParams.PresentationInterval],EDI
    }
    

    nylon::hook::CreateHook<1, nylon::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA")),
        detourCreateWindowExA
    );

    nylon::internal::CreateCFuncHooks();

    nylon::hook::CreateHook<DebugLog>(detourDebugLog);
    nylon::hook::CreateHook<Video_InitializeDevice>(detourVideo_InitializeDevice);
    
    nylon::hook::CreateHook<WindowProc>(detourWindowProc);

    nylon::hook::CreateHook<CreateHighwayDrawRect>(deoutCreateHighwayDrawRect);
    nylon::hook::CreateHook<Nx_DirectInput_InitMouse>(detourNx_DirectInput_InitMouse);
    nylon::hook::CreateHook<D3DDeviceLostFUN_0057ae20>(detourD3DDeviceLostFUN_0057ae20);
    nylon::hook::CreateHook<nylon::NodeArray_SetCFuncInfo>(detourNodeArray_SetCFuncInfo);
    nylon::hook::CreateHook<CRC_CreateKeyNameAssociation>(detour__CRC_CreateKeyNameAssociate);

    // nylon::hook::CreateHook<Time_UpdateTime>(detourTimeUpdateTime);

    // nylon::hook::CreateHook<CFuncWait>(detourCFuncWait);


    _CFuncManager = { };

    _CFuncManager.Register();

    Log.Info("Finished setting up default hooks.");
}
