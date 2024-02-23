#include "StarlightPCH.h"
#include "Application.h"

extern bool bIsApplicationRunning;

CApplication::CApplication(const CApplicationSpecification& Specification)
    : m_ApplicationSpecification(Specification), m_CommandLineArguments(Specification.CommandLineArguments)
{
    m_ApplicationInstance = this;

    std::cout << "Welcome to " << Specification.Name << "!\n";
    std::cout << "Command Line Arguments:\n";

    if (!m_CommandLineArguments.IsEmpty())
    {
        for (const std::string& CommandLineArgument : m_CommandLineArguments)
            std::cout << "  " << CommandLineArgument << "\n";
    }
    else
    {
        std::cout << "  No command line arguments were passed! :(\n";
    }
}

CApplication::~CApplication()
{
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