#include "StarlightPCH.h"
#include "Application.h"

extern bool bIsApplicationRunning;

CApplication::CApplication(const CApplicationSpecification& Specification)
    : m_ApplicationSpecification(Specification), m_CommandLineArguments(Specification.CommandLineArguments)
{
    m_ApplicationInstance = this;

    CLogging::Initialize();

    ENGINE_LOG_INFO_TAG("Core", "Initializing Starlight Engine...");
}

CApplication::~CApplication()
{
    ENGINE_LOG_INFO_TAG("Core", "Shutting down...");
}

void CApplication::Start()
{
    while (bIsRunning)
    {
        
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