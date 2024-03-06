#pragma once

#include "Application/Window.h"

struct GLFWwindow;

class CDesktopWindow : public IWindow
{
public:
    CDesktopWindow() = default;
    ~CDesktopWindow() override;

    void Initialize() override;
    void ProcessEvents() override;
    void SwapBuffers() const override;
    
    std::pair<float, float> GetPosition() const override;

    void Maximize() const override;
    void CenterOnScreen() const override;

    void EnableVSync(bool bEnableVSync) override;

    void SetWindowMode(EWindowMode NewWindowMode) override;
    void EnableResizing(bool bEnableResizing) const override;
    
    void SetTitle(const std::string& Title) const override;

    void* GetHandle() const override { return m_WindowHandle; }
private:
    GLFWwindow* m_WindowHandle;
};
