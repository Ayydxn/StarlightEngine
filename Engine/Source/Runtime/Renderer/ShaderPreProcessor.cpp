#include "StarlightPCH.h"
#include "ShaderPreProcessor.h"

std::unordered_map<EShaderStage, std::string> CShaderPreProcessor::PreProcessShader(const std::string& ShaderSources)
{
    std::unordered_map<EShaderStage, std::string> Result;

    const std::string ShaderStageToken = "#pragma stage :";
    const uint64 ShaderStageTokenLength = ShaderStageToken.length();
    uint64 Position = ShaderSources.find(ShaderStageToken, 0);

    while (Position != std::string::npos)
    {
        const uint64 EndOfShaderStageLine = ShaderSources.find_first_of("\r\n", Position);
        verifyEnginef(EndOfShaderStageLine != std::string::npos, "Failed to pre-process shader! Syntax error!")

        const uint64 StartOfShaderStageName = Position + ShaderStageTokenLength + 1;
        std::string ShaderStageName = ShaderSources.substr(StartOfShaderStageName, EndOfShaderStageLine - StartOfShaderStageName);
        verifyEnginef(GetShaderStageFromString(ShaderStageName) != EShaderStage::Unknown,
            "Failed to get Starlight shader stage for string '{}'!", ShaderStageName)

        const uint64 NextLinePosition = ShaderSources.find_first_not_of("\r\n", EndOfShaderStageLine);
        verifyEnginef(NextLinePosition != std::string::npos, "Failed to pre-process shader! Syntax error!")

        Position = ShaderSources.find(ShaderStageToken, NextLinePosition);
 
        Result[GetShaderStageFromString(ShaderStageName)] = (Position == std::string::npos) ? ShaderSources.substr(NextLinePosition) :
            ShaderSources.substr(NextLinePosition, Position - NextLinePosition);
    }

    return Result;
}

EShaderStage CShaderPreProcessor::GetShaderStageFromString(const std::string& ShaderStage)
{
    if (ShaderStage.compare("vertex") == 0)
        return EShaderStage::Vertex;

    if (ShaderStage.compare("fragment") == 0)
        return EShaderStage::Fragment;

    return EShaderStage::Unknown;
}
