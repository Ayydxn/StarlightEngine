#pragma once

#include <memory>

class IRHIBackend
{
public:
    virtual ~IRHIBackend() = default;
    
    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    static std::shared_ptr<IRHIBackend> Create();
};
