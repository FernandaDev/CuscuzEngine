#pragma once

#include <string>
#include <sstream>
#include "Cuscuz/Core/Core.h"

namespace Cuscuz
{
    enum class CC_EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocused,
        WindowUnfocused,
        //WindowMoved,
        KeyDown,
        KeyUp,
        MouseButtonDown,
        MouseButtonUp,
        MouseMoved,
        MouseScrolled,
        SDLEvent
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };

    class CC_Event
    {
        friend class CC_EventSingleDispatcher;

    protected:
        virtual ~CC_Event() = default;
        bool m_Handled = false;

    public:
        virtual CC_EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        bool Handled() const { return m_Handled; }
    };

    inline std::ostream& operator<<(std::ostream& os, const CC_Event& e)
    {
        return os << e.ToString();
    }
}
