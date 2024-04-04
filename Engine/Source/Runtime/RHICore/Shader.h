#pragma once

#include <filesystem>
#include <memory>

enum class EShaderStage
{
    Unknown,

    Vertex,
    Fragment
};

class IShader
{
public:
    virtual ~IShader() = default;

    virtual void Bind() const = 0;

    const std::string& GetName() const { return m_Name; }

    static std::shared_ptr<IShader> Create(const std::filesystem::path& Filepath);
protected:
    inline static std::string m_Name;
};
