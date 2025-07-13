#pragma once

#include "Cuscuz/Render/Framebuffer.h"
#include "GL/glew.h"
    #define GL_ASSERT(x) if(!(x)) __debugbreak();
    #define GLCall(x) GLUtils::GLClearError();\
    x;\
    GL_ASSERT(GLUtils::GLLogCall(#x, __FILE__, __LINE__))

namespace Cuscuz::GLUtils
{    
    static void GLClearError()
    {
        while(glGetError() != GL_NO_ERROR);
    }

    static bool GLLogCall(const char* function, const char* file, int line)
    {
        while(const GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (" << error << "): " << function << " "<<
                file << ":" << line << std::endl;
            return false;
        }
        return true;
    }

    static GLint GetGLFormat(FramebufferTextureFormat format)
    {
        switch (format)
        {
            case FramebufferTextureFormat::RGBA8:
                return GL_RGBA8;
            case FramebufferTextureFormat::RGBA16F:
                return GL_RGBA16F;
            case FramebufferTextureFormat::DEPTH24STENCIL8:
                return GL_DEPTH24_STENCIL8;
            default:
                CC_ASSERT(false, "Unknown FramebufferTextureFormat!");
                return GL_NONE;
        }
    }
    
    static bool IsDepthFormat(FramebufferTextureFormat format)
    {
        switch (format)
        {
        case FramebufferTextureFormat::DEPTH24STENCIL8:
            return true;
        default:
            return false;
        }
    }

    static void CreateTextures(uint32_t* outID, uint32_t count)
    {
        glCreateTextures(GL_TEXTURE_2D, count, outID);
    }

    static void BindTexture(uint32_t id)
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    // note: it doesn't support multisampling
    static void AttachColorTexture(uint32_t id, GLenum format, uint32_t width, uint32_t height, int index)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
    }

    static void AttachDepthTexture(uint32_t id, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, id, 0);
    }
}