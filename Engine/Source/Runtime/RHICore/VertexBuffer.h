#pragma once

#include "Core/CoreTypes.h"

class IVertexBuffer
{
public:
    virtual ~IVertexBuffer() = default;

    virtual void Bind() const = 0;

    static std::shared_ptr<IVertexBuffer> Create(const void* BufferData, int64 BufferSize);
};
