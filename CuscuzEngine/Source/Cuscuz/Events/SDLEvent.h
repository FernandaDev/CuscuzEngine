#pragma once

#include <SDL_events.h>
#include "CuscuzEvent.h"

namespace Cuscuz
{
    class CC_SDLEvent : public CuscuzEvent
    {
        SDL_Event m_SDLEvent;

    public:
        CC_SDLEvent(const SDL_Event& event) : m_SDLEvent(event) {}
        ~CC_SDLEvent() override = default;

        const SDL_Event& GetSDLEvent() const { return m_SDLEvent; }

        static CuscuzEventType GetStaticType() { return CuscuzEventType::SDLEvent; }
        CuscuzEventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "SDLEvent"; }

        int GetCategoryFlags() const override
        { return EventCategory::EventCategoryApplication; }
     
        std::string ToString() const override { return "SDLEvent"; }
    };
}