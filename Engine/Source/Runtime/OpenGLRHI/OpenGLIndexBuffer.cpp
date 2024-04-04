#include "StarlightPCH.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

COpenGLIndexBuffer::COpenGLIndexBuffer(const void* BufferData, int64 BufferSize)
{
    glCreateBuffers(1, &m_IndexBufferHandle);
    glNamedBufferData(m_IndexBufferHandle, BufferSize, BufferData, GL_STATIC_DRAW);
}

COpenGLIndexBuffer::~COpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_IndexBufferHandle);
}

void COpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferHandle);
}
