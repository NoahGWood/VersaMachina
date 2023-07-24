#pragma once

#include "Core/Base.h"
#include "Events/Event.h"

namespace VersaMachina
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title="VersaMachina",
        uint32_t width = 700,
        uint32_t height = 400)
            : Title(title), Width(width), Height(height) {}
    };

    class Window
    {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() = default;
            virtual void OnUpdate() = 0;

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;

            // Window Attributes
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;

            virtual void* GetNativeWindow() const = 0;

            static Window* Create(const WindowProps& props = WindowProps());

    };
} // namespace VersaMachina

