#include "pch.h"
#include "OpenGLTexture.h"

#include "GL/glew.h"
#include "stb_image.h"

OpenGLTexture::OpenGLTexture(std::string&& filePath) : Texture(std::move(filePath))
{
    //stbi_set_flip_vertically_on_load(1);
    m_ImageBuffer = stbi_load(m_FilePath.c_str(),
        &m_Width, &m_Height, &m_Channels, 4);

    if(!m_ImageBuffer)
    {
        LOG_ERROR("Couldn't load image: {0}", m_FilePath);
        return;
    }

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height,
       0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    if(m_ImageBuffer)
        stbi_image_free(m_ImageBuffer);
}

OpenGLTexture::~OpenGLTexture()
{
    OpenGLTexture::Unload();
}

void OpenGLTexture::SetActive(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void OpenGLTexture::Unload()
{
    glDeleteTextures(1, &m_TextureID);
}
