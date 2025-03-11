#pragma once
#include "vec4.hpp"
#include "Cuscuz/Events/EventDefinitions.h"

namespace Cuscuz
{
    class OrthographicCamera;
    class IDrawable;
    class Texture2D;

    DECLARE_EVENT_ONE_ARG(DrawableProxyEvent, IDrawable*, drawable)
    
    class Scene
    {
        std::vector<IDrawable*> m_Drawables;
        glm::vec4 m_ClearColor = {0.6f, 0.6f, 0.6f, 1.0f};
        static DrawableProxyEvent m_OnDrawableProxyAdded;
        static DrawableProxyEvent m_OnDrawableProxyRemoved;
        
    public:
        Scene();
        ~Scene();

        void OnRender(const OrthographicCamera& camera) const;

        static DrawableProxyEvent GetOnDrawableProxyAddedEvent() { return m_OnDrawableProxyAdded; }
        static DrawableProxyEvent GetOnDrawableProxyRemovedEvent() { return m_OnDrawableProxyRemoved; }
        
        void OnProxyAdded(IDrawable* drawable);
        void OnProxyRemoved(IDrawable* drawable);
    };
}
