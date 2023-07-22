#include "pch.h"
#include <Core/Log.h>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace VersaMachina
{
    std::shared_ptr<spdlog::logger> Log::__CoreLogger;
    std::shared_ptr<spdlog::logger> Log::__ClientLogger;
    
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        __CoreLogger = spdlog::stdout_color_mt("VersaMachina");
        __CoreLogger->set_level(spdlog::level::trace);
        __ClientLogger = spdlog::stdout_color_mt("App");
        __ClientLogger->set_level(spdlog::level::trace);
    }
    
} // namespace VersaMachina
