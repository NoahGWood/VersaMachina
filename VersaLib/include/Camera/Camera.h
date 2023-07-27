#pragma once

#include "Camera/CameraSettings.h"

namespace VersaMachina
{
    namespace Camera
    {
        class Camera
        {
            public:
                Camera(CameraSettings& settings);
                Camera(const std::string name);
                Camera();
                ~Camera()
                {
                    if(m_SettingsPtr != nullptr)
                    {
                        delete m_SettingsPtr;
                    }
                }

                void Translate(glm::vec3 translation);
                void TranslateX(float x);
                void TranslateY(float y);
                void TranslateZ(float z);
                
                void Rotate(glm::vec3 rotation);
                void RotateX(float x);
                void RotateY(float y);
                void RotateZ(float z);
                
                // Name
                void setName(std::string name) { m_Settings.Name = name; }
                const std::string getName() const { return  m_Settings.Name; }
                // Type
                void setCameraType(CameraType type) { m_Settings.Type = type; }
                const CameraType getCameraType() const { return m_Settings.Type; }
                // Transform
                void setTransform(glm::vec3 transform) { m_Settings.Transform = transform; RecalculateViewMatrix(); }
                const glm::vec3 getTransform()const { return m_Settings.Transform; }
                // Rotation
                void SetRotation(glm::vec3 rotation) { m_Settings.Rotation = rotation; RecalculateViewMatrix(); }
                const glm::vec3 getRotation() const { return m_Settings.Rotation; }
                // Field of View (FOV)
                const float getFOV() const { return m_Settings.FieldOfView; }
                // Aspect Ratio (AR)
                const float getAR() const { return m_Settings.AspectRatio; }
                // Matrices
                const glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
                const glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
                const glm::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

            private:
                void RecalculateViewMatrix();
                void SetType();              
                // Translations
                void f_TranslateX(float x);
                void f_TranslateY(float y);
                void f_TranslateZ(float z);
                // Rotations
                void f_Rotate(glm::vec3 rotation);
                void f_RotateX(float x);
                void f_RotateY(float y);
                void f_RotateZ(float z);

            private:
                CameraSettings m_Settings;
                CameraSettings* m_SettingsPtr; // just to prevent memory leaks
                
                glm::mat4 m_ProjectionMatrix;
                glm::mat4 m_ViewMatrix;
                glm::mat4 m_ViewProjectionMatrix;


// Translation x Rotation x Scale
//                proj x view x model x vertexPos

        };     
    } // namespace Camera
    
} // namespace VersaMachina
