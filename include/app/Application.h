#pragma once
#include <common/Base.h>
#include <app/AppContext.h>
namespace VM
{    
    class Application{
        public:
            static Application& Get() { return *s_Instance; }
            bool IsRunning() const { return m_Running; }

            bool Init();
            bool Tick();
            bool Shutdown();

            void Save();
            void Load();
            void New();

        private:
            inline static Application* s_Instance = nullptr;
            std::shared_ptr<AppContext> m_AppContext;
    
            bool m_Running = true;
            bool m_ShutdownCalled = false;
            uint64_t m_Frame = 0;
            double m_DeltaTime = 0.0;
            std::chrono::steady_clock::time_point m_LastFrame;
    };
} // namespace VM
