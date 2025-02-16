#include <Windows.h>

#include <string>
#include <array>
#include <vector>
#include <filesystem>

// Vultu: We are going to provide the needed imports for GH3 from d3d9.dll since we are replacing it
// We are going to manually specify WINAPI (__stdcall) calling convention and then manually parse the decorated names
// into non-decorated ones. This is probably a bad idea, but it will work for now.


constexpr static auto MAX_PATH_CHARS = 32768u;
static HMODULE getWINMM() 
{
    static auto xinput = []() -> HMODULE
        {
            std::wstring path(MAX_PATH_CHARS, L'\0');

            auto size = GetSystemDirectoryW(path.data(), path.size());
            if (size)
            {
                path.resize(size);
                return LoadLibraryW((path + L"\\d3d9.dll").c_str());
            }
            return NULL;
        }();

    return xinput;
}

static FARPROC getFP(const std::string& sym) 
{
    if (auto module = getWINMM())
        return GetProcAddress(module, sym.c_str());

    return NULL;
}

#pragma comment(linker, "/export:Direct3DCreate9@@YGPAXI@Z=Direct3DCreate9")
void* WINAPI Direct3DCreate9(UINT SDKVersion)
{
    static auto fp = getFP("Direct3DCreate9");
    if (fp)
    {
        using FPType = decltype(&Direct3DCreate9);
        return reinterpret_cast<FPType>(fp)(SDKVersion);
    }

    return NULL;
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
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

            //Copy the error message into a std::string.

            message = "An error occured when loading Nylon, the error details are as follows:\n";
            message.append(messageBuffer, size);

          
            MessageBox(NULL, message.c_str(), "Unable to load \"nylon.dll\"", MB_OK);
            // CreateThread(NULL, 0, &errorThread, param, 0, NULL);

            //Free the Win32's string's buffer.
            LocalFree(messageBuffer);
        }
    }
    

    return TRUE;
}
