#pragma once

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

namespace VersaMachina
{
    class Log
    {
        public:
            static void Init();
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()  { return __CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger()  { return __ClientLogger; }

        private:
            static std::shared_ptr<spdlog::logger> __CoreLogger;
            static std::shared_ptr<spdlog::logger> __ClientLogger;
    };

} // namespace VersaMachina


// Core logging macros

#define VM_CORE_TRACE(...) ::VersaMachina::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VM_CORE_INFO(...) ::VersaMachina::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VM_CORE_WARN(...) ::VersaMachina::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VM_CORE_ERROR(...) ::VersaMachina::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VM_CORE_CRITICAL(...) ::VersaMachina::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logging macros

#define VM_TRACE(...) ::VersaMachina::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VM_INFO(...) ::VersaMachina::Log::GetClientLogger()->info(__VA_ARGS__)
#define VM_WARN(...) ::VersaMachina::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VM_ERROR(...) ::VersaMachina::Log::GetClientLogger()->error(__VA_ARGS__)
#define VM_CRITICAL(...) ::VersaMachina::Log::GetClientLogger()->critical(__VA_ARGS__)
