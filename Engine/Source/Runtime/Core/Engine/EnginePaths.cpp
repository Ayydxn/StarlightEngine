﻿#include "StarlightPCH.h"
#include "EnginePaths.h"
#include "Utils/PlatformUtils.h"

std::filesystem::path CEnginePaths::GetEngineDirectory()
{
    std::filesystem::path EngineDirectory = IPlatformUtils::GetApplicationDirectory() / "Starlight Engine";
    CreateDirectories(EngineDirectory);
    
    return EngineDirectory;
}

std::filesystem::path CEnginePaths::GetCacheDirectory()
{
    std::filesystem::path CacheDirectory =  GetEngineDirectory() / "Cache";
    CreateDirectories(CacheDirectory);
    
    return CacheDirectory;
}

std::filesystem::path CEnginePaths::GetShaderCacheDirectory()
{
    std::filesystem::path ShaderCacheDirectory = GetCacheDirectory() / "Shaders";
    CreateDirectories(ShaderCacheDirectory);
    
    return ShaderCacheDirectory;
}

void CEnginePaths::CreateDirectories(const std::filesystem::path& DirectoryPath)
{
    if (!std::filesystem::exists(DirectoryPath))
        std::filesystem::create_directories(DirectoryPath);
}
