#pragma once
#include <app/AppContext.h>
#include <imgui.h>
#include <common/Base.h>

namespace VM
{
    class IMenu
    {
        public:
            explicit IMenu(std::shared_ptr<AppContext> context)
                : m_AppContext(std::move(context)) {}
            virtual ~IMenu() = default;
            
            virtual const std::string Name() const { return m_Name; }
            bool IsOpen() const { return m_IsOpen; }
            void Open() { m_IsOpen = true; }
            virtual void Tick() { }
            virtual void Render() { }

        protected:
            std::shared_ptr<AppContext> m_AppContext;
            std::string m_Name = "IMenu";
            bool m_IsOpen = true;
    };
} // namespace VM
