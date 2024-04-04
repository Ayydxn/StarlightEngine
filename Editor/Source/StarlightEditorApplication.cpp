#include "Application/Application.h"
#include "Application/ApplicationEntryPoint.h"
#include "RHICore/IndexBuffer.h"
#include "RHICore/Shader.h"
#include "RHICore/VertexBuffer.h"

class CStarlightEditorLayer : public ILayer
{
public:
    CStarlightEditorLayer()
        : ILayer("Starlight Editor") {}
    
    void OnAttach() override
    {
        constexpr float Vertices[9] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        constexpr int32 Indices[3] =
        {
            0, 1, 2
        };
        
        m_DefaultShader = IShader::Create("Resources/Shaders/DefaultShader.glsl");
        m_VertexBuffer = IVertexBuffer::Create(Vertices, sizeof(Vertices));
        m_IndexBuffer = IIndexBuffer::Create(Indices, sizeof(Indices));
    }
private:
    std::shared_ptr<IShader> m_DefaultShader;
    std::shared_ptr<IVertexBuffer> m_VertexBuffer;
    std::shared_ptr<IIndexBuffer> m_IndexBuffer;
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