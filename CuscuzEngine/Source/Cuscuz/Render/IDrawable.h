#pragma once

namespace Cuscuz
{
    class IDrawable
    {
    protected:
        ~IDrawable() = default;

    public:
        virtual void Draw() = 0;
        virtual uint32_t GetDrawOrder() const = 0;
    };
}