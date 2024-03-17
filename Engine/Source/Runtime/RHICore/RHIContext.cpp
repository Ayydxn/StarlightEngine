#include "StarlightPCH.h"
#include "RHIContext.h"
#include "OpenGLRHI/OpenGLContext.h"
#include "Renderer/Renderer.h"

std::shared_ptr<IRHIContext> IRHIContext::Create(void* WindowHandle)
{
    switch (CRenderer::GetGraphicsAPI())
    {
        case EGraphicsAPI::OpenGL: return std::make_shared<COpenGLContext>(WindowHandle);
        case EGraphicsAPI::Vulkan: verifyEnginef(false, "Failed to create a RHI context! Vulkan isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D11: verifyEnginef(false, "Failed to create a RHI context! DirectX 11 isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D12: verifyEnginef(false, "Failed to create a RHI context! DirectX 12 isn't supported!") return nullptr;
        case EGraphicsAPI::Metal: verifyEnginef(false, "Failed to create a RHI context! Metal isn't supported!") return nullptr;
        default: verifyEnginef(false, "Failed to create a RHI context! Unknown/unsupported graphics API!") return nullptr;
    }
}
