#include "StarlightPCH.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"

extern bool bIsApplicationRunning;

CApplication::CApplication(const CApplicationSpecification& Specification)
    : m_ApplicationSpecification(Specification), m_CommandLineArguments(Specification.CommandLineArguments)
{
    m_ApplicationInstance = this;

    CLogging::Initialize();

    ENGINE_LOG_INFO_TAG("Core", "Initializing Starlight Engine...");

    DispatchEvent<CApplicationInitializeEvent>();
}

CApplication::~CApplication()
{
    ENGINE_LOG_INFO_TAG("Core", "Shutting down...");

    // Clearing the event queue.
    // This also ensures that we free the memory used by it.
    std::queue<std::function<void()>>().swap(m_EventQueue);

    DispatchEvent<CApplicationShutdownEvent>();
}

void CApplication::OnEvent(IEvent& Event)
{
    CEventDispatcher EventDispatcher(Event);
}

void CApplication::Start()
{
    while (bIsRunning)
    {
        ProcessEvents();
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

void CApplication::ProcessEvents()
{
    std::scoped_lock EventQueueMutexLock(m_EventQueueMutex);

    while (!m_EventQueue.empty())
    {
        auto& EventFunction = m_EventQueue.front();
        EventFunction();

        m_EventQueue.pop();
    }
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