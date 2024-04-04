#pragma once

#include "Core/CoreTypes.h"
#include "RHICore/Shader.h"

#include <filesystem>
#include <unordered_map>

class COpenGLShader : public IShader
{
public:
    COpenGLShader(const std::filesystem::path& Filepath);
    ~COpenGLShader() override;

    void Bind() const override;
private:
    void CompileShaderToBytecode(const std::unordered_map<EShaderStage, std::string>& PreProcessedShaderSources);
    void CreateShaderProgram();
private:
    std::unordered_map<uint32, std::vector<uint32>> m_ShaderHandleToBytecode;
    std::filesystem::path m_ShaderFilepath;

    uint32 m_ShaderProgramHandle;
};
