#include <Windows.h>

#include <string>
#include <array>
#include <vector>
#include <filesystem>

// Vultu: We are going to provide the needed imports for GH3 from xinput3_1.dll since we are replacing it
// We are going to manually specify WINAPI (__stdcall) calling convention and then manually parse the decorated names
// into non-decorated ones. This is probably a bad idea, but it will work for now.

struct XINPUT_STATE;
struct XINPUT_CAPABILITIES;
struct XINPUT_VIBRATION;

struct IP_ADAPTER_INFO;
typedef IP_ADAPTER_INFO* PIP_ADAPTER_INFO;

constexpr static auto MAX_PATH_CHARS = 32768u;
static HMODULE getXInput() 
{
    static auto xinput = []() -> HMODULE
        {
            std::wstring path(MAX_PATH_CHARS, L'\0');

            // Vultu: Some people have special xinput1_3.dll for their guitars.. apparently
            // We are already modding the game might as well give them support for it.
            if (std::filesystem::exists("nylon\\xinput1_3.dll"))
            {
                return LoadLibraryW(L"nylon\\xinput1_3.dll");
            }

            auto size = GetSystemDirectoryW(path.data(), path.size());
            if (size)
            {
                path.resize(size);
                return LoadLibraryW((path + L"\\xinput1_3.dll").c_str());
            }
            return NULL;
        }();

    return xinput;
}
static HMODULE getIPHLPAPI()
{
    static auto iphlpapi = []() -> HMODULE
        {
            std::wstring path(MAX_PATH_CHARS, L'\0');

            auto size = GetSystemDirectoryW(path.data(), path.size());
            if (size)
            {
                path.resize(size);
                return LoadLibraryW((path + L"\\IPHLPAPI.DLL").c_str());
            }
            return NULL;
        }();

    return iphlpapi;
}

static FARPROC getFPIPHLPAPI(const std::string& sym)
{
    if (auto module = getIPHLPAPI())
        return GetProcAddress(module, sym.c_str());

    return NULL;
}
static FARPROC getFPXInput(const std::string& sym)
{
    if (auto module = getXInput())
        return GetProcAddress(module, sym.c_str());

    return NULL;
}

#pragma comment(linker, "/export:GetAdaptersInfo@@YGKPAUIP_ADAPTER_INFO@@PAK@Z=GetAdaptersInfo")
DWORD WINAPI GetAdaptersInfo(_Out_writes_bytes_opt_(*SizePointer) PIP_ADAPTER_INFO AdapterInfo, _Inout_ PULONG SizePointer)
{
    static auto fp = getFPIPHLPAPI("GetAdaptersInfo");
    if (fp)
    {
        using FPType = decltype(&GetAdaptersInfo);
        return reinterpret_cast<FPType>(fp)(AdapterInfo, SizePointer);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

// extern "C" __declspec(dllexport) GetAdaptersInfo()

#pragma comment(linker, "/export:XInputGetState@@YGKKPAUXINPUT_STATE@@@Z=XInputGetState,@2")
DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    static auto fp = getFPXInput("XInputGetState");
    if (fp)
    {
        using FPType = decltype(&XInputGetState);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, pState);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputSetState@@YGKKPAUXINPUT_VIBRATION@@@Z=XInputSetState,@3")
DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
    static auto fp = getFPXInput("XInputSetState");
    if (fp)
    {
        using FPType = decltype(&XInputSetState);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, pVibration);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputGetCapabilities@@YGKKKPAUXINPUT_CAPABILITIES@@@Z=XInputGetCapabilities,@4")
DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
    static auto fp = getFPXInput("XInputGetCapabilities");
    if (fp)
    {
        using FPType = decltype(&XInputGetCapabilities);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, dwFlags, pCapabilities);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputEnable@@YGXH@Z=XInputEnable,@5")
void WINAPI XInputEnable(BOOL enable)
{
    static auto fp = getFPXInput("XInputEnable");
    if (fp)
    {
        using FPType = decltype(&XInputEnable);
        reinterpret_cast<FPType>(fp)(enable);
    }

    return;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    std::string message = { };

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        
        std::wstring path = (std::filesystem::current_path() / L"nylon.dll").wstring();

        if (!std::filesystem::exists(path))
        {
            MessageBox(NULL, "Unable to find nylon.dll", "Unable to load \"nylon.dll\"", MB_OK);
            return FALSE;
        }

        // This is UB. -- Vultu: Too bad!
        if (LoadLibraryW(path.c_str()) == NULL)
        {
            DWORD errorMessageID = GetLastError();
            LPSTR messageBuffer = nullptr;
            //Ask Win32 to give us the string version of that message ID.
            //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
            size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

            //Copy the error message into a std::string.

            message = std::format("An error occured when loading Nylon, ErrorCode: {:#8X} the error details are as follows:\n", errorMessageID);
            message.append(messageBuffer, size);

          
            MessageBox(NULL, message.c_str(), "Unable to load \"nylon.dll\"", MB_OK);
            // CreateThread(NULL, 0, &errorThread, param, 0, NULL);

            //Free the Win32's string's buffer.
            LocalFree(messageBuffer);
        }
    }
    

    return TRUE;
}
