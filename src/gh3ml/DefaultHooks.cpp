#include "Main.hpp"
#include <GH3ML/Hook.hpp>
#include <d3d9.h>
#include <GH3ML/Core.hpp>
#include <filesystem>
#include <GH3ML/Config.hpp>

#include <iostream>

#include <dinput.h>

#include <GH3/CFunc.hpp>

#include <GH3/Addresses.hpp>

constexpr int INST_NOP = 0x90;

constexpr int FUNC_INITIALIZEDEVICE = 0x0057B940;

extern float* DeltaTime = reinterpret_cast<float*>(0x009596bc);

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
      
        return 1;
    }

    return result;
}

using LoadPak = gh3ml::hook::Binding<0x004a1780, gh3ml::hook::cconv::CDecl, bool, QbStruct*>;

int loadPakCount = 0;

std::unordered_map<uint32_t, std::string> keyMap = { };


using FUN_004788b0 = gh3ml::hook::Binding<0x004788b0, gh3ml::hook::cconv::ThisCall, bool, QbStruct*, uint32_t, void*, uint32_t>;

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

        for (const auto pair : gh3ml::internal::LoadedMods)
        {

            auto expectedPakPath = pair.second.GetDirectory() + "\\pak\\" + pair.first + ".pak";

            gh3ml::internal::LogGH3.Info("Expecting: \"%s\"", expectedPakPath.c_str());

            if (!std::filesystem::exists(gh3ml::GetModsDirectory() + expectedPakPath + ".xen"))
            {
                gh3ml::internal::LogGH3.Info("Unable to find pak file.");
                continue;
            }

            expectedPakPath.insert(0, "..\\gh3ml\\Mods\\");

            gh3ml::internal::LogGH3.Info("Found it! Loading...");
            QbStruct modPakStruct = QbStruct();

            Functions::InsertCStringItem(&modPakStruct, 0, expectedPakPath.data());

            LoadPak::Orig(&modPakStruct);
            gh3ml::internal::LogGH3.Info("Done!");
        }

        _doPakCheck = false;
    }

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

using HashTableGetInt = gh3ml::hook::Binding<0x004a5960, gh3ml::hook::cconv::CDecl, uint32_t, uint32_t>;

using  Wait_GameFrames = gh3ml::hook::Binding<0x00493020, gh3ml::hook::cconv::ThisCall, void, void*, float>;
void detourWaitGameFrames(void* self, float wait)
{

    // Vultu: Waittime is hardcoded to "wait * (1/60)" so we need to remove that
    float newWait = wait / (16.666666f);

    // Vultu: Use a union to get the Deltatime var from memory
    union
    {
        uint8_t bytes[sizeof(float)];
        float value;
    } float_u;

    float_u.value = 0;

    gh3ml::ReadMemory(0x009596bc, float_u.bytes, sizeof(float));

    if (float_u.value != 0)
        newWait *= (float_u.value * 1000);
    else
        newWait = wait;

    //if (wait != 0)
    //    gh3ml::internal::LogGH3.Info("WaitFrames: D: %f - %f - %X", float_u.value, newWait, wait);

    Wait_GameFrames::Orig(self, wait);
}

using func_SetNewWhammyValue = gh3ml::hook::Binding<0x0041de60, gh3ml::hook::cconv::CDecl, bool, QbStruct*>;
bool detourSetNewWhammyValue(QbStruct* self)
{
    return SetNewWhammyValue(self);
    //return func_SetNewWhammyValue::Orig(self);
}


using CreateHighwayDrawRect = gh3ml::hook::Binding<0x00601d30, gh3ml::hook::cconv::CDecl, int, double*, float, float, float, float, float, float, float, float, float, float>;

int deoutCreateHighwayDrawRect(double * array, float param_2, float param_3, float whammyTopWidth, float param_5, float whammyWidthOffset , float param_7, float param_8, float param_9, float param_10, float param_11)
{
    //std::cout
    //    << " param_2: " << param_2
    //    << " param_3: " << param_3
    //    << " whammyTopWidth: " << whammyTopWidth
    //    << " param_5: " << param_3
    //    << " whammyWidthOffset: " 
    //    << whammyWidthOffset 
    //    << " param_7: " << param_7
    //    << " param_8: " << param_8
    //    << " param_9: " << param_9
    //    << " param_10: " << param_10
    //    << " param_11: " << param_11
    //    << std::endl;
    //    
    float delta = (*DeltaTime * 60);

    return CreateHighwayDrawRect::Orig(array, param_2, param_3, whammyTopWidth, param_5, whammyWidthOffset, param_7 * (1080.0f / 720.0f) * 1.25f, param_8, param_9, param_10, param_11);
}


void gh3ml::internal::SetupDefaultHooks()
{
    Log.Info("Setting up default hooks...");

    if (gh3ml::Config::UnlockFPS())
    {
        // Vultu: I really don't feel like rewriting the entire function for right now
        // so I'm going NOP where some global variables are setr
        uint8_t buffer[6];
        memset(buffer, INST_NOP, sizeof(buffer));

        gh3ml::WriteMemory(FUNC_INITIALIZEDEVICE + 0x1C7, buffer, sizeof(buffer)); // 0x0057BB07 : dword ptr [D3DPresentParams.SwapEffect],EDI
        gh3ml::WriteMemory(FUNC_INITIALIZEDEVICE + 0x239, buffer, sizeof(buffer)); // 0x0057bb79 : dword ptr [D3DPresentParams.PresentationInterval],EDI
    }

    gh3ml::hook::CreateHook<1, gh3ml::hook::cconv::STDCall>(
        reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA")),
        detourCreateWindowExA
    );


    gh3ml::hook::CreateHook<DebugLog>(detourDebugLog);
    gh3ml::hook::CreateHook<Video_InitializeDevice>(detourVideo_InitializeDevice);

    if (gh3ml::Config::OverrideWindProc())
        gh3ml::hook::CreateHook<WindowProc>(detourWindowProc);

    gh3ml::hook::CreateHook<LoadPak>(detourLoadPak);
    gh3ml::hook::CreateHook<CFuncPrintF>(detourCFuncPrintF);

    //gh3ml::hook::CreateHook<Wait_GameFrames>(detourWaitGameFrames);

    // gh3ml::hook::CreateHook<func_SetNewWhammyValue>(detourSetNewWhammyValue);
    gh3ml::hook::CreateHook<CreateHighwayDrawRect>(deoutCreateHighwayDrawRect);

    // Log.Info("Finished setting up default hooks.");
}