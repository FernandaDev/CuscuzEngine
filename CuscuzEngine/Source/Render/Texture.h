#pragma once
#include "Core/CC_Core.h"

class Texture
{
public:
    virtual ~Texture() = default;

    virtual void Bind(unsigned int slot = 0) = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual uint32_t GetRendererID() const = 0;
};

class Texture2D : public Texture
{
public:

    static CC_AssetRef<Texture2D> Create(std::string&& filepath);
};