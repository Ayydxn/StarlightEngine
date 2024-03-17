#pragma once

#include "RHICore/RHIContext.h"

class COpenGLContext : public IRHIContext
{
public:
    COpenGLContext(void* WindowHandle);
    ~COpenGLContext() override = default;

    void Initialize() override;
    void SwapBuffers() override;
    void SetVSync(bool bEnableVSync) override;
private:
    void* m_WindowHandle;
};
