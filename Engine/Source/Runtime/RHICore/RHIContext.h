#pragma once

#include <memory>

class IRHIContext
{
public:
    virtual ~IRHIContext() = default;

    virtual void Initialize() = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetVSync(bool bEnableVSync) = 0;

    static std::shared_ptr<IRHIContext> Create(void* WindowHandle);
};
