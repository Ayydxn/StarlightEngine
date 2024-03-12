#include "StarlightPCH.h"
#include "Window.h"

#ifdef STARLIGHT_PLATFORM_WIN64
    #include "DesktopWindow.h"
#endif

std::unique_ptr<IWindow> IWindow::Create(const FWindowSpecification& Specification)
{
    m_Specification = Specification;

    m_WindowState.Title = Specification.Title;
    m_WindowState.Width = Specification.Width;
    m_WindowState.Height = Specification.Height;
    m_WindowState.bIsDecorationEnabled = Specification.bEnableDecoration;
    m_WindowState.WindowMode = Specification.WindowMode;
    m_WindowState.bIsVSyncEnabled = Specification.bEnableVSync;
    m_WindowState.bIsResizingEnabled = Specification.bEnableResizing;

    #if defined(STARLIGHT_PLATFORM_WIN64) || defined(STARLIGHT_PLATFORM_MAC) || defined(STARLIGHT_PLATFORM_LINUX)
        return std::make_unique<CDesktopWindow>();
    #else
        verifyEnginef(false, "Failed to create window '{}'! Unknown/unsupported platform!", Specification.Title)
        return nullptr;
    #endif
}