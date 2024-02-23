#pragma once

#include "Application.h"

extern CApplication* CreateApplication(char** Arguments, int32 ArgumentCount);

inline bool bIsApplicationRunning = true;

inline int32 StarlightMain(char** Arguments, int32 ArgumentCount)
{
    // We encapsulate the application in a double while loop (this one and the one present in CApplication::Start so that restarting programatically is possible. 
    while (bIsApplicationRunning)
    {
        CApplication* Application = CreateApplication(Arguments, ArgumentCount);
        Application->Start();
        delete Application;
    }

    return 0;
}

#ifdef STARLIGHT_PLATFORM_WIN64

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, PSTR lpCommandLine, int nCommandShow)
{
    return StarlightMain(__argv, __argc);
}

#else

int main(int ArgumentCount, char** Arguments)
{
    return StarlightMain(Arguments, ArgumentCount);
}
    
#endif