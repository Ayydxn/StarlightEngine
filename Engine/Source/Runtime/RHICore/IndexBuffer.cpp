#include "StarlightPCH.h"
#include "IndexBuffer.h"
#include "Renderer/Renderer.h"
#include "OpenGLRHI/OpenGLIndexBuffer.h"

std::shared_ptr<IIndexBuffer> IIndexBuffer::Create(const void* BufferData, int64 BufferSize)
{
    switch (CRenderer::GetGraphicsAPI())
    {
        case EGraphicsAPI::OpenGL: return std::make_shared<COpenGLIndexBuffer>(BufferData, BufferSize);
        case EGraphicsAPI::Vulkan: verifyEnginef(false, "Failed to create a index buffer! Vulkan isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D11: verifyEnginef(false, "Failed to create a index buffer! DirectX 11 isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D12: verifyEnginef(false, "Failed to create a index buffer! DirectX 12 isn't supported!") return nullptr;
        case EGraphicsAPI::Metal: verifyEnginef(false, "Failed to create a index buffer! Metal isn't supported!") return nullptr;
        default: verifyEnginef(false, "Failed to create a index buffer! Unknown/unsupported graphics API!") return nullptr;
    }
}
