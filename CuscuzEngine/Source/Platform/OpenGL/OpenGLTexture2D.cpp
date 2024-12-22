#include "pch.h"
#include "OpenGLTexture2D.h"

#include "GL/glew.h"
#include "stb_image.h"

OpenGLTexture2D::OpenGLTexture2D(std::string&& filePath) :
m_RendererID(0), m_Width(0), m_Height(0), m_FilePath(std::move(filePath))
{
    m_Name = std::filesystem::path(m_FilePath).filename().string();

    int width, height, channels;
    
    const auto imageBuffer = stbi_load(m_FilePath.c_str(),
        &width, &height, &channels, 0);

    CC_ASSERT(imageBuffer, "Couldn't load image: {0}", m_FilePath)

    m_Width = width;
    m_Height = height;

    GLenum internalFormat = GL_RGB8;
    GLenum dataFormat = GL_RGB;
    
    if(channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height,
                        dataFormat, GL_UNSIGNED_BYTE, imageBuffer);

    stbi_image_free(imageBuffer);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::Bind(unsigned int slot)
{
    glBindTextureUnit(slot, m_RendererID);
}
