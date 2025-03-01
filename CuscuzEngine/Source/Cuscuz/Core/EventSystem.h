#pragma once

#include "Cuscuz/Events/EventDefinitions.h"

namespace Cuscuz
{
    class EventSystem
    {
    public:
        using EventCallbackFn = std::function<void(CC_Event&)>;

    private:
        EventCallbackFn m_EventCallbackFn;

    public:
        EventSystem() = default;
        ~EventSystem() = default;

        void SetEventCallback(const EventCallbackFn& callback);

        void OnUpdate() const;
    };
}
