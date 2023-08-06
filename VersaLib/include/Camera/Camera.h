#pragma once
#include "Core/Base.h"
#include "Camera/CameraSettings.h"

namespace VersaMachina
{
    namespace Camera
    {
        class Camera
        {
            public:
                Camera()
                {
                    m_Settings = new CameraSettings();
                    SetProjectionMatrix();
                    RecalculateViewMatrix();
                }
                ~Camera()
                {
                    delete m_Settings;
                }

                const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
                const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
                const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

                CameraSettings* GetSettings() { return m_Settings; }
                const CameraSettings* GetSettings() const { return m_Settings; }

                const void SetSettings(CameraSettings settings);

                void Resize(float width, float height);

                void SetProjectionMatrix();
                void RecalculateViewMatrix();

                CameraSettings* m_Settings;
                
            private:
                glm::mat4 m_ProjectionMatrix;
                glm::mat4 m_ViewMatrix;
                glm::mat4 m_ViewProjectionMatrix;

// Translation x Rotation x Scale
//                proj x view x model x vertexPos

        };     
    } // namespace Camera
    
} // namespace VersaMachina
