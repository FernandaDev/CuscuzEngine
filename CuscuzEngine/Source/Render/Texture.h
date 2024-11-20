#pragma once

#include <string>

class Texture
{
protected:
    unsigned int m_TextureID;
    unsigned char* m_ImageBuffer;
    std::string m_FilePath;
    int m_Width, m_Height;
    int m_Channels;
    
public:
    Texture(std::string&& filePath) :
    m_TextureID(0), m_ImageBuffer(nullptr),m_FilePath(std::move(filePath)),
    m_Width(0), m_Height(0), m_Channels(0){}
    virtual ~Texture() = default;

    virtual void Unload() = 0;

    virtual void SetActive(unsigned int slot = 0) = 0;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
};
