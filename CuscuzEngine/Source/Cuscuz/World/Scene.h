#pragma once

#include "vec4.hpp"
#include "Cuscuz/Events/EventDefinitions.h"
#include "gtc/matrix_transform.hpp"

namespace Cuscuz
{
    class TransformComponent;
}

namespace Cuscuz
{
    class SceneCamera;
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

        uint32_t m_ViewportWidth = 0;
        uint32_t m_ViewportHeight = 0;
        
        SceneCamera* m_MainCamera = {};
        TransformComponent* m_CameraTransform = {};

        friend class LevelSerializer;
    public:
        Scene();
        Scene(SceneCamera* camera);
        ~Scene();

        void SetMainCamera(SceneCamera* camera, TransformComponent* cameraTransform);
        
        void OnRender(const OrthographicCamera& camera) const;
        void OnRender() const;

        static DrawableProxyEvent GetOnDrawableProxyAddedEvent() { return m_OnDrawableProxyAdded; }
        static DrawableProxyEvent GetOnDrawableProxyRemovedEvent() { return m_OnDrawableProxyRemoved; }
        
        void OnProxyAdded(IDrawable* drawable);
        void OnProxyRemoved(IDrawable* drawable);
        void OnViewPortResize(uint32_t width, uint32_t height);

        //Temp
        SceneCamera* GetSceneCamera() const { return m_MainCamera; }
    };
}
