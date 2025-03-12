
#include <Cuscuz/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Cuscuz
{
    class EditorApp : public Engine
    {
    public:
        EditorApp()
        {
            PushLayer(std::make_shared<EditorLayer>());
        }

        ~EditorApp() override = default;
    };


    Engine* CreateApplication()
    {
        return new EditorApp();
    }
}