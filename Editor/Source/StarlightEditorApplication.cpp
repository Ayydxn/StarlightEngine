#include "Application/Application.h"
#include "Application/ApplicationEntryPoint.h"

class CStarlgihtEditorApplication : public CApplication
{
public:
    CStarlgihtEditorApplication(const CApplicationSpecification& Specification)
        : CApplication(Specification) {}
};

CApplication* CreateApplication(char** Arguments, int32 ArgumentCount)
{
    CApplicationSpecification StarlightEditorApplicationSpecification;
    StarlightEditorApplicationSpecification.Name = "Starlight Editor";
    StarlightEditorApplicationSpecification.CommandLineArguments = CCommandLineArguments(Arguments, ArgumentCount);

    return new CStarlgihtEditorApplication(StarlightEditorApplicationSpecification);
}