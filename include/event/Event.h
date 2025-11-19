#pragma once
#include <common/Base.h>
#include <event/EventCategory.h>
#include <event/EventType.h>
#include <event/EventData.h>

namespace VM
{
    struct Event{
        EventCategory category;
        EventType type;
        EventData data;
        bool handled = false;
    };
} // namespace VM
