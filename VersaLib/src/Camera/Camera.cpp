#include "pch.h"

#include "Camera/Camera.h"

namespace VersaMachina
{
    namespace Camera
    {
        void Camera::SetProjectionMatrix()
        {
            VM_PROFILE_FUNCTION();

            switch (m_Settings->Type)
            {
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
            m_ViewMatrix = glm::inverse(m_Settings->Transform);
            m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }

        const void Camera::SetSettings(CameraSettings settings)
        {
            m_Settings->AspectRatio = settings.AspectRatio;

            m_Settings->Name = settings.Name;
            m_Settings->Type = settings.Type;
            m_Settings->Viewport = settings.Viewport;
            m_Settings->FieldOfView = settings.FieldOfView;
            m_Settings->FieldOfViewAxis = settings.FieldOfViewAxis;
            m_Settings->AspectRatio = settings.AspectRatio;
            m_Settings->NearClip = settings.NearClip;
            m_Settings->FarClip = settings.FarClip;
            m_Settings->Transform = settings.Transform;
            m_Settings->ZoomLevel = settings.ZoomLevel;
            m_Settings->MoveSpeed = settings.MoveSpeed;
            m_Settings->RotateSpeed = settings.RotateSpeed;
        }
        void Camera::Resize(float width, float height)
        {
            m_Settings->AspectRatio = width/height;
            _Resize();
        }

        void Camera::_Resize()
        {
            m_Settings->Viewport[0] = -m_Settings->AspectRatio * m_Settings->ZoomLevel; // Left
            m_Settings->Viewport[1] = m_Settings->AspectRatio * m_Settings->ZoomLevel; // Right
            m_Settings->Viewport[2] = -m_Settings->ZoomLevel; // Bottom
            m_Settings->Viewport[3] = m_Settings->ZoomLevel; // Top
            SetProjectionMatrix();
            RecalculateViewMatrix();
        }
    } // namespace Camera
    
} // namespace VersaMachina
