#pragma once

#include "Render/Texture.h"

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture() = default;
    OpenGLTexture(std::string&& filePath);
    ~OpenGLTexture() override;

    void SetActive(unsigned int slot = 0) override;
    void Unload() override;
};