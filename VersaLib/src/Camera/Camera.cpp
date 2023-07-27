#include "pch.h"

#include "Camera/Camera.h"

namespace VersaMachina
{
    namespace Camera
    {
        Camera::Camera()
            : m_ViewMatrix(1.0f)
        {
            m_SettingsPtr = new CameraSettings(); // Create new camera with default values
            m_Settings = *m_SettingsPtr;
            m_Settings.Name = "Default Camera";
            SetType();
            RecalculateViewMatrix();
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
        Camera::Camera(std::string name)
            : m_ViewMatrix(1.0f)
        {
            m_SettingsPtr = new CameraSettings(); // Create new camera with default values
            m_Settings = *m_SettingsPtr;
            m_Settings.Name = name;
            SetType();
            RecalculateViewMatrix();
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
        Camera::Camera(CameraSettings& settings)
            : m_Settings(settings), m_ViewMatrix(1.0f)
        {
            m_SettingsPtr = nullptr;
            SetType();
            RecalculateViewMatrix();
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
        // Calculations
        void Camera::RecalculateViewMatrix()
        {
            glm::mat4 transform;
            switch (m_Settings.Type)
            {
                case CameraType::None : VM_ASSERT(false, "Camera must have a CameraType!"); break;
                case CameraType::Orthographic :
                {
                    transform = glm::translate(glm::mat4(1.0f), m_Settings.Transform)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings.Rotation.z), glm::vec3(0,0,1));
                    break;
                }
                case CameraType::Perspective :
                {
                    transform = glm::translate(glm::mat4(1.0f), -m_Settings.Transform)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings.Rotation.x), glm::vec3(1,0,0))
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings.Rotation.y), glm::vec3(0,1,0))
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings.Rotation.z), glm::vec3(0,0,1));
                    break;
                }
                default:
                    VM_ASSERT(false, "CameraType not implemented.");
            }

            m_ViewMatrix = glm::inverse(transform);
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

        }
        // Rotation
        void Camera::Rotate(glm::vec3 rotation)
        {
            f_RotateX(rotation.x);
            f_RotateY(rotation.y);
            f_RotateZ(rotation.z);
            RecalculateViewMatrix();
        }
        void Camera::RotateX(float x)
        {
            f_RotateX(x);
            RecalculateViewMatrix();
        }
        void Camera::RotateY(float y)
        {
            f_RotateY(y);
            RecalculateViewMatrix();
        }
        void Camera::RotateZ(float z)
        {
            f_RotateZ(z);
            RecalculateViewMatrix();
        }
        // Translation

        void Camera::Translate(glm::vec3 translation)
        {
            f_TranslateX(translation.x);
            f_TranslateY(translation.y);
            f_TranslateZ(translation.z);
            RecalculateViewMatrix();
        }
        void Camera::TranslateX(float x)
        {
            f_TranslateX(x);
            RecalculateViewMatrix();
        }
        void Camera::TranslateY(float y)
        {
            f_TranslateY(y);
            RecalculateViewMatrix();
        }

        void Camera::TranslateZ(float z)
        {
            f_TranslateZ(z);
            RecalculateViewMatrix();
        }

    } // namespace Camera
    
} // namespace VersaMachina
