﻿#include "StarlightPCH.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"
#include "Events/WindowEvents.h"
#include "Input/Input.h"
#include "Misc/CommandLineParser.h"
#include "Renderer/Renderer.h"

extern bool bIsApplicationRunning;

CApplication::CApplication(const CApplicationSpecification& Specification)
    : m_ApplicationSpecification(Specification), m_CommandLineArguments(Specification.CommandLineArguments)
{
    m_ApplicationInstance = this;

    CLogging::Initialize();

    ENGINE_LOG_INFO_TAG("Core", "Initializing Starlight Engine...");

    CRenderer::PreInitialize();

    FWindowSpecification ApplicationWindowSpecification;
    ApplicationWindowSpecification.Title = m_ApplicationSpecification.Name;
    ApplicationWindowSpecification.Width = m_ApplicationSpecification.WindowWidth;
    ApplicationWindowSpecification.Height = m_ApplicationSpecification.WindowHeight;
    ApplicationWindowSpecification.WindowMode = m_ApplicationSpecification.WindowMode;
    ApplicationWindowSpecification.bEnableVSync = m_ApplicationSpecification.bEnableVSync;
    ApplicationWindowSpecification.bEnableDecoration = m_ApplicationSpecification.bEnableWindowDecoration;
    ApplicationWindowSpecification.bEnableResizing = m_ApplicationSpecification.bEnableWindowResizing;

    /*-----------------------------------------------------*/
    /* -- Parsing window related command line arguments -- */
    /*-----------------------------------------------------*/

    if (CCommandLineParser::Param(m_CommandLineArguments, "windowed"))
        ApplicationWindowSpecification.WindowMode = EWindowMode::Windowed;
    
    if (CCommandLineParser::Param(m_CommandLineArguments, "windowedFullscreen"))
        ApplicationWindowSpecification.WindowMode = EWindowMode::WindowedFullscreen;
    
    if (CCommandLineParser::Param(m_CommandLineArguments, "fullscreen"))
        ApplicationWindowSpecification.WindowMode = EWindowMode::Fullscreen;

    if (ApplicationWindowSpecification.WindowMode == EWindowMode::Windowed || ApplicationWindowSpecification.WindowMode == EWindowMode::Fullscreen)
    {
        int32 CmdLineWindowWidth = 0;
        int32 CmdLineWindowHeight = 0;

        if (CCommandLineParser::Value(m_CommandLineArguments, "ResolutionX", &CmdLineWindowWidth))
        {
            if (CmdLineWindowWidth != 0)
                ApplicationWindowSpecification.Width = CmdLineWindowWidth;
        }

        if (CCommandLineParser::Value(m_CommandLineArguments, "ResolutionY", &CmdLineWindowHeight))
        {
            if (CmdLineWindowHeight != 0)
                ApplicationWindowSpecification.Height = CmdLineWindowHeight;
        }
    }
    
    m_ApplicationWindow = IWindow::Create(ApplicationWindowSpecification);
    m_ApplicationWindow->Initialize();
    m_ApplicationWindow->SetEventCallbackFunction([this](IEvent& Event) { return OnEvent(Event); });

    CInput::Initialize();
    CRenderer::Initialize();
    
    DispatchEvent<CApplicationInitializeEvent>();
}

CApplication::~CApplication()
{
    ENGINE_LOG_INFO_TAG("Core", "Shutting down...");

    DispatchEvent<CApplicationShutdownEvent>();
    
    m_ApplicationWindow->SetEventCallbackFunction([](IEvent&) {});

    for (ILayer* Layer : m_LayerManager.GetLayers())
    {
        Layer->OnDetach();
        delete Layer;
    }

    // Clearing the event queue.
    // This also ensures that we free the memory used by it.
    std::queue<std::function<void()>>().swap(m_EventQueue);

    CRenderer::Shutdown();
}

void CApplication::OnEvent(IEvent& Event)
{
    CEventDispatcher EventDispatcher(Event);
    EventDispatcher.Dispatch<CWindowCloseEvent>([this](CWindowCloseEvent&)
    {
        Close();

        return true;
    });
    
    for (const auto& Layer : m_LayerManager.GetLayers())
    {
        if (Event.bIsHandled)
            break;
        
        Layer->OnEvent(Event);
    }
}

void CApplication::Start()
{
    while (bIsRunning)
    {
        /*-----------------*/
        /* --  Updating -- */
        /*-----------------*/

        OnUpdate();

        for (ILayer* Layer : m_LayerManager.GetLayers())
            Layer->OnUpdate();

        ProcessEvents();

        DispatchEvent<CApplicationUpdateEvent>();

        /*-----------------*/
        /* -- Rendering -- */
        /*-----------------*/
        
        OnPreRender();

        for (ILayer* Layer : m_LayerManager.GetLayers())
            Layer->OnPreRender();

        CRenderer::BeginFrame();

        OnRender();

        for (ILayer* Layer : m_LayerManager.GetLayers())
            Layer->OnRender();

        DispatchEvent<CApplicationRenderEvent>();

        CRenderer::EndFrame();

        OnPostRender();

        for (ILayer* Layer : m_LayerManager.GetLayers())
            Layer->OnPostRender();

        m_ApplicationWindow->SwapBuffers();

        /*---------------*/
        /* -- Ticking -- */
        /*---------------*/

        OnTick();

        for (ILayer* Layer : m_LayerManager.GetLayers())
            Layer->OnTick();

        DispatchEvent<CApplicationTickEvent>();
    }
}

void CApplication::Restart()
{
    bIsRunning = false;
}

void CApplication::Close()
{
    bIsRunning = false;
    bIsApplicationRunning = false;
}

template <typename Event, typename ... EventArgs>
void CApplication::DispatchEvent(EventArgs&&... Arguments)
{
    static_assert(std::is_assignable_v<IEvent, Event>);

    std::shared_ptr<Event> EventInstance = std::make_shared<Event>(std::forward<EventArgs>(Arguments)...);
    OnEvent(*EventInstance);
}

template <typename EventFunction>
void CApplication::QueueEvent(EventFunction&& EventFunc)
{
    std::scoped_lock EventQueueMutexLock(m_EventQueueMutex);
    
    m_EventQueue.push(EventFunc);
}

void CApplication::PushLayer(ILayer* Layer)
{
    m_LayerManager.PushLayer(Layer);
}

void CApplication::PushOverlay(ILayer* Overlay)
{
    m_LayerManager.PushOverlay(Overlay);
}

void CApplication::PopLayer(ILayer* Layer)
{
    m_LayerManager.PopLayer(Layer);
}

void CApplication::PopOverlay(ILayer* Overlay)
{
    m_LayerManager.PopOverlay(Overlay);
}

void CApplication::ProcessEvents()
{
    CInput::TransitionPressedKeys();
    CInput::TransitionPressedMouseButtons();
    
    m_ApplicationWindow->ProcessEvents();
    
    std::scoped_lock EventQueueMutexLock(m_EventQueueMutex);

    while (!m_EventQueue.empty())
    {
        auto& EventFunction = m_EventQueue.front();
        EventFunction();

        m_EventQueue.pop();
    }
}
