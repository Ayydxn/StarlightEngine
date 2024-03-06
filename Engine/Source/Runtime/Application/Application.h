#pragma once

#include "Window.h"
#include "Core/Misc/CommandLineArguments.h"
#include "Events/Event.h"

#include <mutex>
#include <queue>
#include <string>

struct CApplicationSpecification
{
    std::string Name = "Starlight Engine";
    uint32 WindowWidth = 1600;
    uint32 WindowHeight = 900;
    EWindowMode WindowMode = EWindowMode::Windowed;
    bool bEnableVSync = true;
    bool bEnableWindowDecoration = true;
    bool bEnableWindowResizing = true;
    
    CCommandLineArguments CommandLineArguments;
};

class CApplication
{
    using EventCallbackFunction = std::function<void(IEvent&)>;
public:
    CApplication(const CApplicationSpecification& Specification = CApplicationSpecification());
    virtual ~CApplication();

    virtual void OnEvent(IEvent& Event);

    void Start();
    void Restart();
    void Close();

    template<typename Event, typename ... EventArgs>
    void DispatchEvent(EventArgs&& ... Arguments);

    template<typename EventFunction>
    void QueueEvent(EventFunction&& EventFunc);
    
    static CApplication& GetInstance() { return *m_ApplicationInstance; }

    const CApplicationSpecification& GetSpecification() const { return m_ApplicationSpecification; }

    const CCommandLineArguments& GetCommandLineArguments() const { return m_CommandLineArguments; }
private:
    void ProcessEvents();
private:
    inline static CApplication* m_ApplicationInstance = nullptr;

    std::shared_ptr<IWindow> m_ApplicationWindow = nullptr;
    
    CApplicationSpecification m_ApplicationSpecification;
    CCommandLineArguments m_CommandLineArguments;

    std::mutex m_EventQueueMutex;
    std::queue<std::function<void()>> m_EventQueue;
    
    bool bIsRunning = true;
};

CApplication* CreateApplication(char** Arguments, int32 ArgumentCount);