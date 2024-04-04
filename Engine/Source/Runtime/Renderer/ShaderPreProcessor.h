#pragma once

#include "RHICore/Shader.h"

#include <unordered_map>

class CShaderPreProcessor
{
public:
    static std::unordered_map<EShaderStage, std::string> PreProcessShader(const std::string& ShaderSources);
private:
    static EShaderStage GetShaderStageFromString(const std::string& ShaderStage);
};
