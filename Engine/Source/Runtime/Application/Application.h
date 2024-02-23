#pragma once

#include "Core/Misc/CommandLineArguments.h"

#include <string>

struct CApplicationSpecification
{
    std::string Name = "Starlight Engine";

    CCommandLineArguments CommandLineArguments;
};

class CApplication
{
public:
    CApplication(const CApplicationSpecification& Specification = CApplicationSpecification());
    virtual ~CApplication();

    void Start();
    void Restart();
    void Close();
    
    static CApplication& GetInstance() { return *m_ApplicationInstance; }

    const CApplicationSpecification& GetSpecification() const { return m_ApplicationSpecification; }

    const CCommandLineArguments& GetCommandLineArguments() const { return m_CommandLineArguments; }
private:
    inline static CApplication* m_ApplicationInstance = nullptr;

    CApplicationSpecification m_ApplicationSpecification;
    CCommandLineArguments m_CommandLineArguments;
    
    bool bIsRunning = true;
};

CApplication* CreateApplication(char** Arguments, int32 ArgumentCount);