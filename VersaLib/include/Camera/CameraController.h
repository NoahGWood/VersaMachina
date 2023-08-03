#pragma once
#include "Core/Base.h"
#include "Core/Timestep.h"

#include "Camera/CameraSettings.h"
#include "Camera/Camera.h"

#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"

namespace VersaMachina
{
    namespace Camera
    {
        class CameraController
        {
            public:
                CameraController();
//                CameraController(CameraSettings& settings); // aspectratio * 2 units
                ~CameraController();

                void OnUpdate(Timestep ts);
                void OnEvent(Event& e);

                void Resize(float width, float height);

                Camera& GetCamera() { return m_Camera; }
                const Camera& GetCamera() const { return m_Camera; }

            private:
                bool OnMouseScrolledEvent(MouseScrolledEvent& e);
                bool OnWindowResized(WindowResizedEvent& e);
            private:
                Ref<CameraSettings> m_Settings;
                CameraSettings* m_SettingsPtr; // just to prevent memory leaks
                Camera m_Camera;


        };
    } // namespace Camera
    
} // namespace VersaMachina
