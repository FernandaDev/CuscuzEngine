#pragma once
#include <Cuscuz/Core/Core.h>

namespace Cuscuz
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void Bind(unsigned int slot = 0) = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;
        virtual void SetData(void* data, uint32_t size) = 0;
        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static CC_AssetRef<Texture2D> Create(std::string&& filepath);
        static CC_AssetRef<Texture2D> Create(uint32_t width, uint32_t height);
    };
}