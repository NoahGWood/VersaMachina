#pragma once

#include <string>
#include <glm/glm.hpp>

namespace VersaMachina
{
    namespace Tuners
    {
        struct GaugeComponent
        {
            std::string Name = "Gauge Name (seen in menu)";
            std::string Title = "Gauge Title (displayed on gauge)";
            std::string Units = "%";
            float Low=0, LowWarn=600, LowDanger=300;
            float High=800, HighWarn=3000, HighDanger=5000;
            float LowDecimal = 0;
            float HighDecimal = 0;
            // Name, Var, Title, Units, Lo, Hi, LoD, LoW, HiW, HiD
                // vd, ld
        };
        struct IndicatorComponent
        {
            std::string OffLabel = "Indicator Off";
            std::string OnLabel = "Indicator On";
            glm::vec4 OnBackground = {0,1,0,1};
            glm::vec4 OnForeground = {0,0,0,1};
            glm::vec4 OffBackground = {1,1,1,1};
            glm::vec4 OnForeground = {0,0,0,1};
        };
    } // namespace Tuners
    
} // namespace VersaMachina
