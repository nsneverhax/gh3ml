#include "Main.hpp"
#include <GH3ML/Hook.hpp>
#include <d3d9.h>
#include <GH3ML/Core.hpp>

constexpr int INST_NOP = 0x90;

constexpr int FUNC_INITIALIZEDEVICE = 0x0057B940;

#pragma region Default Hooks
using DebugLog = gh3ml::hook::Binding<0x00472b50, gh3ml::hook::cconv::CDecl, void, char*, va_list>;

void detourDebugLog(char* fmt, va_list args)
{
    gh3ml::internal::LogGH3.Info(fmt, args);

    DebugLog::Orig(fmt, args);
}



HWND detourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    return gh3ml::hook::Orig<1, gh3ml::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, WS_POPUP, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

using Video_InitializeDevice = gh3ml::hook::Binding<0x0057b940, gh3ml::hook::cconv::CDecl, void, void*>;

void detourVideo_InitializeDevice(void* engineParams)
{
    // Vultu: We need to set the values we NOP'd out before
    union
    {
        uint8_t bytes[sizeof(uint32_t)];
        uint32_t value;
    } uint32_u;

    uint32_u.value = 0x01;

    gh3ml::WriteMemory(0x00c5b918, uint32_u.bytes, sizeof(uint32_t));

    uint32_u.value = D3DPRESENT_INTERVAL_IMMEDIATE;

    gh3ml::WriteMemory(0x00c5b934, uint32_u.bytes, sizeof(uint32_t));

    Video_InitializeDevice::Orig(engineParams);
}

using WindowProc = gh3ml::hook::Binding<0x00578880, gh3ml::hook::cconv::STDCall, LRESULT, HWND, UINT, WPARAM, LPARAM>;

LRESULT detourWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = WindowProc::Orig(hWnd, uMsg, wParam, lParam);
    if ((uMsg == WM_SETCURSOR) && ((short)lParam == HTCLIENT))
    {
        if (GetCursor() == nullptr)
        {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            ShowCursor(TRUE);
        }
        //ShowCursor(TRUE);
        return 1;
    }

    return result;
}

struct QbStruct
{
    uint16_t member0;
    uint8_t member1;
    uint8_t member2;
    void* first;

    using InsertCStringItem = gh3ml::hook::Binding<0x00479ac0, gh3ml::hook::cconv::ThisCall, void, QbStruct*, uint32_t, const char*>;
    using InsertQbKeyItem = gh3ml::hook::Binding<0x00479c80, gh3ml::hook::cconv::ThisCall, void, QbStruct*, uint32_t, uint32_t>;
};

using LoadPak = gh3ml::hook::Binding<0x004a1780, gh3ml::hook::cconv::CDecl, bool, QbStruct*>;

int loadPakCount = 0;

std::unordered_map<uint32_t, std::string> keyMap = { };

bool detourLoadPak(QbStruct* qbStruct)
{
    auto ret = LoadPak::Orig(qbStruct);
    if (loadPakCount == 1)
    {

        loadPakCount++;

        // if (std::filesystem::exists("./gh3ml/Mods/GH3Deluxe/pak/gh3dx.pak"))
         //{
        QbStruct deluxeStruct = QbStruct();
        QbStruct::InsertCStringItem(&deluxeStruct, 0, "../gh3ml/Mods/GH3Deluxe/pak/gh3dx.pak");
        //LoadPak::Orig(&deluxeStruct);
    //}
    }
    else
        loadPakCount++;
    return ret;
}

using CFuncPrintF = gh3ml::hook::Binding<0x00530940, gh3ml::hook::cconv::CDecl, bool, void*>;
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

    gh3ml::internal::LogGH3.Info(buffer);
    //return gh3ml::hook::Orig<0x00530940, gh3ml::hook::cconv::CDecl, bool, char*>(param1);
    return true;
}

#pragma endregion


void gh3ml::internal::SetupDefaultHooks()
{
    Log.Info("Setting up default hooks...");

    // Vultu: I really don't feel like rewriting the entire function for right now
    // so I'm going NOP where some global variables are setr
    uint8_t buffer[6];
    memset(buffer, INST_NOP, sizeof(buffer));

    gh3ml::WriteMemory(FUNC_INITIALIZEDEVICE + 0x1C7, buffer, sizeof(buffer)); // 0x0057BB07 : dword ptr [D3DPresentParams.SwapEffect],EDI
    gh3ml::WriteMemory(FUNC_INITIALIZEDEVICE + 0x239, buffer, sizeof(buffer)); // 0x0057bb79 : dword ptr [D3DPresentParams.PresentationInterval],EDI

    gh3ml::hook::CreateHook<1, gh3ml::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA")),
        detourCreateWindowExA
    );

    gh3ml::hook::CreateHook<DebugLog>(detourDebugLog);
    gh3ml::hook::CreateHook<Video_InitializeDevice>(detourVideo_InitializeDevice);

    gh3ml::hook::CreateHook<WindowProc>(detourWindowProc);

    // gh3ml::hook::CreateHook<LoadPak>(detourLoadPak);
    gh3ml::hook::CreateHook<CFuncPrintF>(detourCFuncPrintF);


    Log.Info("Finished setting up default hooks.");
}