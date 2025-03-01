#pragma once

namespace Cuscuz
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void Render() = 0;
    };
}