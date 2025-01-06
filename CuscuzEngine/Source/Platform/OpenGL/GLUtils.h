#pragma once

#include "GL/glew.h"
    #define GL_ASSERT(x) if(!(x)) __debugbreak();
    #define GLCall(x) GLUtils::GLClearError();\
    x;\
    GL_ASSERT(GLUtils::GLLogCall(#x, __FILE__, __LINE__))

namespace GLUtils
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
}