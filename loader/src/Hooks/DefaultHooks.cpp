#include "../Main.hpp"
#include "../Imgui/Imgui.hpp"
#include "DirectXHooks.hpp"
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
#include <GH3/CRC32.hpp>
constexpr int INST_NOP = 0x90;

constexpr int FUNC_INITIALIZEDEVICE = 0x0057B940;

extern float* DeltaTime = reinterpret_cast<float*>(0x009596bc);

// TEMP
nylon::CFuncManager _CFuncManager;

#pragma region Default Hooks
using DebugLog = nylon::hook::Binding<0x00472b50, nylon::hook::cconv::CDecl, void, char*, va_list>;

void detourDebugLog(char* fmt, va_list args)
{
    nylon::internal::LogGH3.Info(fmt, args);

    DebugLog::Orig(fmt, args);
}


HWND WindowHandle = nullptr;

HWND detourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    WindowHandle = nylon::hook::Orig<1, nylon::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, WS_POPUP, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);


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


    (*gh3::MouseDevice)->SetCooperativeLevel(WindowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    (*gh3::KeyboardDevice)->SetCooperativeLevel(WindowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_KEYDOWN:
        switch (LOWORD(wParam))
        {
        case VK_TAB:

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
        case VK_TAB:
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

using LoadPak = nylon::hook::Binding<0x004a1780, nylon::hook::cconv::CDecl, bool, QbStruct*>;

int loadPakCount = 0;

std::unordered_map<uint32_t, std::string> keyMap = { };


using FUN_004788b0 = nylon::hook::Binding<0x004788b0, nylon::hook::cconv::ThisCall, bool, QbStruct*, uint32_t, void*, uint32_t>;

bool detourLoadPak(QbStruct* qbStruct)
{
    static bool _doPakCheck = true;

    auto ret = LoadPak::Orig(qbStruct);

    if (!_doPakCheck)
        return ret;

    char* pakNameBuffer[128];
    memset(pakNameBuffer, 0, 128);

    FUN_004788b0(qbStruct, 0, pakNameBuffer, 0);

    if (strcmp("pak/qb.pak", pakNameBuffer[0]) == 0)
    {

        for (const auto pair : nylon::internal::LoadedMods)
        {

            auto expectedPakPath = pair.second.GetDirectory() + "\\pak\\" + pair.first + ".pak";

            nylon::internal::LogGH3.Info("Expecting: \"%s\"", expectedPakPath.c_str());

            if (!std::filesystem::exists(nylon::ModsDirectory() + expectedPakPath + ".xen"))
            {
                nylon::internal::LogGH3.Info("Unable to find pak file.");
                continue;
            }

            expectedPakPath.insert(0, "..\\nylon\\Mods\\");

            nylon::internal::LogGH3.Info("Found it! Loading...");
            QbStruct modPakStruct = QbStruct();

            Functions::InsertCStringItem(&modPakStruct, 0, expectedPakPath.data());

            LoadPak::Orig(&modPakStruct);
            nylon::internal::LogGH3.Info("Done!");
        }

        _doPakCheck = false;
    }

    return ret;
}

using CFuncPrintF = nylon::hook::Binding<0x00530940, nylon::hook::cconv::CDecl, bool, void*>;
bool detourCFuncPrintF(void* param1)
{

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    reinterpret_cast<void(*)(char*, size_t, void*)>(0x00532a80)(buffer, 1023, param1);


    // Replace linebreaks becuase we take care of them ourself
    for (auto i = 0; i < 1024; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = ' ';
        }
        if (buffer[i] == '\0')
            break;
    }

    nylon::internal::LogGH3.Info(buffer);
    //return nylon::hook::Orig<0x00530940, nylon::hook::cconv::CDecl, bool, char*>(param1);
    return true;
}

#pragma endregion


using func_SetNewWhammyValue = nylon::hook::Binding<0x0041de60, nylon::hook::cconv::CDecl, bool, QbStruct*>;
bool detourSetNewWhammyValue(QbStruct* self)
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
        auto instance = (gh3::EngineParams::Instance());
        IDirect3DSurface9* pSurface;
        (*gh3::Direct3DDevice)->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
        D3DSURFACE_DESC SurfaceDesc;
        pSurface->GetDesc(&SurfaceDesc);
        backBufferWidth = SurfaceDesc.Width;
        pSurface->Release();
    }

    float whammySizeMultiplier = ((float)backBufferWidth / 1280.0f) * 1.25f;
    return CreateHighwayDrawRect::Orig(array, param_2, param_3, whammyTopWidth * whammySizeMultiplier, param_5, whammyWidthOffset, param_7 * whammySizeMultiplier, param_8, param_9, param_10, param_11);
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

using CFuncWait = nylon::hook::Binding<0x0052eaf0, nylon::hook::cconv::CDecl, bool, QbStruct*, void*>;

bool detourCFuncWait(QbStruct* params, void* script)
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

    nylon::hook::CreateHook<DebugLog>(detourDebugLog);
    nylon::hook::CreateHook<Video_InitializeDevice>(detourVideo_InitializeDevice);
    
    nylon::hook::CreateHook<WindowProc>(detourWindowProc);

    nylon::hook::CreateHook<LoadPak>(detourLoadPak);
    nylon::hook::CreateHook<CFuncPrintF>(detourCFuncPrintF);

    nylon::hook::CreateHook<CreateHighwayDrawRect>(deoutCreateHighwayDrawRect);
    nylon::hook::CreateHook<Nx_DirectInput_InitMouse>(detourNx_DirectInput_InitMouse);
    nylon::hook::CreateHook<D3DDeviceLostFUN_0057ae20>(detourD3DDeviceLostFUN_0057ae20);
    nylon::hook::CreateHook<nylon::NodeArray_SetCFuncInfo>(detourNodeArray_SetCFuncInfo);

    nylon::hook::CreateHook<CFuncWait>(detourCFuncWait);

    _CFuncManager = { };

    _CFuncManager.Register();

    Log.Info("Finished setting up default hooks.");
}
