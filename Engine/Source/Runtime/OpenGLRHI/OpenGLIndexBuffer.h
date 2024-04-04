#pragma once

#include "RHICore/IndexBuffer.h"

class COpenGLIndexBuffer : public IIndexBuffer
{
public:
    COpenGLIndexBuffer(const void* BufferData, int64 BufferSize);
    ~COpenGLIndexBuffer() override;

    void Bind() const override;
private:
    uint32 m_IndexBufferHandle;
};
