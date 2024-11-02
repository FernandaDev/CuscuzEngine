#pragma once

#include "Render/Texture.h"

class OpenGLTexture : public Texture
{
public:
    OpenGLTexture() = default;
    ~OpenGLTexture() override = default;

    bool Load(const std::string& filePath) override;
    void Unload() override;
    void SetActive() override;
};