#include "CFuncHooks.hpp"

#include <Nylon/Config.hpp>

bool PrintStruct(gh3::QbStruct* params, gh3::QbScript* script)
{
	return true;
}

bool PrintF(gh3::QbStruct* params, gh3::QbScript* script)
{
    if (!nylon::Config::AllowQScriptPrintf())
        return true;

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    reinterpret_cast<void(*)(char*, size_t, void*)>(0x00532a80)(buffer, 1023, params);


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
    return true;
}


void nylon::internal::CreateCFuncHooks()
{
	hook::CreateHook<binding::CFunc_PrintStruct>(PrintStruct);
    hook::CreateHook<binding::CFunc_PrintF>(PrintF);
}