#include "StarlightPCH.h"
#include "Shader.h"
#include "OpenGLRHI/OpenGLShader.h"
#include "Renderer/Renderer.h"

std::shared_ptr<IShader> IShader::Create(const std::filesystem::path& Filepath)
{
    m_Name = Filepath.stem().string();

    switch (CRenderer::GetGraphicsAPI())
    {
        case EGraphicsAPI::OpenGL: return std::make_shared<COpenGLShader>(Filepath);
        case EGraphicsAPI::Vulkan: verifyEnginef(false, "Failed to create a shader! Vulkan isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D11: verifyEnginef(false, "Failed to create a shader! DirectX 11 isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D12: verifyEnginef(false, "Failed to create a shader! DirectX 12 isn't supported!") return nullptr;
        case EGraphicsAPI::Metal: verifyEnginef(false, "Failed to create a shader! Metal isn't supported!") return nullptr;
        default: verifyEnginef(false, "Failed to create a shader! Unknown/unsupported graphics API!") return nullptr;
    }
}
