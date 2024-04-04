#pragma once

#include <memory>

class IIndexBuffer
{
public:
    virtual ~IIndexBuffer() = default;

    virtual void Bind() const = 0;

    uint32 GetCount() const { return m_Size / sizeof(uint32); }

    static std::shared_ptr<IIndexBuffer> Create(const void* BufferData, int64 BufferSize);
protected:
    inline static uint32 m_Size;
};
