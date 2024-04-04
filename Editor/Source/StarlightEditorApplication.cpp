#include "Application/Application.h"
#include "Application/ApplicationEntryPoint.h"
#include "RHICore/Shader.h"

class CStarlightEditorLayer : public ILayer
{
public:
    CStarlightEditorLayer()
        : ILayer("Starlight Editor") {}
    
    void OnAttach() override
    {
        m_DefaultShader = IShader::Create("Resources/Shaders/DefaultShader.glsl");
    }
private:
    std::shared_ptr<IShader> m_DefaultShader;
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