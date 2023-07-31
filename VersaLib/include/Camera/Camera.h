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
                Camera(Ref<CameraSettings> settings);
                ~Camera(){}

                const glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
                const glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
                const glm::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

                void SetProjectionMatrix();
                void RecalculateViewMatrix();
                
            private:
                Ref<CameraSettings> m_Settings;
                
                glm::mat4 m_ProjectionMatrix;
                glm::mat4 m_ViewMatrix;
                glm::mat4 m_ViewProjectionMatrix;


// Translation x Rotation x Scale
//                proj x view x model x vertexPos

        };     
    } // namespace Camera
    
} // namespace VersaMachina
