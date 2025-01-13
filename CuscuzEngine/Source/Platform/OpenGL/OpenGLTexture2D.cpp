#include "pch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"
#include "GL/glew.h"

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
    m_Width(width), m_Height(height), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

OpenGLTexture2D::OpenGLTexture2D(std::string&& filePath) :
m_RendererID(0), m_Width(0), m_Height(0), m_FilePath(std::move(filePath))
{
    m_Name = std::filesystem::path(m_FilePath).filename().string();

    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    
    const auto imageBuffer = stbi_load(m_FilePath.c_str(),
        &width, &height, &channels, 0);

    CC_ASSERT(imageBuffer, "Couldn't load image: {0}", m_FilePath)

    m_Width = width;
    m_Height = height;

    m_InternalFormat = GL_RGB8;
    m_DataFormat = GL_RGB;
    
    if(channels == 4)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height,
                        m_DataFormat, GL_UNSIGNED_BYTE, imageBuffer);

    stbi_image_free(imageBuffer);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height,
                        m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(unsigned int slot)
{
    glBindTextureUnit(slot, m_RendererID);
}
