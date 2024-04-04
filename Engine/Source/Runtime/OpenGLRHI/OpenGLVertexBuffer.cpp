#include "StarlightPCH.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

COpenGLVertexBuffer::COpenGLVertexBuffer(const void* BufferData, int64 BufferSize)
{
    glCreateBuffers(1, &m_VertexBufferHandle);
    glNamedBufferData(m_VertexBufferHandle, BufferSize, BufferData, GL_STATIC_DRAW);
}

COpenGLVertexBuffer::~COpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_VertexBufferHandle);
}

void COpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferHandle);
}
