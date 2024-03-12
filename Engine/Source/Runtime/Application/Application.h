#pragma once

#include "Window.h"
#include "Core/Misc/CommandLineArguments.h"
#include "Events/Event.h"
#include "Layers/LayerManager.h"

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

    virtual void OnInitialize() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(IEvent& Event);
    virtual void OnPreRender() {}
    virtual void OnRender() {}
    virtual void OnPostRender() {}
    virtual void OnTick() {}
    virtual void OnShutdown() {}

    void Start();
    void Restart();
    void Close();

    template<typename Event, typename ... EventArgs>
    void DispatchEvent(EventArgs&& ... Arguments);

    template<typename EventFunction>
    void QueueEvent(EventFunction&& EventFunc);

    void PushLayer(ILayer* Layer);
    void PushOverlay(ILayer* Overlay);
    void PopLayer(ILayer* Layer);
    void PopOverlay(ILayer* Overlay);
    
    static CApplication& GetInstance() { return *m_ApplicationInstance; }

    const IWindow& GetWindow() const { return *m_ApplicationWindow; }

    const CApplicationSpecification& GetSpecification() const { return m_ApplicationSpecification; }

    const CCommandLineArguments& GetCommandLineArguments() const { return m_CommandLineArguments; }
private:
    void ProcessEvents();
private:
    inline static CApplication* m_ApplicationInstance = nullptr;

    std::unique_ptr<IWindow> m_ApplicationWindow = nullptr;
    
    CApplicationSpecification m_ApplicationSpecification;
    CCommandLineArguments m_CommandLineArguments;
    CLayerManager m_LayerManager;

    std::mutex m_EventQueueMutex;
    std::queue<std::function<void()>> m_EventQueue;
    
    bool bIsRunning = true;
};

CApplication* CreateApplication(char** Arguments, int32 ArgumentCount);