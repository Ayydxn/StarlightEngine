#include "StarlightPCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

COpenGLContext::COpenGLContext(void* WindowHandle)
    : m_WindowHandle(WindowHandle)
{
    verifyEnginef(WindowHandle != nullptr, "Failed to creata an OpenGL RHI context! Window handle is invalid!")
}

void COpenGLContext::Initialize()
{
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_WindowHandle));
    verifyEnginef(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to create an OpenGL context!")

    ENGINE_LOG_INFO_TAG("Renderer", "Graphics Card Info:");
    ENGINE_LOG_INFO_TAG("Renderer", "  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    ENGINE_LOG_INFO_TAG("Renderer", "  Device: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    ENGINE_LOG_INFO_TAG("Renderer", "  Driver Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void COpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_WindowHandle));
}

void COpenGLContext::SetVSync(bool bEnableVSync)
{
    glfwSwapInterval(bEnableVSync);
}
