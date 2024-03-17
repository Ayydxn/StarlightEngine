﻿#pragma once

#include "RHICore/RHIBackend.h"

enum class EGraphicsAPI
{
    OpenGL,
    Vulkan,
    Direct3D11,
    Direct3D12,
    Metal
};

class CRenderer
{
public:
    static void PreInitialize();
    static void Initialize();
    static void Shutdown();

    static void BeginFrame();
    static void EndFrame();

    static EGraphicsAPI GetGraphicsAPI() { return m_GraphicsAPI; }
    static void SetGraphicsAPI(EGraphicsAPI NewGraphicsAPI) { m_GraphicsAPI = NewGraphicsAPI; }
private:
    inline static std::shared_ptr<IRHIBackend> m_RHIBackend;
    
    inline static EGraphicsAPI m_GraphicsAPI;
};
