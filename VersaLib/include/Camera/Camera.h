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
                    m_Settings = CreateRef<CameraSettings>();
                    SetProjectionMatrix();
                    RecalculateViewMatrix();
                }
                virtual ~Camera()
                {
                }

            public:
                // Getters
                CameraType GetType() const { return m_Settings->Type; }
                glm::mat4 GetTransform() const { return m_Settings->Transform; }
                glm::vec4 GetViewport() const { return m_Settings->Viewport; }
                // Field of view
                float GetFOV() const { return m_Settings->FieldOfView; }
                FOVAxis GetFOVAxis() const { return m_Settings->FieldOfViewAxis; }
                // Aspect ratio
                float GetAspectRatio() const { return m_Settings->AspectRatio; }
                bool GetFixedAspectRatio() const { return m_Settings->FixedAspectRatio; }
                // Clipping
                float GetNearClip() const { return m_Settings->NearClip; }
                float GetFarClip() const { return m_Settings->FarClip; }
                // Position (done in transform)
                // Zoom
                float GetZoomLevel() const { return m_Settings->ZoomLevel; }
                float GetMoveSpeed() const { return m_Settings->MoveSpeed; }
                float GetRotateSpeed() const { return m_Settings->RotateSpeed; }
            public:
                // Setters
                void SetName(std::string name) { m_Settings->Name = name; }
                void SetType(CameraType type) { m_Settings->Type = type; _Resize(); }
                void SetType(int type) { m_Settings->Type = (CameraType)type; _Resize(); }
                void SetTransform(glm::mat4 Transform) { m_Settings->Transform = Transform; _Resize(); }
                void SetViewport(glm::vec4 viewport) { m_Settings->Viewport = viewport; _Resize(); }
                // Field of view
                void SetFOV(float fov) { m_Settings->FieldOfView = fov; _Resize(); }
                void SetFOVAxis(FOVAxis fa) { m_Settings->FieldOfViewAxis = fa; _Resize(); }
                void SetFOVAxis(int fa) { m_Settings->FieldOfViewAxis = (FOVAxis)fa; _Resize(); }
                // Aspect Ratio
                void SetAspectRatio(float ar) { m_Settings->AspectRatio = ar; _Resize(); }
                void SetFixedAspectRatio(bool far) { m_Settings->FixedAspectRatio = far; }
                // Clipping
                void SetNearClip(float nc) { m_Settings->NearClip = nc; _Resize(); }
                void SetFarClip(float fc) { m_Settings->FarClip = fc; _Resize(); }
                // Zoom and movement
                void SetZoomLevel(float zl) { m_Settings->ZoomLevel = zl; _Resize(); }
                void SetMoveSpeed(float ms) { m_Settings->MoveSpeed = ms; _Resize(); }
                void SetRotateSpeed(float rs) { m_Settings->RotateSpeed = rs; _Resize(); }

            public:
                const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
                const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
                const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

                Ref<CameraSettings> GetSettings() { return m_Settings; }

                const void SetSettings(CameraSettings settings);

                void Resize(float width, float height);
                void _Resize();

                void SetProjectionMatrix();
                void RecalculateViewMatrix();

                Ref<CameraSettings> m_Settings;
                
            private:
                glm::mat4 m_ProjectionMatrix;
                glm::mat4 m_ViewMatrix;
                glm::mat4 m_ViewProjectionMatrix;

// Translation x Rotation x Scale
//                proj x view x model x vertexPos

        };     
    } // namespace Camera
    
} // namespace VersaMachina
