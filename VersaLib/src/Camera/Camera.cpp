#include "pch.h"

#include "Camera/Camera.h"

namespace VersaMachina
{
    namespace Camera
    {
        Camera::Camera(Ref<CameraSettings> settings)
            : m_Settings(settings), m_ViewMatrix(1.0f)
        {
            VM_PROFILE_FUNCTION();

            SetProjectionMatrix();
            RecalculateViewMatrix();
        }
        void Camera::SetProjectionMatrix()
        {
            VM_PROFILE_FUNCTION();

            switch (m_Settings->Type)
            {
                case CameraType::None : VM_ASSERT(false, "Camera must have a CameraType!"); break;
                case CameraType::Orthographic :
                {
                    m_ProjectionMatrix = glm::ortho(
                        m_Settings->Viewport[0], // Left
                        m_Settings->Viewport[1], // Right
                        m_Settings->Viewport[2], // Bottom
                        m_Settings->Viewport[3], // Top
                        m_Settings->NearClip,    // Near
                        m_Settings->FarClip     // Far
                        );
                    break;
                }
                case CameraType::Perspective :
                {
                    m_ProjectionMatrix = glm::perspective(
                        glm::radians(m_Settings->FieldOfView),
                        m_Settings->AspectRatio,
                        m_Settings->NearClip,
                        m_Settings->FarClip
                        );
                    break;
                }
                case CameraType::Physical :
                {
                    VM_CORE_ASSERT(false, "CameraType::Physical not implemented!");
                    break;
                }
                default: VM_ASSERT(false, "Camera must have a CameraType!"); break;
            }
        }

        // Calculations
        void Camera::RecalculateViewMatrix()
        {
            VM_PROFILE_FUNCTION();

            glm::mat4 transform;
            switch (m_Settings->Type)
            {
                case CameraType::None : VM_ASSERT(false, "Camera must have a CameraType!"); break;
                case CameraType::Orthographic :
                {
                    transform = glm::translate(glm::mat4(1.0f), m_Settings->Position)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings->Rotation.z), glm::vec3(0,0,1));
                    break;
                }
                case CameraType::Perspective :
                {
                    transform = glm::translate(glm::mat4(1.0f), -m_Settings->Position)
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings->Rotation.x), glm::vec3(1,0,0))
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings->Rotation.y), glm::vec3(0,1,0))
                    * glm::rotate(glm::mat4(1.0f), glm::radians(m_Settings->Rotation.z), glm::vec3(0,0,1));
                    break;
                }
                default:
                    VM_ASSERT(false, "CameraType not implemented.");
            }

            m_ViewMatrix = glm::inverse(transform);
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
    } // namespace Camera
    
} // namespace VersaMachina
