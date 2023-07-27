#include "pch.h"

#include "Camera/Camera.h"

namespace VersaMachina
{
    namespace Camera
    {
        // Rotation
        void Camera::f_RotateX(float x)
        {
            m_Settings.Rotation.x += x;
        }
        void Camera::f_RotateY(float y)
        {
            m_Settings.Rotation.y += y;
        }
        void Camera::f_RotateZ(float z)
        {
            m_Settings.Rotation.z += z;
        }
        // Translation

        void Camera::f_TranslateX(float x)
        {
            m_Settings.Transform.x += x;
        }
        void Camera::f_TranslateY(float y)
        {
            m_Settings.Transform.y += y;
        }

        void Camera::f_TranslateZ(float z)
        {
            m_Settings.Transform.z += z;
        }

        // Private functions
        void Camera::SetType()
        {
            switch (m_Settings.Type)
            {
                case CameraType::None : VM_ASSERT(false, "Camera must have a CameraType!"); break;
                case CameraType::Orthographic :
                {
                    m_ProjectionMatrix = glm::ortho(
                        m_Settings.Viewport[0], // Left
                        m_Settings.Viewport[1], // Right
                        m_Settings.Viewport[2], // Bottom
                        m_Settings.Viewport[3], // Top
                        m_Settings.NearClip,    // Near
                        m_Settings.FarClip     // Far
                        );
                    break;
                }
                case CameraType::Perspective :
                {
                    m_ProjectionMatrix = glm::perspective(
                        m_Settings.FieldOfView,
                        m_Settings.AspectRatio,
                        m_Settings.NearClip,
                        m_Settings.FarClip
                        );
                    break;
                }
                case CameraType::Physical :
                {
                    VM_CORE_ASSERT(false, "CameraType;:Physical not implemented!");
                    break;
                }
                default: VM_ASSERT(false, "Camera must have a CameraType!"); break;
            }
        }

    } // namespace Camera
    
} // namespace VersaMachina
