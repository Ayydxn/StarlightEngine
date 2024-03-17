#pragma once

#include "RHICore/RHIBackend.h"

class COpenGLRenderer : public IRHIBackend
{
public:
    COpenGLRenderer() = default;
    ~COpenGLRenderer() override = default;

    void Initialize() override;
    void Shutdown() override {}
    void BeginFrame() override {}
    void EndFrame() override {}
private:
    static void DebugMessageCallback(uint32 Source, uint32 Type, uint32 ID, uint32 Severity, int32 Length, const char* Message, const void* UserData);
};
