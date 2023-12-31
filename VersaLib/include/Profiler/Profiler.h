#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace VersaMachina
{
    namespace Profiling
    {
        struct ProfileResult
        {
            std::string Name;
            long long Start, End;
            uint32_t ThreadID;
        };

        struct ProfilerSession
        {
            std::string Name;
            /* data */
        };
        

        class Profiler
        {
            private:
                ProfilerSession* m_CurrentSession;
                std::ofstream m_OutputStream;
                int m_ProfileCount;

            public:
                Profiler()
                    : m_CurrentSession(nullptr), m_ProfileCount(0) { }

                Profiler(const Profiler&) = delete;
                Profiler(const Profiler&&) = delete;
                ~Profiler()
                {
                    EndSession();
                }

                void BeginSession(const std::string& name, const std::string& filepath = "results.json")
                {
                    m_OutputStream.open(filepath);
                    WriteHeader();
                    m_CurrentSession = new ProfilerSession{ name };
                }

                void EndSession()
                {
                    WriteFooter();
                    m_OutputStream.close();
                    delete m_CurrentSession;
                    m_CurrentSession = nullptr;
                    m_ProfileCount = 0;
                }

                void WriteProfile(const ProfileResult& result)
                {
                    if(m_ProfileCount++ >0)
                    {
                        m_OutputStream << ",";
                    }
                    
                    std::string name = result.Name;
                    std::replace(name.begin(), name.end(), '"', '\'');

        			m_OutputStream << "{";
        			m_OutputStream << "\"cat\":\"function\",";
        			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        			m_OutputStream << "\"name\":\"" << name << "\",";
        			m_OutputStream << "\"ph\":\"X\",";
        			m_OutputStream << "\"pid\":0,";
        			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        			m_OutputStream << "\"ts\":" << result.Start;
        			m_OutputStream << "}";

                    m_OutputStream.flush();
                }

                void WriteHeader()
                {
        			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        			m_OutputStream.flush();
                }

                void WriteFooter()
                {
                    m_OutputStream << "]}";
                    m_OutputStream.flush();
                }

            static Profiler& Get()
            {
                static Profiler instance;
                return instance;
            }
        };

        class ProfilerTimer
        {
            public:
                ProfilerTimer(const char* name)
                    : m_Name(name), m_Stopped(false)
                {
                    m_StartTimepoint = std::chrono::high_resolution_clock::now();
                }
                ~ProfilerTimer()
                {
                    if(!m_Stopped)
                    {
                        Stop();
                    }
                }

                void Stop()
                {
                    auto endTimePoint = std::chrono::high_resolution_clock::now();
                    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
                    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
                    

        			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
                    Profiler::Get().WriteProfile({m_Name, start, end, threadID});

                    m_Stopped = true;
                }

            private:
                const char* m_Name;
                std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
                bool m_Stopped;
        };
        
    } // namespace Profiling
} // namespace VersaMachina

//#define VM_PROFILE 1

#if VM_PROFILE

	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define VM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define VM_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define VM_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define VM_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define VM_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define VM_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define VM_FUNC_SIG __func__
	#else
		#define VM_FUNC_SIG "VM_FUNC_SIG unknown!"
	#endif

	#define VM_PROFILE_BEGIN_SESSION(name, filepath) ::VersaMachina::Profiling::Profiler::Get().BeginSession(name, filepath)
	#define VM_PROFILE_END_SESSION() ::VersaMachina::Profiling::Profiler::Get().EndSession()
	#define VM_PROFILE_SCOPE(name) ::VersaMachina::Profiling::ProfilerTimer timer##__LINE__(name);
	#define VM_PROFILE_FUNCTION() VM_PROFILE_SCOPE(VM_FUNC_SIG)
#else
	#define VM_PROFILE_BEGIN_SESSION(name, filepath)
	#define VM_PROFILE_END_SESSION()
	#define VM_PROFILE_SCOPE(name)
	#define VM_PROFILE_FUNCTION()
#endif