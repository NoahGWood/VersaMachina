#include <common/Logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
namespace VM
{
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
    std::shared_ptr<ImGuiLogSink>   Logger::s_ImGuiSink;

    void Logger::Init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");

        auto consoleSink = std::make_shared<ImGuiLogSink>();
        s_ImGuiSink = consoleSink;

        auto coreStdout   = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto clientStdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        std::vector<spdlog::sink_ptr> coreSinks   { coreStdout, consoleSink };
        std::vector<spdlog::sink_ptr> clientSinks { clientStdout, consoleSink };

        s_CoreLogger = std::make_shared<spdlog::logger>("Core", coreSinks.begin(), coreSinks.end());
        s_ClientLogger = std::make_shared<spdlog::logger>("App", clientSinks.begin(), clientSinks.end());

        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);

        spdlog::register_logger(s_CoreLogger);
        spdlog::register_logger(s_ClientLogger);
    }
} // namespace VM
