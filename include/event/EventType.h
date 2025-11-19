#pragma once
namespace VM
{
    enum class EventType
    {
        Init, Tick, Shutdown,
        Created, Destroyed, Modified,
        Request, Complete, Failed, Status,
        Custom
    };
} // namespace VM
