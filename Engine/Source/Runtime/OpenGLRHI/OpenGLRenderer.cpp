#include "StarlightPCH.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>

void COpenGLRenderer::Initialize()
{
    #if defined(STARLIGHT_BUILD_DEBUG) || defined(STARLIGHT_BUILD_RELEASE)
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(COpenGLRenderer::DebugMessageCallback, nullptr);
        
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_MEDIUM | GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DEBUG_SEVERITY_MEDIUM | GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
    #endif
}

void COpenGLRenderer::DebugMessageCallback(uint32 Source, uint32 Type, uint32 ID, uint32 Severity, int32 Length, const char* Message, const void* UserData)
{
    switch (Severity)
    {
        case GL_DEBUG_SEVERITY_MEDIUM:
        {
            if (Type == GL_DEBUG_TYPE_ERROR)
            {
                ENGINE_LOG_WARN_TAG("OpenGL Debug - Error", Message);
                break;
            }
            
            if (Type == GL_DEBUG_TYPE_PERFORMANCE)
            {
                ENGINE_LOG_WARN_TAG("OpenGL Debug - Performance", Message);
                break;    
            }
                
            break;
        }

        case GL_DEBUG_SEVERITY_HIGH:
        {
            if (Type == GL_DEBUG_TYPE_ERROR)
            {
                ENGINE_LOG_ERROR_TAG("OpenGL Debug - Error", Message);
                break;
            }
            
            if (Type == GL_DEBUG_TYPE_PERFORMANCE)
            {
                ENGINE_LOG_ERROR_TAG("OpenGL Debug - Performance", Message);
                break;    
            }
                
            break;
        }

        default: break;
    }
}
