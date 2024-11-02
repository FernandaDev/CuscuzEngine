#pragma once

class Texture
{
protected:
    unsigned int m_TextureID;
    
    int m_Width;
    int m_Height;
    
public:
   Texture() = default;
   virtual ~Texture() = default;

    virtual bool Load(const std::string& filePath) = 0;
    virtual void Unload() = 0;

    virtual void SetActive() = 0;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
};
