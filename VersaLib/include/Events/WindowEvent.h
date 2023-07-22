#pragma once

#include "Events/Event.h"

namespace VersaMachina
{
    // WindowClose,

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    // WindowResize,

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : __Width(width), __Height(height) {}

        unsigned int GetWidth() const { return __Width; }
        unsigned int GetHeight() const { return __Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << __Width << ", " << __Height;
            return ss.str();
        }

    private:
        unsigned int __Width, __Height;
    };

    // WindowFocus,
    // WindowLostFocus,
    // WindowMove,

} // namespace VersaMachina
