#include "pch.h"
#include "OpenGLTexture.h"

#include "SOIL.h"
#include "GL/glew.h"

bool OpenGLTexture::Load(const std::string& filePath)
{
    int channels = 0;

    auto image = SOIL_load_image(filePath.c_str(),
        &m_Width, &m_Height, &channels, SOIL_LOAD_AUTO);

    if(image == nullptr)
    {
        LOG_ERROR("Couldn't load image: {0}", filePath);
        return false;
    }

    int format = GL_RGB;
    if(channels == 4)
    {
        format = GL_RGBA;
    }

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height,
        0, format, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void OpenGLTexture::Unload()
{
    glDeleteTextures(1, &m_TextureID);
}

void OpenGLTexture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}