#include "StarlightPCH.h"
#include "PlatformUtils.h"

#ifdef STARLIGHT_PLATFORM_WIN64
    #include "Windows/WindowsPlatformUtils.h"
#endif

std::shared_ptr<IPlatformUtils> IPlatformUtils::CreateInstance()
{
    #ifdef STARLIGHT_PLATFORM_WIN64
        return std::make_shared<CWindowsPlatformUtils>();
    #else
        verifyEnginef(false, "Failed to create platform utilities! Unknown/unsupported platform!")
        return nullptr;
    #endif
}

std::filesystem::path IPlatformUtils::GetApplicationDirectory()
{
    return m_PlatformUtilsInstance->GetApplicationDirectory_Implementation();
}
