#pragma once

namespace VersaMachina
{
    class Timestep
    {
        public:
            Timestep(float time = 0.0f)
                : m_Time(time)
            {
            }
            operator float() const { return m_Time; }
            float GetSeconds() { return m_Time * 0.001; }
            float GetMilliseconds() { return m_Time; }
        private:
            float m_Time;
    };
} // namespace VersaMachina
