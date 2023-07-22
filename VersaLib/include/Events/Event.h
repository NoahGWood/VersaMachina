#pragma once

#ifndef BIT
    #define BIT(x) (1<<x)
#endif 

#include <functional>
#include <sstream>
#include <string>

namespace VersaMachina
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        NetworkTick,
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryWindow         = BIT(1),
        EventCategoryInput          = BIT(2),
        EventCategoryKeyboard       = BIT(3),
        EventCategoryMouse          = BIT(4),
        EventCategoryMouseButton    = BIT(5),
        EventCategoryNetwork        = BIT(6),
    };

    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event
    {

        friend class EventDispatcher;

        public:
            virtual EventType GetEventType() const = 0;
            virtual const char* GetName() const = 0;
            virtual int GetCategoryFlags() const = 0;
            virtual std::string ToString() const { return GetName(); }

            inline bool IsInCategory(EventCategory category){
                return GetCategoryFlags() & category;
            }

            inline bool IsHandled() {
                return __handled;
            }
        protected:
            bool __handled = false;
    };
    
    class EventDispatcher
    {
        public:

    		template<typename T>
            using EventFn = std::function<bool(T&)>;
            EventDispatcher(Event& event)
             : __Event(event)
            {
            }

    		template<typename T>
            bool Dispatch(EventFn<T> func)
            {
                if(__Event.GetEventType() == T::GetStaticType()){
                    __Event.__handled |= func(*(T*)&__Event);
                    return true;
                }
                return false;
            }
        private:
            Event& __Event;

    };

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
} // namespace VersaMachina
