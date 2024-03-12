#include "Application/Application.h"
#include "Application/ApplicationEntryPoint.h"

class CStarlightEditorLayer : public ILayer
{
public:
    CStarlightEditorLayer()
        : ILayer("Starlight Editor") {}
    
    void OnAttach() override
    {
        APPLICATION_LOG_INFO_TAG("Core", "Hello from the Starlight Editor layer!");
    }
};

class CStarlightEditorApplication : public CApplication
{
public:
    CStarlightEditorApplication(const CApplicationSpecification& Specification)
        : CApplication(Specification)
    {
        PushLayer(new CStarlightEditorLayer());
    }
};

CApplication* CreateApplication(char** Arguments, int32 ArgumentCount)
{
    CApplicationSpecification StarlightEditorApplicationSpecification;
    StarlightEditorApplicationSpecification.Name = "Starlight Editor";
    StarlightEditorApplicationSpecification.CommandLineArguments = CCommandLineArguments(Arguments, ArgumentCount);

    return new CStarlightEditorApplication(StarlightEditorApplicationSpecification);
}