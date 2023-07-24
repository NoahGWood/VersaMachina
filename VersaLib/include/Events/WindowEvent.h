#pragma once

#include "Events/Event.h"

namespace VersaMachina
{
    // WindowClose,

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent(){}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)
    };

    // WindowResize,

    class WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}


        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }


        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryWindow)

    private:
        unsigned int m_Width, m_Height;
    };

    // WindowFocus,
    // WindowLostFocus,
    // WindowMove,

} // namespace VersaMachina
