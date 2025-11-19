#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <common/ImGuiLogging.h>

namespace VM
{
    class Logger {
        public:
            static void Init();
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
            inline static std::shared_ptr<ImGuiLogSink>& GetImGuiSink() { return s_ImGuiSink; }
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
            static std::shared_ptr<ImGuiLogSink> s_ImGuiSink;
    };
} // namespace VM

#define CORE_TRACE(...) VM::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) VM::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) VM::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) VM::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) VM::Logger::GetCoreLogger()->critical(__VA_ARGS__)
// Client logging macros (user logs)
#define TRACE(...) VM::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...) VM::Logger::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...) VM::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...) VM::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...) VM::Logger::GetClientLogger()->critical(__VA_ARGS__)

#define CORE_FATAL(...) \
    do { \
        VM::Logger::GetCoreLogger()->critical(__VA_ARGS__); \
        std::exit(-1); \
    } while(0)

#define FATAL(...) \
    do { \
        VM::Logger::GetCoreLogger()->critical(__VA_ARGS__); \
        std::exit(-1); \
    } while(0)
