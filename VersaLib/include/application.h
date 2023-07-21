#pragma once

namespace VersaMachina
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();
    };
    
    // Defined in client
    Application* CreateApplication();

} // namespace VersaMachina
