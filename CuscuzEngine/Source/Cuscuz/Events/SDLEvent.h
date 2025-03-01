#pragma once

#include <SDL_events.h>
#include "CC_Event.h"

namespace Cuscuz
{
    class CC_SDLEvent : public CC_Event
    {
        SDL_Event m_SDLEvent;

    public:
        CC_SDLEvent(const SDL_Event& event) : m_SDLEvent(event) {}
        ~CC_SDLEvent() override = default;

        const SDL_Event& GetSDLEvent() const { return m_SDLEvent; }

        static CC_EventType GetStaticType() { return CC_EventType::SDLEvent; }
        CC_EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "SDLEvent"; }

        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryApplication; }
     
        std::string ToString() const override { return "SDLEvent"; }
    };
}