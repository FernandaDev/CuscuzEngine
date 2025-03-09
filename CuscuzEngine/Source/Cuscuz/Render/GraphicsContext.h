#pragma once

namespace Cuscuz
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        
        virtual void Init() = 0;
        virtual void Render() = 0;
    };
}