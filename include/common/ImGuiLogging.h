#pragma once
#include <mutex>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

namespace VM
{
    struct ImGuiLogEntry{
        std::string message;
        spdlog::level::level_enum level;
    };

    class ImGuiLogSink : public spdlog::sinks::base_sink<std::mutex> {
        public:
            const std::vector<ImGuiLogEntry>& Entries() const {
                return m_Entries;
            }
            void Clear(){
                m_Entries.clear();
            }

        protected:
            void sink_it_(const spdlog::details::log_msg& msg) override {
                spdlog::memory_buf_t formatted;
                formatter_->format(msg, formatted);
                m_Entries.push_back(ImGuiLogEntry{
                    fmt::to_string(formatted),
                    msg.level
                });
                if(m_Entries.size() > m_MaxEntries){
                    m_Entries.erase(m_Entries.begin());
                }
            }
            void flush_() override {}

        private:
            std::vector<ImGuiLogEntry> m_Entries;
            size_t m_MaxEntries = 2000;
    };
} // namespace VM
