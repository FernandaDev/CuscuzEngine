#pragma once

#include <string>
#include <filesystem>

class Texture
{
protected:
    unsigned short m_GUID = -1;
    unsigned int m_TextureID;
    unsigned char* m_ImageBuffer;
    std::string m_Name;
    std::string m_FilePath;
    int m_Width, m_Height;
    int m_Channels;
    
public:
    Texture () = default;
    Texture(std::string&& filePath) :
    m_TextureID(0), m_ImageBuffer(nullptr),m_FilePath(std::move(filePath)),
    m_Width(0), m_Height(0), m_Channels(0)
    {
        m_Name = std::filesystem::path(m_FilePath).filename().string();
    }
    
    virtual ~Texture() = default;

    virtual void Unload() = 0;
    
    virtual void SetActive(unsigned int slot = 0) = 0;
    void SetGUID(unsigned short GUID) { m_GUID = GUID; }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetRendererId() const { return m_TextureID; }
    std::string_view GetPath() const { return m_FilePath; }
    const std::string& GetName() const { return m_Name; } 
    unsigned short GetGUID() const { return m_GUID; }
};
