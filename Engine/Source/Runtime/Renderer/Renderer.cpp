#include "StarlightPCH.h"
#include "Renderer.h"

void CRenderer::PreInitialize()
{
    // TODO: (Ayydan) The graphics API we use should come from a configuration file.
    // But for now, we'll force OpenGL since it's the only one we support.
    m_GraphicsAPI = EGraphicsAPI::OpenGL;
}

void CRenderer::Initialize()
{
    m_RHIBackend = IRHIBackend::Create();
    m_RHIBackend->Initialize();
}

void CRenderer::Shutdown()
{
    m_RHIBackend->Shutdown();
}

void CRenderer::BeginFrame()
{
    m_RHIBackend->BeginFrame();
}

void CRenderer::EndFrame()
{
    m_RHIBackend->EndFrame();
}
