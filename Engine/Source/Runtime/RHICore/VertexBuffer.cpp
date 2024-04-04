#include "StarlightPCH.h"
#include "VertexBuffer.h"
#include "OpenGLRHI/OpenGLVertexBuffer.h"
#include "Renderer/Renderer.h"

std::shared_ptr<IVertexBuffer> IVertexBuffer::Create(const void* BufferData, int64 BufferSize)
{
    switch (CRenderer::GetGraphicsAPI())
    {
        case EGraphicsAPI::OpenGL: return std::make_shared<COpenGLVertexBuffer>(BufferData, BufferSize);
        case EGraphicsAPI::Vulkan: verifyEnginef(false, "Failed to create a vertex buffer! Vulkan isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D11: verifyEnginef(false, "Failed to create a vertex buffer! DirectX 11 isn't supported!") return nullptr;
        case EGraphicsAPI::Direct3D12: verifyEnginef(false, "Failed to create a vertex buffer! DirectX 12 isn't supported!") return nullptr;
        case EGraphicsAPI::Metal: verifyEnginef(false, "Failed to create a vertex buffer! Metal isn't supported!") return nullptr;
        default: verifyEnginef(false, "Failed to create a vertex buffer! Unknown/unsupported graphics API!") return nullptr;
    }
}
