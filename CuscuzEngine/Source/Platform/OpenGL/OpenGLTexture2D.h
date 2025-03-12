#pragma once

#include <string>
#include "Cuscuz/Render/Texture.h"

namespace Cuscuz
{
    class OpenGLTexture2D : public Texture2D
    {
        uint32_t m_RendererID;
        int32_t m_Width, m_Height;
        std::string m_Name;
        std::string m_FilePath;
        uint32_t m_InternalFormat, m_DataFormat;
    
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(std::string&& filePath);
        ~OpenGLTexture2D() override;

        bool operator==(const Texture& other) const override
        {
            return m_RendererID == other.GetRendererID();
        }

        const std::string& GetName() const { return m_Name; } 
        std::string_view GetPath() const { return m_FilePath; }
        uint32_t GetRendererID() const override { return m_RendererID; }
        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

        void SetData(void* data, uint32_t size) override;
        void Bind(uint32_t slot = 0) override;
    };
}