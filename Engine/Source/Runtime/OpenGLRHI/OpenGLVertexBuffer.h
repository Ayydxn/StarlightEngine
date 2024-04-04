#pragma once

#include "RHICore/VertexBuffer.h"

class COpenGLVertexBuffer : public IVertexBuffer
{
public:
    COpenGLVertexBuffer(const void* BufferData, int64 BufferSize);
    ~COpenGLVertexBuffer() override;

    void Bind() const override;
private:
    uint32 m_VertexBufferHandle;
};
