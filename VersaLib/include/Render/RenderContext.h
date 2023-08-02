#pragma once

namespace VersaMachina
{
    namespace Render
    {
        class RenderContext
        {
            public:
                virtual void Init() = 0;
                virtual void SwapBuffers() = 0;


            private:

            protected:


        };
    } // namespace Render
    
} // namespace VersaMachina
