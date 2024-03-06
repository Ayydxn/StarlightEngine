#include "StarlightPCH.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"
#include "Misc/CommandLineParser.h"
#include "Events/WindowEvents.h"

extern bool bIsApplicationRunning;

CApplication::CApplication(const CApplicationSpecification& Specification)
    : m_ApplicationSpecification(Specification), m_CommandLineArguments(Specification.CommandLineArguments)
{
    m_ApplicationInstance = this;

    CLogging::Initialize();

    ENGINE_LOG_INFO_TAG("Core", "Initializing Starlight Engine...");

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

    DispatchEvent<CApplicationInitializeEvent>();
}

CApplication::~CApplication()
{
    ENGINE_LOG_INFO_TAG("Core", "Shutting down...");

    m_ApplicationWindow->SetEventCallbackFunction(nullptr);

    // Clearing the event queue.
    // This also ensures that we free the memory used by it.
    std::queue<std::function<void()>>().swap(m_EventQueue);

    DispatchEvent<CApplicationShutdownEvent>();
}

void CApplication::OnEvent(IEvent& Event)
{
    CEventDispatcher EventDispatcher(Event);
    EventDispatcher.Dispatch<CWindowCloseEvent>([this](CWindowCloseEvent&)
    {
        Close();

        return true;
    });

    if (Event.GetEventType() != EEventType::MouseMoved)
        ENGINE_LOG_INFO_TAG("Core", Event.ToString());
}

void CApplication::Start()
{
    while (bIsRunning)
    {
        ProcessEvents();

        m_ApplicationWindow->SwapBuffers();
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

void CApplication::ProcessEvents()
{
    m_ApplicationWindow->ProcessEvents();
    
    std::scoped_lock EventQueueMutexLock(m_EventQueueMutex);

    while (!m_EventQueue.empty())
    {
        auto& EventFunction = m_EventQueue.front();
        EventFunction();

        m_EventQueue.pop();
    }
}
